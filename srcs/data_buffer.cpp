#include "data_buffer.hpp"

DataBuffer& DataBuffer::operator<<(const std::string& str)
	{
		size_t length = str.size();
		*this << length;
		_buffer.insert(_buffer.end(), str.begin(), str.end());
		return *this;
	}

DataBuffer& DataBuffer::operator>>(std::string& str)
{
	size_t length;
	*this >> length; // Deserialize the length

	if (_buffer.size() < length) {
		throw std::runtime_error("There are no more objects to deserialize");
	}

	str.assign(_buffer.begin(), _buffer.begin() + length); // Deserialize string data
	_buffer.erase(_buffer.begin(), _buffer.begin() + length);
	return *this;
}
