#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class WorkerPool
{
	public:
		class IJob
		{
			public:
				virtual ~IJob() = default;
				virtual void execute() = 0;
		};
		WorkerPool(size_t numThreads);
		~WorkerPool();
		void addJob(std::function<void()> &jobToExecute);

	private:
		std::vector<std::thread> _threads;
		std::queue<std::function<void()>> _jobs;
		std::mutex _jobsMutex;
		std::condition_variable _jobsCondition;
		bool _stop = false;
		void worker();
};

#endif
