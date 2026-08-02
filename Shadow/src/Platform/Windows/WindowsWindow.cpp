#include "precomp.h"

#ifdef SHADOW_PLATFORM_WINDOWS

#include "WindowsWindow.h"
#include "Shadow/Event/ApplicationEvent.h"

SHADOW_BEGIN_NAMESPACE

static bool s_WindowInitialized = false;

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
    if (s_WindowInitialized)
    {
        SHADOW_LOG_ERROR("Window already initialized!");
        return;
    }

    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    m_Data.VSync = props.VSync;

    SHADOW_LOG_INFO("Creating window: ({0}, {1})", m_Data.Width, m_Data.Height);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowsWindow::WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"ShadowWindowClass";
    ATOM classAtom = RegisterClass(&wc);
    SHADOW_ASSERT(classAtom, "Failed to register window class!");

    m_WindowHandle = CreateWindowEx(
        0,
        L"ShadowWindowClass",
        m_Data.Title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, m_Data.Width, m_Data.Height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        this
    );
    SHADOW_ASSERT(m_WindowHandle, "Failed to create window! Last Error: {0}", GetLastError());
    
    SHADOW_LOG_INFO("Window created successfully!");
    ShowWindow(m_WindowHandle, SW_SHOW);

    s_WindowInitialized = true;
}

void WindowsWindow::Shutdown()
{
    SHADOW_LOG_INFO("Destroying window: ({0}, {1})", m_Data.Width, m_Data.Height);
    DestroyWindow(m_WindowHandle);
}

void WindowsWindow::SetVSync(bool enabled)
{
    SHADOW_LOG_TRACE("Setting VSync: {0}", enabled);
    m_Data.VSync = enabled;
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
        m_Data.EventCallback(event);
        SHADOW_LOG_INFO("Window Close Event Triggered");
        return 0;
    }
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        m_Data.Width = width;
        m_Data.Height = height;
        WindowResizeEvent event(width, height);
        m_Data.EventCallback(event);
        SHADOW_LOG_INFO("Window Resize Event Triggered: Width = {}, Height = {}", width, height);
        return 0;
    }
    case WM_SETFOCUS:
    {
        WindowFocusEvent event;
        m_Data.EventCallback(event);
        SHADOW_LOG_INFO("Window Focus Event Triggered");
        return 0;
    }
    case WM_KILLFOCUS:
    {
        WindowLostFocusEvent event;
        m_Data.EventCallback(event);
        SHADOW_LOG_INFO("Window Focus Lost Event Triggered");
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