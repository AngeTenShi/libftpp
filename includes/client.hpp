#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <functional>
#include "message.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <map>

class Client
{
	private:
		int _socket;
		std::unordered_map<Message::Type, std::function<void(const Message& msg)>> _actions;
		std::vector<Message> _received_messages;
	public:
		~Client();
		void connect(const std::string& address, const size_t& port);
		void disconnect();
		void defineAction(const Message::Type &messageType, const std::function<void(const Message& msg)>& action);
		void send(const Message& message);
		void update();

};

#endif
