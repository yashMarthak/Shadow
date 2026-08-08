#pragma once
#include "Shadow/Event/Event.h"

SHADOW_BEGIN_NAMESPACE

class KeyPressedEvent : public Event
{
public:
    KeyPressedEvent(int keycode, bool isRepeat)
        : m_KeyCode(keycode), m_IsRepeat(isRepeat) {}

    inline int GetKeyCode() const { return m_KeyCode; }
    inline bool IsRepeat() const { return m_IsRepeat; }

    EventType GetEventType() const override { return EventType::KeyPressed; }
    int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

    const char* GetName() const override { return "KeyPressedEvent"; }
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << ": " << m_KeyCode << " (repeat: " << m_IsRepeat << ")";
        return ss.str();
    }
private:
    int m_KeyCode;
    bool m_IsRepeat;
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