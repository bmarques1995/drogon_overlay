#include "Application.hh"
#include "Register.hh"

DgSample::Application* DgSample::Application::s_Instance = nullptr;

DgSample::Application::Application(std::shared_ptr<CLI> cli) :
	m_CLI{cli}
{
	InitRoutine();
	InitApp();
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

void DgSample::Application::InitApp()
{
	auto& app = drogon::app();
	std::string jsonFile = m_CLI->GetArgument("config");
	if (jsonFile == "")
		throw std::runtime_error("Missing drogon json config file");
	app.loadConfigFile(jsonFile);
	m_Config = app.getCustomConfig();
}
