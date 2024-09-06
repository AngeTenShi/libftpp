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
		const Message &operator>>(int &data) const
		{
			auto str = _data.str();
			try {
				data = std::stoi(str);
			} catch (const std::exception &e) {
				data = 0;
			}
			return *this;
		}

		typedef int Type;
	private:
		int _type;
		std::stringstream _data;
};

#endif
