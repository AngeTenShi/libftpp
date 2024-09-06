#include "persistent_worker.hpp"

std::string PersistentWorker::Task::getName() const {
	return _name;
}

std::function<void()> PersistentWorker::Task::getTask() {
	return _task;
}

void PersistentWorker::addTask(const std::string &name, const std::function<void()> &jobToExecute) {
	_tasks.emplace_back(name, jobToExecute);
}

void PersistentWorker::removeTask(const std::string &name)
{
	if (_tasks.empty())
		return;
	_tasks.erase(std::remove_if(_tasks.begin(), _tasks.end(), [&](const Task& task) {
		return task.getName() == name;
	}), _tasks.end());
}

void PersistentWorker::worker() {
	while (true) {
		for (auto &task : _tasks) {
			task.getTask()();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

PersistentWorker::PersistentWorker() {
	_workerThread = std::thread(&PersistentWorker::worker, this);
}

PersistentWorker::~PersistentWorker() {
	_workerThread.join();
}
