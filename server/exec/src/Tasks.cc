#include "Tasks.hh"
#include "Application.hh"

RunTask::RunTask(std::shared_ptr<DgSample::CLI>& cli) :
	ITask(cli)
{
}

void RunTask::Run()
{
	DgSample::Application* app = new DgSample::Application(m_CLI);
	app->Run();
	delete app;
}

HelpTask::HelpTask(std::shared_ptr<DgSample::CLI>& cli) :
	ITask(cli)
{}

void HelpTask::Run()
{}

AdminTask::AdminTask(std::shared_ptr<DgSample::CLI>& cli) :
	ITask(cli)
{}

void AdminTask::Run()
{}