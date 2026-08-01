#include "precomp.h"
#include "Application.h"
#include "Shadow/Event/ApplicationEvent.h"
#include "Shadow/log.h"

SHADOW_BEGIN_NAMESPACE

Application::Application()
{
}

Application::~Application()
{
}

void Application::Run()
{
    WindowResizeEvent e(1280, 720);
    SHADOW_TRACE(e.ToString());
	while (true);
}
	
SHADOW_END_NAMESPACE