#ifndef PERSISTENT_WORKER_HPP
#define PERSISTENT_WORKER_HPP

#include <string>
#include <functional>
#include <thread>
#include <vector>
#include <iostream>

class PersistentWorker
{
	public:
		class Task {
			private:
				std::string _name;
				std::function<void()> _task;
			public:
				Task(std::string name, std::function<void()> task) : _name(name), _task(task) {}
				std::string getName() const;
				std::function<void()> getTask();
		};
		void addTask(const std::string &name, const std::function<void()> &jobToExecute);
		void removeTask(const std::string &name);
		PersistentWorker();
		~PersistentWorker();
	private:
		std::vector<Task> _tasks;
		std::thread _workerThread;
		void worker();
};

#endif
