#include "Application.hh"
#include "Tasks.hh"

int main(int argc, char** argv)
{
	try
	{
		auto cli = std::make_shared<DgSample::CLI>(argc, argv);
		std::unordered_map<DgSample::Command, std::shared_ptr<ITask>> tasks =
		{
			{ DgSample::Command::DG_RUN, std::make_shared<RunTask>(cli) },
			{ DgSample::Command::DG_HELP, std::make_shared<HelpTask>(cli) },
			{ DgSample::Command::DG_ADMIN, std::make_shared<AdminTask>(cli) }
		};
		auto it = tasks.find(cli->GetCommand());
		if (it != tasks.end())
			it->second->Run();
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
	}

    return 0;
}