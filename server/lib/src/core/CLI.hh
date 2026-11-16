#pragma once

#include "ServerExport.hh"

#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>

namespace DgSample
{
	enum class Command : uint16_t
	{
		DG_NONE,
		DG_RUN,
		DG_HELP,
		DG_ADMIN
	};

	class SERVER_API CLI
	{
	public:
		CLI(int argc, char** argv);
		~CLI();

		const std::string& GetExecutable() const;
		const Command GetCommand() const;
		const std::string& GetArgument(std::string arg);

	private:
		//std::vector<std::string> m_CLIArgs;
		std::string m_ExecName;
		Command m_Command;
		std::unordered_map<std::string, std::string> m_Args;

		void EvaluateArguments(const std::vector<std::string>& args);
		void EvaluateDefaults();

		void ProcessCommand(std::vector<std::string>::const_iterator element);
		bool ProcessOption(std::vector<std::string>::const_iterator first, std::vector<std::string>::const_iterator second);

		static const std::unordered_map<std::string, Command> s_Commands;
		static const std::unordered_map<std::string, bool> s_Options;
	};
}