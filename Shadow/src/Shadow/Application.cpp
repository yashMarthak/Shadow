#include "precomp.h"

#include "Application.h"
#include "Event/Event.h"
#include "Window.h"

SHADOW_BEGIN_NAMESPACE

Application::Application()
{
    m_Window = Window::Create();
    m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });
}

Application::~Application()
{
    delete m_Window;
}

void Application::OnEvent(Event& e)
{
    SHADOW_LOG_TRACE("Event: {0}", e.ToString());
    if (e.GetEventType() == EventType::WindowClose)
    {
        m_Running = false;
    }
}

void Application::Run()
{
    while (m_Running)
    {
        m_Window->OnUpdate();
    }
}

SHADOW_END_NAMESPACE