#ifndef OBSERVER_HPP
# define OBSERVER_HPP

#include <map>
#include <vector>
#include <functional>
#include <iostream>

template <typename TEvent>
class Observer
{
	public:
		void	subscribe(const TEvent& event, const std::function<void()>& lambda)
		{
			_subscribers[event].push_back(lambda);
		}
		void notify(const TEvent &event)
		{
			if (_subscribers.find(event) == _subscribers.end())
				std::cout << "None" << std::endl;
			for (auto &f: _subscribers[event])
			{
				f();
			}
		}
	private:
		std::map<TEvent, std::vector<std::function<void()>>> _subscribers;
};

#endif
