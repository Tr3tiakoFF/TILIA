#include <Tilia.h>

#include "imgui/imgui.h"
#include <glm/glm/ext/matrix_transform.hpp>

class ExampleLayer : public Tilia::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArrayForTriangle.reset(Tilia::VertexArray::Create());
		m_VertexArrayForSquare.reset(Tilia::VertexArray::Create());

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
			-0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.1f, 0.1f, 0.1f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.2f, 0.2f, 0.2f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.3f, 0.3f, 0.3f, 1.0f,
		};

		Tilia::BufferLayout layout = {
			{ Tilia::ShaderDataType::Float3, "a_Position" },
			{ Tilia::ShaderDataType::Float4, "a_Color" }
		};

		std::shared_ptr<Tilia::VertexBuffer> vertexBufferForTriangle;
		vertexBufferForTriangle.reset(Tilia::VertexBuffer::Create(verticesForTriangle, sizeof(verticesForTriangle)));
		vertexBufferForTriangle->SetLayout(layout);
		m_VertexArrayForTriangle->AddVertexBuffer(vertexBufferForTriangle);

		std::shared_ptr<Tilia::VertexBuffer> vertexBufferForSquare;
		vertexBufferForSquare.reset(Tilia::VertexBuffer::Create(verticesForSquare, sizeof(verticesForSquare)));
		vertexBufferForSquare->SetLayout(layout);
		m_VertexArrayForSquare->AddVertexBuffer(vertexBufferForSquare);


		uint32_t indicesForTriangle[3] = { 0, 1, 2 };
		std::shared_ptr<Tilia::IndexBuffer> indexBufferForTriangle;
		indexBufferForTriangle.reset(Tilia::IndexBuffer::Create(indicesForTriangle, sizeof(indicesForTriangle) / sizeof(uint32_t)));
		m_VertexArrayForTriangle->SetIndexBuffer(indexBufferForTriangle);

		uint32_t indicesForSquare[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Tilia::IndexBuffer> indexBufferForSquare;
		indexBufferForSquare.reset(Tilia::IndexBuffer::Create(indicesForSquare, sizeof(indicesForSquare) / sizeof(uint32_t)));
		m_VertexArrayForSquare->SetIndexBuffer(indexBufferForSquare);

		std::string vertexSrcForTriangle = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;

				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;

				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		m_ShaderForTriangle.reset(new Tilia::Shader(vertexSrcForTriangle, fragmentSrcForTriangle));
		m_ShaderForSquare.reset(new Tilia::Shader(vertexSrcForSquare, fragmentSrcForSquare));
	}
	
	void OnUpdate(Tilia::Timestep ts) override
	{
		if (Tilia::Input::IsKeyPressed(TL_KEY_A)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * glm::cos(glm::radians(m_CameraRotation)) * ts;
			m_CameraPosition.y -= m_CameraMoveSpeed * glm::sin(glm::radians(m_CameraRotation)) * ts;
		}
		else if (Tilia::Input::IsKeyPressed(TL_KEY_D)) {
			m_CameraPosition.x += m_CameraMoveSpeed * glm::cos(glm::radians(m_CameraRotation)) * ts;
			m_CameraPosition.y += m_CameraMoveSpeed * glm::sin(glm::radians(m_CameraRotation)) * ts;
		}

		if (Tilia::Input::IsKeyPressed(TL_KEY_W)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * glm::sin(glm::radians(m_CameraRotation)) * ts;
			m_CameraPosition.y += m_CameraMoveSpeed * glm::cos(glm::radians(m_CameraRotation)) * ts;
		}
		else if (Tilia::Input::IsKeyPressed(TL_KEY_S)) {
			m_CameraPosition.x += m_CameraMoveSpeed * glm::sin(glm::radians(m_CameraRotation)) * ts;
			m_CameraPosition.y -= m_CameraMoveSpeed * glm::cos(glm::radians(m_CameraRotation)) * ts;
		}

		if (Tilia::Input::IsKeyPressed(TL_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Tilia::Input::IsKeyPressed(TL_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (Tilia::Input::IsKeyPressed(TL_KEY_Z))
			m_squareScale += 0.1f * ts;
		if (Tilia::Input::IsKeyPressed(TL_KEY_X))
			m_squareScale -= 0.1f * ts;

		//NOT WORKING WITH ROTATION CURRENTLY
		/*
		if (Tilia::Input::IsMouseButtonPressed(TL_MOUSE_BUTTON_1)) {
			glm::vec2 cameraSpeedVector = glm::normalize(glm::vec2(Tilia::Input::GetMouseX() - 800.0f, (-1) * Tilia::Input::GetMouseY() + 450.0f)) * m_CameraMoveSpeed;
			m_CameraPosition.x += cameraSpeedVector.x;
			m_CameraPosition.y += cameraSpeedVector.y;
		}
		*/

		Tilia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Tilia::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Tilia::Renderer::BeginScene(m_Camera);
		

		glm::mat4 squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_squareScale));
		float distBetweenSquares = 0.1f;
		for (int x = -10; x <= 10; x++) 
		{
			for (int y = -10; y <= 10; y++) 
			{
				Tilia::Renderer::Submit(m_ShaderForSquare, m_VertexArrayForSquare, squareScale * glm::translate(glm::mat4(1.0f), glm::vec3(x + distBetweenSquares * x, y + distBetweenSquares * y, 0.0f)));
			}
		}
		//Tilia::Renderer::Submit(m_ShaderForTriangle, m_VertexArrayForTriangle);

		Tilia::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Tilia::Event& event) override
	{
		Tilia::EventDispatcher dispatxher(event);
		dispatxher.Dispatch<Tilia::KeyPressedEvent>(TL_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Tilia::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == TL_KEY_R) {
			m_CameraPosition = { 0.0f, 0.0f, 0.0f };
			m_CameraRotation = 0;
		}

		return false;
	}

private:

	std::shared_ptr<Tilia::Shader> m_ShaderForTriangle;
	std::shared_ptr<Tilia::Shader> m_ShaderForSquare;

	std::shared_ptr<Tilia::VertexArray> m_VertexArrayForTriangle;
	std::shared_ptr<Tilia::VertexArray> m_VertexArrayForSquare;

	Tilia::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 3.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f;

	float m_squareScale = 0.4f;
};

class Sandbox : public Tilia::Application 
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

Tilia::Application* Tilia::CreateApplication()
{
	return new Sandbox();
}