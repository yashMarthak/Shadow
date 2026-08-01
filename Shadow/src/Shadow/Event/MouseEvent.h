#pragma once
#include "precomp.h"
#include "Shadow/Event/Event.h"

SHADOW_BEGIN_NAMESPACE

class MouseButtonPressed : public Event
{
public:
    MouseButtonPressed(int button)
        : m_Button(button) {}

    inline int GetMouseButton() const { return m_Button; }

    EventType GetEventType() const override { return EventType::MouseButtonPressed; }
    inline int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton; }

    const char* GetName() const override { return "MouseButtonPressed"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_Button;
        return ss.str();
    }
private:
    int m_Button;
};

class MouseButtonReleased : public Event
{
public:
    MouseButtonReleased(int button)
        : m_Button(button) {}

    inline int GetMouseButton() const { return m_Button; }

    EventType GetEventType() const override { return EventType::MouseButtonReleased; }
    inline int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton; }
    
    const char* GetName() const override { return "MouseButtonReleased"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_Button;
        return ss.str();
    }
private:
    int m_Button;
};

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x, float y)
        : m_MouseX(x), m_MouseY(y) {
    }

    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

    EventType GetEventType() const override { return EventType::MouseMoved; }
    inline int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

    const char* GetName() const override { return "MouseMovedEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset) {}

    inline float GetXOffset() const { return m_XOffset; }
    inline float GetYOffset() const { return m_YOffset; }
    
    EventType GetEventType() const override { return EventType::MouseScrolled; }
    inline int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
    
    const char* GetName() const override { return "MouseScrolledEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_XOffset << ", " << m_YOffset;
        return ss.str();
    }

private:
    float m_XOffset, m_YOffset;
};

SHADOW_END_NAMESPACE