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
		if (Tilia::Input::IsKeyPressed(TL_KEY_TAB))
			TL_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Tilia::Event& event) override
	{
		if (event.GetEventType() == Tilia::EventType::KeyPressed)
		{
			Tilia::KeyPressedEvent& e = (Tilia::KeyPressedEvent&)event;
			if(e.GetKeyCode() == TL_KEY_TAB)
				TL_TRACE("Tab key is pressed (event)!");
			TL_TRACE("{0}", (char)e.GetKeyCode());
		}
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