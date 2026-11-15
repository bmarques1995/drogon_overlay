#include "Application.hh"
#include "Register.hh"

DgSample::Application* DgSample::Application::s_Instance = nullptr;

DgSample::Application::Application()
{
	InitRoutine();
	LogAddress();
}

DgSample::Application::Application(std::string jsonFile)
{
	InitRoutine();

	auto& app = drogon::app();
	app.loadConfigFile(jsonFile);
	m_Config = app.getCustomConfig();
	LogAddress();
}

DgSample::Application::~Application()
{
	DisableSingleton();
	drogon::app().quit();
}

DgSample::Application* DgSample::Application::GetInstance()
{
	return s_Instance;
}

void DgSample::Application::Run()
{
	drogon::app().run();
}

void DgSample::Application::EnableSingleton(Application* app)
{
	s_Instance = app;
}

void DgSample::Application::DisableSingleton()
{
	s_Instance = nullptr;
}

void DgSample::Application::InitRoutine()
{
	if (s_Instance == nullptr)
		EnableSingleton(this);
	else
		return;
	DgSample::Register::RegisterControllers();
}

void DgSample::Application::LogAddress()
{
	drogon::app().registerBeginningAdvice([]()
	{
		auto listeners = drogon::app().getListeners();

		for (const auto& listener : listeners)
		{
			LOG_INFO << "Server running at : " << listener.toIp() << ":" << listener.toPort() << "\n";
		}
	});
}
