#include "packet.h"

hyperledger::network::packet::packet(int _destination, std::string _hash, int _latency, hyperledger::network::message _message, int _source)
{
	this->_destination = _destination;
	this->_hash = _hash;
	this->_latency = _latency;
	this->_message = _message;
	this->_source = _source;
}

hyperledger::network::packet::packet()
{

}

hyperledger::network::packet::~packet()
{

}

int hyperledger::network::packet::get_destination() const
{
	return this->_destination;
}

void hyperledger::network::packet::set_destination(int val)
{
	this->_destination = val;
}

std::string hyperledger::network::packet::get_hash() const
{
	return this->_hash;
}

void hyperledger::network::packet::set_hash(std::string val)
{
	this->_hash = val;
}

int hyperledger::network::packet::get_latency() const
{
	return this->_latency;
}

void hyperledger::network::packet::set_latency(int val)
{
	this->_latency = val;
}

hyperledger::network::message hyperledger::network::packet::get_message() const
{
	return this->_message;
}

void hyperledger::network::packet::set_message(hyperledger::network::message val)
{
	this->_message = val;
}

int hyperledger::network::packet::get_source() const
{
	return this->_source;
}

void hyperledger::network::packet::set_source(int val)
{
	this->_source = val;
}

hyperledger::network::node_delay::node_delay(int id, int delay)
{
	this->node_id = id;
	this->delay_ms = delay;
}

hyperledger::network::node_delay::node_delay()
{

}