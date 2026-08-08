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

    unsigned int GetWidth() const override { return m_Width; }
    unsigned int GetHeight() const override { return m_Height; }

    void SetVSync(bool enabled) override;
    bool IsVSync() const override { return m_VSync; }

    void SetEventCallback(const EventCallbackFn& callback) override { m_EventCallback = callback; }

    void OnUpdate() override;

private:
    void Init(const WindowProps& props);
    void Shutdown();
    LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    HWND m_WindowHandle = nullptr;

    std::string m_Title;
    unsigned int m_Width = 0, m_Height = 0;
    bool m_VSync = false;
    EventCallbackFn m_EventCallback = [](const Event& event) {};
};

SHADOW_END_NAMESPACE

#endif // SHADOW_PLATFORM_WINDOWS