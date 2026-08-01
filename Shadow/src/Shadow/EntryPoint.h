#pragma once

#ifdef SHADOW_PLATFORM_WINDOWS

extern Shadow::Application* Shadow::CreateApplication();

int main(int argc, char** argv)
{
	Shadow::Log::Init();
	SHADOW_WARN("Hello Application");

	auto app = Shadow::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif