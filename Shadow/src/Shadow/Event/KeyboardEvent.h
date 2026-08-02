#pragma once
#include "Shadow/Event/Event.h"

SHADOW_BEGIN_NAMESPACE

class KeyPressedEvent : public Event
{
public:
    KeyPressedEvent(int keycode, int repeatCount)
        : m_KeyCode(keycode), m_RepeatCount(repeatCount) {}

    inline int GetKeyCode() const { return m_KeyCode; }
    inline int GetRepeatCount() const { return m_RepeatCount; }
    inline bool IsRepeat() const { return m_RepeatCount > 0; }

    EventType GetEventType() const override { return EventType::KeyPressed; }
    int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

    const char* GetName() const override { return "KeyPressedEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_KeyCode << " (repeat: " << m_RepeatCount << ")";
        return ss.str();
    }
private:
    int m_KeyCode;
    int m_RepeatCount;
};

class KeyReleasedEvent : public Event
{
public:
    KeyReleasedEvent(int keycode)
        : m_KeyCode(keycode) {
    }

    inline int GetKeyCode() const { return m_KeyCode; }

    EventType GetEventType() const override { return EventType::KeyReleased; }
    int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

    const char* GetName() const override { return "KeyReleasedEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_KeyCode;
        return ss.str();
    }
private:
    int m_KeyCode;
};

SHADOW_END_NAMESPACE