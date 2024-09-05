#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <mutex>
#include <queue>

template <typename TType>
class ThreadSafeQueue
{
	private:
		std::queue<TType> _queue;
		std::mutex _mutex;

	public:
		void push_back(const TType &new_element)
		{
			std::lock_guard<std::mutex> lock(_mutex);
			_queue.push(new_element);
		}
		void push_front(const TType &new_element)
		{
			std::lock_guard<std::mutex> lock(_mutex);
			if (_queue.empty())
			{
				_queue.push(new_element);
				return;
			}
			std::queue<TType> tmp;
			tmp.push(new_element);
			while (!_queue.empty())
			{
				tmp.push(pop_front());
			}
			_queue = tmp;
		}
		TType pop_back()
		{
			std::lock_guard<std::mutex> lock(_mutex);
			if (_queue.empty())
				throw std::runtime_error("Queue is empty");
			std::queue<TType> tmp;
			while (_queue.size() > 1)
			{
				tmp.push(pop_front());
			}
			TType element = _queue.front();
			_queue = tmp;
			return (element);
		}
		TType pop_front()
		{
			std::lock_guard<std::mutex> lock(_mutex);
			if (_queue.empty())
				throw std::runtime_error("Queue is empty");
			TType element = _queue.front();
			_queue.pop();
			return element;
		}
};

#endif
