#pragma once

#include "ITask.hh"

class RunTask : public ITask 
{
public:
	RunTask(std::shared_ptr<DgSample::CLI>& cli);
	~RunTask() = default;

	void Run() override;
};

class HelpTask : public ITask
{
public:
	HelpTask(std::shared_ptr<DgSample::CLI>& cli);
	~HelpTask() = default;

	void Run() override;
};

class AdminTask : public ITask
{
public:
	AdminTask(std::shared_ptr<DgSample::CLI>& cli);
	~AdminTask() = default;

	void Run() override;
};