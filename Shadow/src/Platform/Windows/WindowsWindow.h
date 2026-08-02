#pragma once

#ifdef SHADOW_PLATFORM_WINDOWS

#include "Shadow/Window.h"
#include <Windows.h>

SHADOW_BEGIN_NAMESPACE

class WindowsWindow : public Window
{
public:
    WindowsWindow(const WindowProps& props);
    ~WindowsWindow();

    unsigned int GetWidth() const override { return m_Data.Width; }
    unsigned int GetHeight() const override { return m_Data.Height; }

    void SetVSync(bool enabled) override;
    bool IsVSync() const override { return m_Data.VSync; }

    void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

    void OnUpdate() override;

private:
    void Init(const WindowProps& props);
    void Shutdown();
    LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    HWND m_WindowHandle = nullptr;

    struct WindowData
    {
        std::wstring Title;
        unsigned int Width = 0, Height = 0;
        bool VSync = false;
        EventCallbackFn EventCallback = [](const Event& event) {};
    };
    WindowData m_Data;
};

SHADOW_END_NAMESPACE

#endif // SHADOW_PLATFORM_WINDOWS