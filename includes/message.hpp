#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <sstream>

class Message
{
	public:
		Message(int type);
		~Message() = default;
		int type() const;
		template <typename T>
		Message &operator<<(const T &data)
		{
			_data << data;
			return *this;
		}
		template <typename T>
		Message &operator>>(T &data)
		{
			_data >> data;
			return *this;
		}
	private:
		int _type;
		std::stringstream _data;
};

#endif
