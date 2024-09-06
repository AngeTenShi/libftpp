#include "client.hpp"
#include "thread_safe_iostream.hpp"
void Client::connect(const std::string& address, const size_t& port)
{
	 struct sockaddr_in serv_addr;

	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
	{
		std::cerr << "Could not create socket" << std::endl;
		exit(1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if (::connect(_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "Connection failed" << std::endl;
		exit(1);
	}
}

void Client::disconnect()
{
	close(_socket);
	_socket = -1;
}

void Client::defineAction(const Message::Type &messageType, const std::function<void(const Message& msg)>& action)
{
	_actions[messageType] = action;
}

void Client::send(const Message& message)
{
	// TODO
}

void Client::update()
{
	for(auto &msg: _received_messages)
	{
		_actions[msg.type()](msg);
	}
}

Client::~Client()
{
	if (_socket != -1)
	{
		close(_socket);
	}
}
