#pragma once

#include <memory>
#include "CLI.hh"

class ITask
{
public:
	ITask(std::shared_ptr<DgSample::CLI>& cli);
	virtual ~ITask() = default;
	
	virtual void Run() = 0;
protected:
	std::shared_ptr<DgSample::CLI> m_CLI;
};