#include "node.h"

void hyperledger::server::node::accept_message(hyperledger::network::message val)
{
	bool exists;

	bool exists_id;

	switch (val.get_message_type())
	{
	case 5:
		this->_message_que.push_back(val);
		this->_number_signatures.push_back(0);
		this->_temp_message_que.push_back(val);
		break;
	case 4:
		exists = false;
		for (auto m : _message_que)
		{
			if (m.get_message_id() == val.get_message_id())
			{
				exists = true;
			}
		}
		if (exists)
		{
			_temp_message_que.push_back(val);
		}
		else
		{
			this->_message_que.push_back(val);
			this->_number_signatures.push_back(0);
		}
		break;
	case 3:
		exists = false;
		exists_id = 0;
		for (size_t i = 0; i < _message_que.size(); i++)
		{
			if (_message_que[i].get_message_id() == val.get_message_id())
			{
				exists = true;
				exists_id = i;
			}
		}
		if (exists)
		{
			_temp_message_que.push_back(val);
			//_number_signatures[exists_id]++;
		}
		break;
	case 2:
		_temp_message_que.push_back(val);
		break;
	case 1:
		
		break;
	default:
		break;
	}
}