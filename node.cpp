#include "node.h"

hyperledger::server::node::node(std::vector<hyperledger::network::message> _message_que, int _node_id, std::vector<int> _number_signatures, std::string _signature)
{
	this->_message_que = _message_que;
	this->_node_id = _node_id;
	this->_number_signatures = _number_signatures;
	this->_signature = _signature;
}

hyperledger::server::node::node(int _node_id, int _signatures_required)
{
	this->_node_id = _node_id;
	this->_signatures_required = _signatures_required;
}

hyperledger::server::node::node()
{

}

hyperledger::server::node::~node()
{

}

std::vector<hyperledger::network::message> hyperledger::server::node::get_message_que() const
{
	return this->_message_que;
}

void hyperledger::server::node::set_message_que(std::vector<hyperledger::network::message> val)
{
	this->_message_que = val;
}

int hyperledger::server::node::get_node_id() const
{
	return this->_node_id;
}

void hyperledger::server::node::set_node_id(int val)
{
	this->_node_id = val;
}

std::vector<int> hyperledger::server::node::get_number_signatures() const
{
	return this->_number_signatures;
}

void hyperledger::server::node::set_number_signatures(std::vector<int> val)
{
	this->_number_signatures = val;
}

std::string hyperledger::server::node::get_signature() const
{
	return this->_signature;
}

void hyperledger::server::node::set_signature(std::string val)
{
	this->_signature = val;
}

std::vector<hyperledger::network::node_delay> hyperledger::server::node::get_latencies() const
{
	return this->_latencies;
}

void hyperledger::server::node::set_latencies(std::vector<hyperledger::network::node_delay> val)
{
	this->_latencies = val;
}

void hyperledger::server::node::append_latencies(hyperledger::network::node_delay val)
{
	this->_latencies.push_back(val);
}

std::ostream& hyperledger::server::operator<<(std::ostream& os, const hyperledger::server::node& _node)
{
	for (size_t i = 0; i < _node._latencies.size(); i++)
	{
		os << "ID: " << _node._latencies[i].node_id << " Delay: " << _node._latencies[i].delay_ms << " [ms]" << std::endl;
	}
	return os;
}

std::vector<hyperledger::network::message> hyperledger::server::node::get_temp_message_que() const
{
	return this->_temp_message_que;
}

void hyperledger::server::node::set_temp_message_que(std::vector<hyperledger::network::message> val)
{
	this->_temp_message_que = val;
}


void hyperledger::server::node::write_to_file(hyperledger::network::message val)
{
	std::ofstream file;
	file.open("file_node_" + std::to_string(this->_node_id)+".txt", std::ios_base::app);
	file << "Time: " << this->_node_time << " [ms], " << val << std::endl;
	file.close();
}