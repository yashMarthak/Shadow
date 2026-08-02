#include "precomp.h"

#include "Application.h"
#include "Window.h"

SHADOW_BEGIN_NAMESPACE

Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application()
{

}

void Application::Run()
{
    while (true)
    {
        m_Window->OnUpdate();
    }
}

SHADOW_END_NAMESPACE