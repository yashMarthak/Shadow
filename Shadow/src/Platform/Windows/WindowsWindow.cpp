#include "precomp.h"

#ifdef SHADOW_PLATFORM_WINDOWS

#include "WindowsWindow.h"
#include "Shadow/Event/ApplicationEvent.h"
#include "Shadow/Event/KeyboardEvent.h"
#include "Shadow/Event/MouseEvent.h"

#include <Windows.h>

SHADOW_BEGIN_NAMESPACE

static bool s_WindowClassRegistered = false;

Window* Window::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    Init(props);
}

WindowsWindow::~WindowsWindow()
{
    Shutdown();
}

void WindowsWindow::Init(const WindowProps& props)
{
    m_Title = props.Title;
    m_Width = props.Width;
    m_Height = props.Height;
    m_VSync = props.VSync;

    SHADOW_LOG_INFO("Creating window: {0} ({1}, {2})", m_Title, m_Width, m_Height);

    if (s_WindowClassRegistered == false)
    {
        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowsWindow::WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = L"ShadowWindowClass";
        ATOM classAtom = RegisterClass(&wc);
        SHADOW_ASSERT(classAtom, "Failed to register window class!");
        s_WindowClassRegistered = true;
    }

    std::wstring wTitle = std::wstring(m_Title.begin(), m_Title.end());

    m_WindowHandle = CreateWindowEx(
        0,
        L"ShadowWindowClass",
        wTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        this
    );
    SHADOW_ASSERT(m_WindowHandle, "Failed to create window! Last Error: {0}", GetLastError());
    
    SHADOW_LOG_INFO("Window created successfully!");
    ShowWindow(m_WindowHandle, SW_SHOW);
}

void WindowsWindow::Shutdown()
{
    SHADOW_LOG_INFO("Destroying window: {0} ({1}, {2})", m_Title, m_Width, m_Height);
    DestroyWindow(m_WindowHandle);
}

void WindowsWindow::SetVSync(bool enabled)
{
    // TODO: Implement VSync functionality for Windows platform after renderer is implemented
    m_VSync = enabled;
}

void WindowsWindow::OnUpdate()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT WindowsWindow::HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CLOSE:
        {
            WindowCloseEvent event;
            m_EventCallback(event);
            return 0;
        }
        case WM_SIZE:
        {
            m_Width = LOWORD(lParam);
            m_Height = HIWORD(lParam);
            WindowResizeEvent event(m_Width, m_Height);
            m_EventCallback(event);
            return 0;
        }
        case WM_SETFOCUS:
        {
            WindowFocusEvent event;
            m_EventCallback(event);
            return 0;
        }
        case WM_KILLFOCUS:
        {
            WindowLostFocusEvent event;
            m_EventCallback(event);
            return 0;
        }
        case WM_MOVE:
        {
            int x = (int)(short)LOWORD(lParam);
            int y = (int)(short)HIWORD(lParam);
            WindowMovedEvent event(x, y);
            m_EventCallback(event);
            return 0;
        }
        case WM_KEYDOWN:
        {
            int key = (int)wParam;
            bool isRepeat = (lParam & 0x40000000) != 0;
            KeyPressedEvent event(key, isRepeat);
            m_EventCallback(event);
            return 0;
        }
        case WM_KEYUP:
        {
            int key = (int)wParam;
            KeyReleasedEvent event(key);
            m_EventCallback(event);
            return 0;
        }
        case WM_LBUTTONDOWN:
        {
            MouseButtonPressedEvent event(0); // 0 for left button
            m_EventCallback(event);
            return 0;
        }
        case WM_LBUTTONUP:
        {
            MouseButtonReleasedEvent event(0); // 0 for left button
            m_EventCallback(event);
            return 0;
        }
        case WM_RBUTTONDOWN:
        {
            MouseButtonPressedEvent event(1); // 1 for right button
            m_EventCallback(event);
            return 0;
        }
        case WM_RBUTTONUP:
        {
            MouseButtonReleasedEvent event(1); // 1 for right button
            m_EventCallback(event);
            return 0;
        }
        case WM_MBUTTONDOWN:
        {
            MouseButtonPressedEvent event(2); // 2 for middle button
            m_EventCallback(event);
            return 0;
        }
        case WM_MOUSEMOVE:
        {
            float x = (float)(short)LOWORD(lParam);
            float y = (float)(short)HIWORD(lParam);
            MouseMovedEvent event(x, y);
            m_EventCallback(event);
            return 0;
        }
        case WM_MOUSEWHEEL:
        {
            float delta = GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
            MouseScrolledEvent event(0.0f, delta);
            m_EventCallback(event);
            return 0;
        }
        default:
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK WindowsWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WindowsWindow* window = nullptr;
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        window = reinterpret_cast<WindowsWindow*>(createStruct->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    }
    else
    {
        window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (window)
        return window->HandleMessage(hwnd, msg, wParam, lParam);

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

SHADOW_END_NAMESPACE

#endif // SHADOW_PLATFORM_WINDOWS