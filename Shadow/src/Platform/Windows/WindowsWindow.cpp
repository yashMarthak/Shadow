#include "precomp.h"

#include "WindowsWindow.h"
#include "Shadow\Event\ApplicationEvent.h"
#include <Windows.h>

SHADOW_BEGIN_NAMESPACE

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
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowsWindow::WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"ShadowWindowClass";
    RegisterClass(&wc);

    m_WindowHandle = CreateWindowEx(
        0,
        L"ShadowWindowClass",
        (LPCWSTR)m_Data.Title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, m_Data.Width, m_Data.Height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        this
    );
    ShowWindow(m_WindowHandle, SW_SHOW);
}

void WindowsWindow::Shutdown()
{
    DestroyWindow(m_WindowHandle);
}

void WindowsWindow::SetVSync(bool enabled)
{
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

void WindowsWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
    {
        WindowCloseEvent event;
        //m_Data.EventCallback(event);
        SHADOW_LOG_INFO("Window Close Event Triggered");
        break;
    }
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        m_Data.Width = width;
        m_Data.Height = height;
        WindowResizeEvent event(width, height);
        //m_Data.EventCallback(event);
        SHADOW_LOG_INFO("Window Resize Event Triggered: Width = {}, Height = {}", width, height);
        break;
    }
    case WM_SETFOCUS:
    {
        WindowFocusEvent event;
        //m_Data.EventCallback(event);
        SHADOW_LOG_INFO("Window Focus Event Triggered");
        break;
    }
    case WM_KILLFOCUS:
    {
        WindowFocusEvent event;
        //m_Data.EventCallback(event);
        SHADOW_LOG_INFO("Window Focus Event Triggered");
        break;
    }
    default:
        break;
    }
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
    {
        window->HandleMessage(msg, wParam, lParam);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

SHADOW_END_NAMESPACE