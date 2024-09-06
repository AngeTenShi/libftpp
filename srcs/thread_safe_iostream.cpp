#include "thread_safe_iostream.hpp"


thread_local ThreadSafeIOStream threadSafeCout;
std::mutex globalMutex;

void ThreadSafeIOStream::setPrefix(const std::string &prefix) {
	_prefix = prefix;
}

ThreadSafeIOStream& ThreadSafeIOStream::operator<<(std::ostream& (*manip)(std::ostream&)) {
	_buffer << manip;
	flush();
	return *this;
}

void ThreadSafeIOStream::flush() {
	std::lock_guard<std::mutex> lock(globalMutex);
	std::fwrite(_prefix.c_str(), 1, _prefix.size(), stdout);
	std::fwrite(_buffer.str().c_str(), 1, _buffer.str().size(), stdout);
	_buffer.str("");
}
