#include "message.h"

hyperledger::network::message::message(int _message_type, std::map<std::string,std::string> _parameters, std::string _signature, int _delay)
{
	this->_message_type = _message_type;
	this->_parameters = _parameters;
	this->_signature = _signature;
	this->_delay = _delay;
}

hyperledger::network::message::message(int _message_type, int _signature, int _delay, int _message_id, int _message_from)
{
	this->_message_type = _message_type;
	this->_signature = "Message " + std::to_string(_signature) + " signature";
	this->_delay = _delay;
	this->_message_id = _message_id;
	this->_message_from = _message_from;
}

hyperledger::network::message::message()
{

}

hyperledger::network::message::~message()
{

}

int hyperledger::network::message::get_message_type() const
{
	return this->_message_type;
}

void hyperledger::network::message::set_message_type(int val)
{
	this->_message_type = val;
}

std::map<std::string,std::string> hyperledger::network::message::get_parameters() const
{
	return this->_parameters;
}

void hyperledger::network::message::set_parameters(std::map<std::string,std::string> val)
{
	this->_parameters = val;
}

std::string hyperledger::network::message::get_signature() const
{
	return this->_signature;
}

void hyperledger::network::message::set_signature(std::string val)
{
	this->_signature = val;
}

int hyperledger::network::message::get_delay() const
{
	return this->_delay;
}

void hyperledger::network::message::set_delay(int val)
{
	this->_delay = val;
}

int hyperledger::network::message::get_message_id() const
{
	return this->_message_id;
}

void hyperledger::network::message::set_message_id(int val)
{
	this->_message_id = val;
}

int hyperledger::network::message::get_message_from() const
{
	return this->_message_from;
}


void hyperledger::network::message::set_message_from(int val)
{
	this->_message_from = val;
}

std::ostream& hyperledger::network::operator<<(std::ostream& os, const hyperledger::network::message& _message)
{
	switch (_message.get_message_type())
	{
	case 5:
		os << "Message ID: " << _message.get_message_id() << ", Message type: REQUEST";
		break;
	case 4:
		os << "Message ID: " << _message.get_message_id() << ", Message type: PRE-PREPARE" << ", Message from node: " << _message.get_message_from();
		break;
	case 3:
		os << "Message ID: " << _message.get_message_id() << ", Message type: PREPARE" << ", Message from node: " << _message.get_message_from();
		break;
	case 2:
		os << "Message ID: " << _message.get_message_id() << ", Message type: COMMIT" << ", Message from node: " << _message.get_message_from();
		break;
	case 1:
		os << "Message ID: " << _message.get_message_id() << ", Message type: REPLY";
		break;
	default:
		os << "Message: unknown";
		break;
	}

	return os;
}