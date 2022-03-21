#pragma once

#ifdef TL_PLATFORM_WINDOWS

extern Tilia::Application* Tilia::CreateApplication();

int main(int argc, char** argv)
{
	Tilia::Log::Init();
	TL_CORE_INFO("Initialized Log!");

	auto application = Tilia::CreateApplication();
	application->Run();
	delete application;
}

#endif