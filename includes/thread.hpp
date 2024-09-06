#ifndef THREAD_HPP
#define THREAD_HPP

#include <thread>
#include <string>
#include <functional>

class Thread
{
	private:
		std::string _name;
		std::function<void()> _functToExecute;
		std::thread _thread;

	public:
		Thread(const std::string &name, std::function<void()> functToExecute);
	void start();
	void stop();

};

#endif
