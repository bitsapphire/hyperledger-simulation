#include "node.h"

std::vector<hyperledger::network::message> hyperledger::server::node::message_responses(int time_step_ms)
{
	this->_node_time += time_step_ms;

	std::vector<hyperledger::network::message> ret;

	for (auto m : this->_message_que)
	{
		m.set_delay(m.get_delay() - time_step_ms);
	}

	for (size_t i = 0; i < this->_temp_message_que.size(); i++)
	{
		_temp_message_que[i].set_delay(_temp_message_que[i].get_delay() - time_step_ms);

		if (_temp_message_que[i].get_delay() <= 0)
		{
			write_to_file(_temp_message_que[i]);

			if (_temp_message_que[i].get_message_type() == 3)
			{
				bool exists = false;
				bool temp_id = 0;

				for (size_t m = 0; m < this->_message_que.size(); m++)
				{
					if (_temp_message_que[i].get_message_id() == _message_que[m].get_message_id())
					{
						temp_id = m;
						exists = true;
					}
				}

				if (exists)
				{
					_number_signatures[temp_id]++;
				}
			}

			_temp_message_que.erase(_temp_message_que.begin() + i);

			i--;
		}
	}



	for (size_t i = 0; i < this->_message_que.size(); i++)
	{
		_message_que[i].set_delay(_message_que[i].get_delay() - time_step_ms);

		if (_message_que[i].get_delay() <= 0)
		{
			if (_message_que[i].get_message_type() == 1)
			{

				_message_que.erase(_message_que.begin() + i);

				_number_signatures.erase(_number_signatures.begin() + i);

				i--;
			}

			else if (_message_que[i].get_message_type() == 2) //reply
			{

				_message_que[i].set_message_type(1);
				 
				hyperledger::network::message temp_mes;

				temp_mes.set_message_from(-1);

				temp_mes.set_message_id(_message_que[i].get_message_id());

				temp_mes.set_message_type(1);

				temp_mes.set_signature(std::to_string(this->_node_id));

				temp_mes.set_delay(0);

				this->_temp_message_que.push_back(temp_mes);

			}

			else if (_message_que[i].get_message_type() == 3) //commit
			{
				if (this->_number_signatures[i] >= this->_signatures_required)
				{
					_message_que[i].set_message_type(2);

					hyperledger::network::message temp_mes;

					temp_mes.set_message_from(this->get_node_id());

					temp_mes.set_message_id(_message_que[i].get_message_id());

					temp_mes.set_message_type(2);

					temp_mes.set_signature(std::to_string(this->_node_id));

					ret.push_back(temp_mes);
				}
			}

			else if (_message_que[i].get_message_type() == 4) //prepare
			{
				_message_que[i].set_message_type(3);

				hyperledger::network::message temp_mes;

				temp_mes.set_message_from(this->get_node_id());

				temp_mes.set_message_id(_message_que[i].get_message_id());

				temp_mes.set_message_type(3);

				temp_mes.set_signature(std::to_string(this->_node_id));

				ret.push_back(temp_mes);

			}

			else if (_message_que[i].get_message_type() == 5) //pre-prepare
			{

				_message_que[i].set_message_type(4);

				//if (this->_node_id == 0) //Master node
				//{
					
					hyperledger::network::message temp_mes;
					
					temp_mes.set_message_from(this->get_node_id());
					
					temp_mes.set_message_id(_message_que[i].get_message_id());
					
					temp_mes.set_message_type(4);
					
					temp_mes.set_signature(std::to_string(this->_node_id));
					
					ret.push_back(temp_mes);

				//}
			}
		}
	}

	return ret;
}