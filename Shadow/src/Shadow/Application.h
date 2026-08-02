#pragma once
#include "Shadow/config.h"
#include <memory>

SHADOW_BEGIN_NAMESPACE

class Window;

class SHADOW_API Application
{
public:
    Application();
    virtual ~Application();

    void Run();

private:
    std::unique_ptr<class Window> m_Window;
};

// To be defined in CLIENT
Application* CreateApplication();

SHADOW_END_NAMESPACE