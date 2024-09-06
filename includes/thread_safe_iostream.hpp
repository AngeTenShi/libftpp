#ifndef THREAD_SAFE_IOSTREAM_HPP
#define THREAD_SAFE_IOSTREAM_HPP

#pragma once

#include <mutex>
#include <sstream>
#include <string>
#include <ostream>

extern std::mutex coutMutex;

class ThreadSafeIOStream {
private:
	std::string _prefix;
	std::ostringstream _buffer;

public:

	void setPrefix(const std::string& prefix);

	template <typename T>
	ThreadSafeIOStream& operator<<(const T& value) {
		_buffer << value;
		return *this;
	}

	ThreadSafeIOStream& operator<<(std::ostream& (*manip)(std::ostream&));

	template <typename T>
	ThreadSafeIOStream& operator>>(const T& value) {
		_buffer >> value;
		return *this;
	}

	void flush();
};

extern thread_local ThreadSafeIOStream threadSafeCout;

#endif
