#include <Tilia.h>

class ExampleLayer : public Tilia::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}
	
	void OnUpdate() override
	{
		TL_INFO("ExampleLayer::Update");
	}

	void OnEvent(Tilia::Event& event) override
	{
		TL_TRACE("{0}", event);
	}
};

class Sandbox : public Tilia::Application 
{
public:
	Sandbox() 
	{
		//PushLayer(new Tilia::ImGuiLayer());
		//PushLayer(new ExampleLayer());
		PushOverlay(new Tilia::ImGuiLayer());
	}
	~Sandbox() {}
};

Tilia::Application* Tilia::CreateApplication()
{
	return new Sandbox();
}