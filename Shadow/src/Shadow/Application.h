#pragma once

SHADOW_BEGIN_NAMESPACE
	
class SHADOW_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();
};

// To be defined in CLIENT
Application* CreateApplication();

SHADOW_END_NAMESPACE