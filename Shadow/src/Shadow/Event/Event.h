#pragma once
#include "spdlog/fmt/ostr.h"

SHADOW_BEGIN_NAMESPACE

enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput       = BIT(1),
    EventCategoryKeyboard    = BIT(2),
    EventCategoryMouse       = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

class Event
{
public:
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;
    virtual int GetCategoryFlags() const = 0;
  
    inline bool IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & category;
    }

    virtual const char* GetName() const = 0;
    virtual std::string ToString() const { return GetName(); }
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}

SHADOW_END_NAMESPACE