#ifndef THREAD_SAFE_IOSTREAM_HPP
#define THREAD_SAFE_IOSTREAM_HPP

#include <mutex>
#include <sstream>
#include <string>
#include <iostream>
#include <ostream>

class ThreadSafeIOStream {
private:
	std::mutex _mutex;
	std::string _prefix;
	std::ostringstream _buffer;

public:
	void setPrefix(const std::string& prefix);

	template <typename T>
	ThreadSafeIOStream& operator<<(const T& value) {
		std::lock_guard<std::mutex> lock(_mutex);
		_buffer << value;
		return *this;
	}
	ThreadSafeIOStream& operator<<(std::ostream& (*manip)(std::ostream&));
	template <typename T>
	ThreadSafeIOStream& operator>>(const T& value)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_buffer >> value;
		return *this;
	}
};

extern thread_local ThreadSafeIOStream threadSafeIOStream;

#endif
