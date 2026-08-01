#pragma once
#include "precomp.h"
#include "Shadow/Event/Event.h"

SHADOW_BEGIN_NAMESPACE

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}

    EventType GetEventType() const override { return EventType::WindowClose; }
    int GetCategoryFlags() const override { return EventCategoryApplication; }

    const char* GetName() const override { return "WindowCloseEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName();
        return ss.str();
    }
};

class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(int width, int height)
        : m_Width(width), m_Height(height) {
    }

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }

    EventType GetEventType() const override { return EventType::WindowResize; }
    int GetCategoryFlags() const override { return EventCategoryApplication; }

    const char* GetName() const override { return "WindowResizeEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_Width << ", " << m_Height;
        return ss.str();
    }

private:
    int m_Width, m_Height;
};

class WindowFocusEvent : public Event
{
public:
    WindowFocusEvent() {}
    
    EventType GetEventType() const override { return EventType::WindowFocus; }
    int GetCategoryFlags() const override { return EventCategoryApplication; }
    
    const char* GetName() const override { return "WindowFocusEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName();
        return ss.str();
    }
};

class WindowLostFocusEvent : public Event
{
public:
    WindowLostFocusEvent() {}

    EventType GetEventType() const override { return EventType::WindowLostFocus; }
    int GetCategoryFlags() const override { return EventCategoryApplication; }

    const char* GetName() const override { return "WindowLostFocusEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName();
        return ss.str();
    }
};

class WindowMovedEvent : public Event
{
public:
    WindowMovedEvent(int x, int y)
        : m_WindowX(x), m_WindowY(y) {
    }

    inline int GetX() const { return m_WindowX; }
    inline int GetY() const { return m_WindowY; }

    EventType GetEventType() const override { return EventType::WindowMoved; }
    int GetCategoryFlags() const override { return EventCategoryApplication; }

    const char* GetName() const override { return "WindowMovedEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_WindowX << ", " << m_WindowY;
        return ss.str();
    }

private:
    int m_WindowX, m_WindowY;
};

SHADOW_END_NAMESPACE