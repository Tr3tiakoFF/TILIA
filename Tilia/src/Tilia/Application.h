#pragma once

#include "Core.h"

#include "Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "LayerStack.h"
#include "Tilia/ImGui/ImGuiLayer.h"

#include "Tilia/Renderer/Shader.h"
#include "Tilia/Renderer/Buffer.h"
#include "Tilia/Renderer/VertexArray.h"

#include <Tilia/Renderer/OrthographicCamera.h>

namespace Tilia {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;

		OrthographicCamera m_Camera;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}
