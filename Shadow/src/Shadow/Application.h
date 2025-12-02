#pragma once
#include "config.h"

namespace Shadow
{
	class SHADOW_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}