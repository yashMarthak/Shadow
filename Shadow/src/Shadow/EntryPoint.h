#pragma once

#ifdef SHADOW_PLATFORM_WINDOWS

extern Shadow::Application* Shadow::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Shadow::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif