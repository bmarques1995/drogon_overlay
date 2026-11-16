#include "ITask.hh"

ITask::ITask(std::shared_ptr<DgSample::CLI>& cli) :
	m_CLI{cli}
{
}
