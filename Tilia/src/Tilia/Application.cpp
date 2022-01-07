#include "tlpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Tilia {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			TL_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			TL_TRACE(e);
		}
		while (true);
	}

}
