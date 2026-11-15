#pragma once

#include "ServerExport.hh"
#include <drogon/drogon.h>

namespace DgSample
{
	class SERVER_API Application
	{
	public:
		Application();
		Application(std::string jsonFile);
		~Application();

		static Application* GetInstance();
		void Run();
		
	private:
		static void EnableSingleton(Application* app);
		static void DisableSingleton();

		void InitRoutine();
		void LogAddress();

		static Application* s_Instance;
		Json::Value m_Config;
	};
}