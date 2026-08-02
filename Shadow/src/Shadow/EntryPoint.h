#pragma once

#include "Shadow/config.h"

#ifdef SHADOW_PLATFORM_WINDOWS

extern Shadow::Application* Shadow::CreateApplication();

int main(int argc, char** argv)
{
    Shadow::Log::Init();
    SHADOW_LOG_WARN("Hello Application");

    auto app = Shadow::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif