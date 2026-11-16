#include "CLI.hh"
#include <filesystem>

using fs_path = std::filesystem::path;

const std::unordered_map<std::string, DgSample::Command> DgSample::CLI::s_Commands = 
{
	{ "run", DgSample::Command::DG_RUN },
	{ "help", DgSample::Command::DG_HELP },
	{ "admin", DgSample::Command::DG_ADMIN }
};

const std::unordered_map<std::string, bool> DgSample::CLI::s_Options =
{
	{ "config", true },
	{ "verbose", false}
};

DgSample::CLI::CLI(int argc, char** argv)
{
	std::vector<std::string> cliArgs;
	cliArgs.reserve((size_t)argc - 1);
	for (size_t i = 1; i < argc; i++)
	{
		cliArgs.push_back(argv[i]);
	}

	fs_path path(argv[0]);
	m_ExecName = path.filename().stem().string();
	m_Command = Command::DG_NONE;
	EvaluateDefaults();
	EvaluateArguments(cliArgs);
#warning "clang-cl debug"
	auto debug = this;
}

DgSample::CLI::~CLI()
{

}

const std::string& DgSample::CLI::GetExecutable() const
{
	return m_ExecName;
}

const DgSample::Command DgSample::CLI::GetCommand() const
{
	return m_Command;
}


const std::string& DgSample::CLI::GetArgument(std::string arg)
{
	static const std::string empty = "";
	auto it = m_Args.find(arg);
	return it != m_Args.end() ? it->second : empty;
}

void DgSample::CLI::EvaluateArguments(const std::vector<std::string>& args)
{
	for (auto it = args.begin(); it != args.end(); it++)
	{
		if (it->starts_with("--"))
		{
			if ((it + 1) == args.end())
				throw std::runtime_error("Options must provide one value");
			if (ProcessOption(it, it + 1))
				it++;
		}
		else
			ProcessCommand(it);
	}
#pragma warning "clang-cl debug"
	auto debug = this;
}

void DgSample::CLI::EvaluateDefaults()
{
	for (auto it = s_Options.begin(); it != s_Options.end(); it++)
	{
		if (!it->second)
			m_Args[it->first] = "0";
	}
}

void DgSample::CLI::ProcessCommand(std::vector<std::string>::const_iterator element)
{
	auto commandIt = s_Commands.find(*element);
	if (commandIt == s_Commands.end())
		throw std::runtime_error("Command not available");
	if (m_Command != Command::DG_NONE)
		throw std::runtime_error("Only one command is available per execution");
	m_Command = commandIt->second;
}

bool DgSample::CLI::ProcessOption(std::vector<std::string>::const_iterator first, std::vector<std::string>::const_iterator second)
{
	std::string treatedOption = *first;
	treatedOption.erase(0, 2);
	auto optionIt = s_Options.find(treatedOption);
	
	if (optionIt == s_Options.end())
		throw std::runtime_error("Option not available");
	if (optionIt->second)
		m_Args[treatedOption] = *second;
	else
		m_Args[treatedOption] = "1";

	return optionIt->second;
}
