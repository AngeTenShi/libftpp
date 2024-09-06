#include "worker_pool.hpp"

WorkerPool::WorkerPool(size_t numThreads) {
	for (size_t i = 0; i < numThreads; ++i) {
		_threads.emplace_back([this]() {
			worker();
		});
	}
}

void WorkerPool::addJob(std::function<void()> &jobToExecute) {
	{
		std::lock_guard<std::mutex> lock(_jobsMutex);
		_jobs.push(jobToExecute);
	}
	_jobsCondition.notify_one();
}

void WorkerPool::worker() {
	while (true) {
		std::function<void()> job;
		{
			std::unique_lock<std::mutex> lock(_jobsMutex);
			_jobsCondition.wait(lock, [this]() {
				return _stop || !_jobs.empty();
			});
			if (_stop && _jobs.empty()) {
				return;
			}
			job = _jobs.front();
			_jobs.pop();
		}
		job();
	}
}

WorkerPool::~WorkerPool() {
	{
		std::lock_guard<std::mutex> lock(_jobsMutex);
		_stop = true;
	}
	_jobsCondition.notify_all();
	for (auto &thread : _threads) {
		thread.join();
	}
}

