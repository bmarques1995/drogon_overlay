#pragma once

#ifdef SERVER_WIN_EXPORT
	#define SERVER_API __declspec(dllexport)
#elif defined(SERVER_WIN_IMPORT)
	#define SERVER_API __declspec(dllimport)
#else
	#define SERVER_API
#endif