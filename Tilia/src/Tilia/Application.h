#pragma once

#include "Core.h"

#include "Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "LayerStack.h"
#include "Tilia/ImGui/ImGuiLayer.h"

#include "Tilia/Renderer/Shader.h"
#include "Tilia/Renderer/Buffer.h"

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

		unsigned int m_VertexArray;
	private:
		static Application* s_Instance;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}
