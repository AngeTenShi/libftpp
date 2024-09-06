#include "thread.hpp"
#include "thread_safe_iostream.hpp"

Thread::Thread(const std::string &name, std::function<void()> functToExecute) : _name(name), _functToExecute(functToExecute)
{
}

void Thread::start()
{
	_thread = std::thread([this]() {
		auto str = _name + " ";
		threadSafeCout.setPrefix(str);
		_functToExecute();
	});
}

void Thread::stop()
{
	if (_thread.joinable())
		_thread.join();
}
