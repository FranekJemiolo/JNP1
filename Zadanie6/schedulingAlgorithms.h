#ifndef _SCHEDULINGALGORITHMS_H_
#define _SCHEDULINGALGORITHMS_H_

#include "process.h"
#include <vector>
#include <set>
#include <memory>

typedef long long time_type;

class SchedulingAlgorithm
{
	public:
		SchedulingAlgorithm() {}
		virtual void setTasks(std::shared_ptr<std::vector<std::shared_ptr<Process>>> tasks) {}
		virtual std::shared_ptr<Process> decide() {}
};

// First Come First Served.
class FCFS : public SchedulingAlgorithm
{
	private:
		std::shared_ptr<std::vector<std::shared_ptr<Process>>> tasks;
		std::vector<std::shared_ptr<Process>>::iterator position;
	public:
		FCFS();
		void setTasks(std::shared_ptr<std::vector<std::shared_ptr<Process>>> tasks);
		std::shared_ptr<Process> decide();
};

// Round Robin.
class RR : public SchedulingAlgorithm
{
	private:
		std::set<std::shared_ptr<Process>> tasks;
		std::set<std::shared_ptr<Process>>::iterator position;
		time_type quantum;
		time_type quantum_left;
	public:
		RR(time_type quantum);
		void setTasks(std::shared_ptr<std::vector<std::shared_ptr<Process>>> tasks);
		std::shared_ptr<Process> decide();
};

// Shortest Job First
class SJF : public SchedulingAlgorithm
{
	private:
		std::set<std::shared_ptr<Process>> tasks;
	public:
		SJF();
		void setTasks(std::shared_ptr<std::vector<std::shared_ptr<Process>>> tasks);
		std::shared_ptr<Process> decide();
};

#endif
