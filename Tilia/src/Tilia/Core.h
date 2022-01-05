#pragma once

#ifdef TL_PLATFORM_WINDOWS
	#ifdef TL_BUILD_DLL
		#define TILIA_API __declspec(dllexport)
	#else
		#define TILIA_API __declspec(dllimport)
	#endif
#else 
	#error Tilia only support Windows! (for now)
#endif