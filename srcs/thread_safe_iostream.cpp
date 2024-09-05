#include "thread_safe_iostream.hpp"

void ThreadSafeIOStream::setPrefix(const std::string &prefix) {
	std::lock_guard<std::mutex> lock(_mutex);
	_prefix = prefix;
}

ThreadSafeIOStream& ThreadSafeIOStream::operator<<(std::ostream& (*manip)(std::ostream&)) {
		std::lock_guard<std::mutex> lock(_mutex);
		std::fwrite(_prefix.c_str(), 1, _prefix.size(), stdout);
		_buffer << manip;
		std::fwrite(_buffer.str().c_str(), 1, _buffer.str().size(), stdout);
		_buffer.str("");
		return *this;
	}
