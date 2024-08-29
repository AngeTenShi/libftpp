#ifndef DATA_BUFFER_HPP
#define DATA_BUFFER_HPP

#include <vector>
#include <stdexcept>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>

class DataBuffer {
public:
	DataBuffer() = default;
	~DataBuffer() = default;

	// serialize trivially copyable types using std::memcpy
	template <typename T>
	typename std::enable_if<std::is_trivially_copyable<T>::value, DataBuffer&>::type
	operator<<(const T& object)
	{
		const uint8_t* data = reinterpret_cast<const uint8_t*>(&object);
		_buffer.insert(_buffer.end(), data, data + sizeof(T));
		return *this;
	}

	// deserialize trivially copyable types using std::memcpy
	template <typename T>
	typename std::enable_if<std::is_trivially_copyable<T>::value, DataBuffer&>::type
	operator>>(T& object)
	{
		if (_buffer.size() < sizeof(T)) {
			throw std::runtime_error("There are no more objects to deserialize");
		}
		std::memcpy(&object, _buffer.data(), sizeof(T));
		_buffer.erase(_buffer.begin(), _buffer.begin() + sizeof(T));
		return *this;
	}

	DataBuffer& operator<<(const std::string& str)
	{
		size_t length = str.size();
		*this << length;
		_buffer.insert(_buffer.end(), str.begin(), str.end());
		return *this;
	}

	DataBuffer& operator>>(std::string& str)
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

private:
	std::vector<uint8_t> _buffer;
};

#endif
