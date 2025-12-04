#pragma once

#ifdef SHADOW_PLATFORM_WINDOWS

extern Shadow::Application* Shadow::CreateApplication();

int main(int argc, char** argv)
{
	Shadow::Log::Init();
	SHADOW_ENGINE_INFO("Hello Engine");
	SHADOW_APP_WARN("Hello Application");

	auto app = Shadow::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif