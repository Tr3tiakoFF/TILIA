#pragma once

#ifdef TL_PLATFORM_WINDOWS

extern Tilia::Application* Tilia::CreateApplication();

int main(int argc, char** argv)
{
	auto application = Tilia::CreateApplication();
	application->Run();
	delete application;
}

#endif