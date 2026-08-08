#pragma once
#include "Shadow/config.h"

SHADOW_BEGIN_NAMESPACE

class Window;
class Event;

class SHADOW_API Application
{
public:
    Application();
    virtual ~Application();

    Application(Application&) = delete;
    Application& operator=(Application&) = delete;

    void Run();

private:
    void OnEvent(Event& e);

private:
    bool m_Running = true;
    Window* m_Window;
};

// To be defined in CLIENT
Application* CreateApplication();

SHADOW_END_NAMESPACE