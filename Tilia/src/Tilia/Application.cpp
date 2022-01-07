#include "tlpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "GLFW/glfw3.h"

namespace Tilia {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		float R = 0;
		float B = 1;
		bool incR = true;
		bool incB = true;
		while (m_Running)
		{
			glClearColor(R, 0, B, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();

			if (R >= 1)
				incR = false;
			if (R <= 0)
				incR = true;

			if (incR)
				R += 0.01;
			else
				R -= 0.01;

			if (B >= 1)
				incB = false;
			if (B <= 0)
				incB = true;

			if (incB)
				B += 0.01;
			else
				B -= 0.01;
		}
	}

}
