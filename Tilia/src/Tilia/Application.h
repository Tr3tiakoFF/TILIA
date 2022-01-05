#pragma once

#include "Core.h"

namespace Tilia {

	class TILIA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}
