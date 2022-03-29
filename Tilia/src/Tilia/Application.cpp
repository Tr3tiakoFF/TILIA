#include "tlpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

#include "Renderer/Renderer.h"

#include "Input.h"

namespace Tilia {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		TL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArrayForTriangle.reset(VertexArray::Create());
		m_VertexArrayForSquare.reset(VertexArray::Create());

		/*
		float vertices[3 * 7] = {
			-0.5f, -0.65f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.65f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f,
			 0.0f,  0.71f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		*/

		float verticesForTriangle[3 * (3 + 4)] = {
			 0.00f,  0.50f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			 0.43f, -0.25f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			-0.43f, -0.25f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
		};

		float verticesForSquare[4 * (3 + 4)] = {
			-0.6f, -0.5f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f,
			 0.6f, -0.5f, 0.0f, 0.1f, 0.1f, 0.1f, 1.0f,
			 0.6f,  0.6f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f,
			-0.6f,  0.6f, 0.0f, 0.3f, 0.3f, 0.3f, 1.0f,
		};

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		std::shared_ptr<VertexBuffer> vertexBufferForTriangle;
		vertexBufferForTriangle.reset(VertexBuffer::Create(verticesForTriangle, sizeof(verticesForTriangle)));
		vertexBufferForTriangle->SetLayout(layout);
		m_VertexArrayForTriangle->AddVertexBuffer(vertexBufferForTriangle);

		std::shared_ptr<VertexBuffer> vertexBufferForSquare;
		vertexBufferForSquare.reset(VertexBuffer::Create(verticesForSquare, sizeof(verticesForSquare)));
		vertexBufferForSquare->SetLayout(layout);
		m_VertexArrayForSquare->AddVertexBuffer(vertexBufferForSquare);


		uint32_t indicesForTriangle[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBufferForTriangle;
		indexBufferForTriangle.reset(IndexBuffer::Create(indicesForTriangle, sizeof(indicesForTriangle) / sizeof(uint32_t)));
		m_VertexArrayForTriangle->SetIndexBuffer(indexBufferForTriangle);

		uint32_t indicesForSquare[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> indexBufferForSquare;
		indexBufferForSquare.reset(IndexBuffer::Create(indicesForSquare, sizeof(indicesForSquare) / sizeof(uint32_t)));
		m_VertexArrayForSquare->SetIndexBuffer(indexBufferForSquare);

		std::string vertexSrcForTriangle = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;

				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrcForTriangle = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		std::string vertexSrcForSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;

				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrcForSquare = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_ShaderForTriangle.reset(new Shader(vertexSrcForTriangle, fragmentSrcForTriangle));
		m_ShaderForSquare.reset(new Shader(vertexSrcForSquare, fragmentSrcForSquare));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_ShaderForSquare, m_VertexArrayForSquare);
			Renderer::Submit(m_ShaderForTriangle, m_VertexArrayForTriangle);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
}
