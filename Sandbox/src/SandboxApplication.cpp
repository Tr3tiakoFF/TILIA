#include <Tilia.h>

class Sandbox : public Tilia::Application 
{
public:
	Sandbox() {}
	~Sandbox() {}
};

Tilia::Application* Tilia::CreateApplication()
{
	return new Sandbox();
}