#include <memory>
#include <set>
#include <vector>
 
#include "schedulingAlgorithms.h"


/* ========================================================================= *
                          First Come First Served
 * ========================================================================= */
 
FCFS::FCFS() {}

void FCFS::setTasks(std::shared_ptr<std::vector<std::shared_ptr<Process>>> tasks) {
	this->tasks = tasks;
	position = (*tasks).begin();
}

std::shared_ptr<Process> FCFS::decide() {
	if (position == (*tasks).end()) 
		return nullptr;
	while (!(*position)->get_size()) {
		position++;
		if (position == (*tasks).end())
			return nullptr;
	}
	return *position;
}


/* ========================================================================= *
                               Round Robin
 * ========================================================================= */
 
RR::RR(time_type quantum) {
	this->quantum = quantum;
}

void RR::setTasks(std::shared_ptr<std::vector<std::shared_ptr<Process>>> tasks) {
	for (auto it = (*tasks).begin(); it != (*tasks).end(); it++)
		if ((*it)->get_size())
			this->tasks.insert(*it);
	position = this->tasks.begin();
	quantum_left = quantum;
}

std::shared_ptr<Process> RR::decide() {
	if (tasks.empty()) 
		return nullptr;
	if (!(*position)->get_size()) {
		quantum_left = quantum;
		tasks.erase(position++);
	}
	else if (!quantum_left) {
		quantum_left = quantum;
		position++;
	}
	if (position == tasks.end())
		position = tasks.begin();
	if (tasks.empty())
		return nullptr;
	quantum_left--;
	return *position;
}

/* ========================================================================= *
                           Shortest Job First
 * ========================================================================= */
 
SJF::SJF() {}

void SJF::setTasks(std::shared_ptr<std::vector<std::shared_ptr<Process>>> tasks) {
	for (auto it = (*tasks).begin(); it != (*tasks).end(); it++)
		this->tasks.insert(*it);
}

std::shared_ptr<Process> SJF::decide() {
	bool found = false;
	while (!found) {
		if (tasks.begin() == tasks.end())
			return nullptr;
		if (!(*tasks.begin())->get_size())
			tasks.erase(tasks.begin());
		else 
			found = true;
	}
	return *(tasks.begin());
}
