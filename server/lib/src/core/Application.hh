#pragma once

#include "ServerExport.hh"
#include <drogon/drogon.h>
#include "CLI.hh"
#include <memory>

namespace DgSample
{
	class SERVER_API Application
	{
	public:
		Application(std::shared_ptr<CLI> cli);
		~Application();

		static Application* GetInstance();
		void Run();
		
	private:
		static void EnableSingleton(Application* app);
		static void DisableSingleton();

		void InitRoutine();
		void LogAddress();
		void InitApp();

		static Application* s_Instance;
		Json::Value m_Config;
		std::shared_ptr<CLI> m_CLI;
	};
}