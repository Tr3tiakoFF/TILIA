#include <Tilia.h>

#include "imgui/imgui.h"

class ExampleLayer : public Tilia::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}
	
	void OnUpdate() override
	{
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Tilia::Event& event) override
	{
	}
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