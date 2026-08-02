#pragma once

SHADOW_BEGIN_NAMESPACE

class Event;

struct WindowProps
{
    unsigned int Width;
    unsigned int Height;
    std::string Title;

    WindowProps(unsigned int width = 1280, unsigned int height = 720, const std::string& title = "Shadow Engine")
        : Width(width), Height(height), Title(title) {}
};

class SHADOW_API Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() = default;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

    virtual void OnUpdate() = 0;

    static Window* Create(const WindowProps& props = WindowProps());
};

SHADOW_END_NAMESPACE