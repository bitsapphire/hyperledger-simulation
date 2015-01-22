#include "pool.h"
#include <iostream>


hyperledger::server::pool::pool(std::vector<hyperledger::server::node> _nodes, int _total_nodes, int _request_cooldown, int _time_step_ms, int _transactions_per_second)
{
	this->_nodes = _nodes;
	this->_total_nodes = _total_nodes;
	this->_request_cooldown = _request_cooldown;
	this->_time_step_ms = _time_step_ms;
	this->_transactions_per_second = _transactions_per_second;
}

hyperledger::server::pool::pool()
{

}

hyperledger::server::pool::~pool()
{

}

std::vector<hyperledger::server::node> hyperledger::server::pool::get_nodes() const
{
	return this->_nodes;
}

void hyperledger::server::pool::set_nodes(std::vector<hyperledger::server::node> val)
{
	this->_nodes = val;
}

int hyperledger::server::pool::get_total_nodes() const
{
	return this->_total_nodes;
}

void hyperledger::server::pool::set_total_nodes(int val)
{
	this->_total_nodes = val;
}

void hyperledger::server::pool::initialize_nodes(int number_of_nodes, bool automatic_fit = true)
{
	std::vector<int> empty_spaces;
	
	int signatures_req = floor((2.0 / 3)*number_of_nodes) + 1;

	if (!automatic_fit)
	{
		throw std::exception::exception("not implemented");
	}
	else
	{
		auto dimension_sqrt = sqrt(number_of_nodes);

		auto mtx_dim = static_cast<int>(round(dimension_sqrt));

		mtx_dim *= 2;

		int *mtx = new int[mtx_dim*mtx_dim];

		while (empty_spaces.size() < (mtx_dim*mtx_dim - number_of_nodes))
		{
			auto R1 = rand() % (mtx_dim*mtx_dim);

			if (std::find(empty_spaces.begin(), empty_spaces.end(), R1) != empty_spaces.end())
			{
				continue;
			}
			else
			{

				empty_spaces.push_back(R1);
			}
		}

		for (size_t i = 0; i < number_of_nodes; i++)
		{
			auto current_node = hyperledger::server::node(i, signatures_req);

			current_node.set_signature("signature_node_"+std::to_string(i));

			this->_nodes.push_back(current_node);
		}

		//for (auto p : this->_nodes)
		//{
		//	std::cout << p.get_signature() << std::endl;
		//}

		int iter = 0; 

		for (size_t i = 0; i < mtx_dim; i++)
		{
			for (size_t j = 0; j < mtx_dim; j++)
			{
				if (std::find(empty_spaces.begin(), empty_spaces.end(), (i + j*mtx_dim)) != empty_spaces.end())
				{
					mtx[j + i*mtx_dim] = -1;
				}
				else
				{
					mtx[j + i*mtx_dim] = _nodes[iter++].get_node_id();
				}
			}
		}
		

		std::random_device rd;

		std::mt19937 gen(rd());

		std::normal_distribution<> normal_low(hyperledger::network::latency::low, 10);

		std::normal_distribution<> normal_medium(hyperledger::network::latency::medium, 10);

		std::normal_distribution<> normal_high(hyperledger::network::latency::high, 10);

		std::normal_distribution<> normal_very_high(hyperledger::network::latency::very_high, 10);



		for (size_t i = 0; i < mtx_dim; i++)
		{
			for (size_t j = 0; j < mtx_dim; j++)
			{
				int linear_position = j + i * mtx_dim;

				if (mtx[linear_position] < 0)
				{
					continue;
				}

				for (size_t inner_i = 0; inner_i < mtx_dim; inner_i++)
				{
					for (size_t inner_j = 0; inner_j < mtx_dim; inner_j++)
					{
						int current_linear_position = inner_j + inner_i * mtx_dim;

						if (current_linear_position <= linear_position)
						{
							continue;
						}

						if (mtx[current_linear_position] <= 0)
						{
							continue;
						}

						auto x = inner_i - i;

						auto y = inner_j - j;

						auto distance = sqrt(x*x + y*y);

						distance = distance / (sqrt(2) * mtx_dim);

						if (distance < 0.25)
						{
							auto delay = static_cast<__int32>(std::round(normal_low(gen)));

							if (delay < 10)
							{
								delay = 10;
							}

							this->_nodes[mtx[linear_position]].append_latencies(hyperledger::network::node_delay(mtx[current_linear_position], delay));

							this->_nodes[mtx[current_linear_position]].append_latencies(hyperledger::network::node_delay(mtx[linear_position], delay));

						}
						else if (distance < 0.50)
						{
							auto delay = static_cast<__int32>(std::round(normal_medium(gen)));

							if (delay < 20)
							{
								delay = 20;
							}

							this->_nodes[mtx[linear_position]].append_latencies(hyperledger::network::node_delay(mtx[current_linear_position], delay));

							this->_nodes[mtx[current_linear_position]].append_latencies(hyperledger::network::node_delay(mtx[linear_position], delay));
						}
						else if (distance < 0.75)
						{
							auto delay = static_cast<__int32>(std::round(normal_high(gen)));

							if (delay < 30)
							{
								delay = 30;
							}

							this->_nodes[mtx[linear_position]].append_latencies(hyperledger::network::node_delay(mtx[current_linear_position], delay));

							this->_nodes[mtx[current_linear_position]].append_latencies(hyperledger::network::node_delay(mtx[linear_position], delay));
						}
						else
						{
							auto delay = static_cast<__int32>(std::round(normal_very_high(gen)));

							if (delay < 40)
							{
								delay = 40;
							}

							this->_nodes[mtx[linear_position]].append_latencies(hyperledger::network::node_delay(mtx[current_linear_position], delay));

							this->_nodes[mtx[current_linear_position]].append_latencies(hyperledger::network::node_delay(mtx[linear_position], delay));
						}
					}
				}
			}
		}

		//for (auto n : _nodes)
		//{
		//	std::cout << "Node: " << n.get_node_id() << std::endl;
		//	std::cout << n << std::endl;
		//}

		this->_mtx_dim = mtx_dim;
		this->_mtx = mtx;
	}
}

int hyperledger::server::pool::get_request_cooldown() const
{
	return this->_request_cooldown;
}

void hyperledger::server::pool::set_request_cooldown(int val)
{
	this->_request_cooldown = val;
}

int hyperledger::server::pool::get_time_step_ms() const
{
	return this->_time_step_ms;
}

void hyperledger::server::pool::set_time_step_ms(int val)
{
	this->_time_step_ms = val;
}

int hyperledger::server::pool::get_transactions_per_second() const
{
	return this->_transactions_per_second;
}

void hyperledger::server::pool::set_transactions_per_second(int val)
{
	this->_transactions_per_second = val;
}


void hyperledger::server::pool::start_pool(int transactions_per_second, int time_step_ms, int time_seconds)
{
	if (this->_nodes.size() < 3)
	{
		//throw std::exception::exception("not enough nodes");
		std::cout << "not enough nodes\n\n";
		return;
	}

	int message_id = 0;

	int average_time_transaction_ms = static_cast<int>(1000.0 / transactions_per_second);

	std::random_device rd;

	std::mt19937 gen(rd());

	std::normal_distribution<> dis(average_time_transaction_ms, 50);

	auto delay = static_cast<__int32>(std::round(dis(gen)));

	if (delay < 10)
	{
		delay = 10;
	}

	this->_request_cooldown = delay;
	
	for (size_t current_time_ms = 0; current_time_ms < 1000 * time_seconds; current_time_ms += time_step_ms)
	{
		this->_request_cooldown -= time_step_ms;

		if (_request_cooldown <= 0)
		{
			new_request(message_id);
			
			message_id++;
			
			auto delay = static_cast<__int32>(std::round(dis(gen)));

			if (delay < 10)
			{
				delay = 10;
			}

			this->_request_cooldown = delay;
		}

		for (size_t i = 0; i < this->_nodes.size(); i++)
		{
			std::vector<hyperledger::network::message> vec = _nodes[i].message_responses(time_step_ms);

			for (auto m : vec)
			{
				broadcast_message(m);
			}
		}
	}
}


void hyperledger::server::pool::broadcast_message(hyperledger::network::message mes)
{
	for (size_t i = 0; i < this->_nodes.size(); i++)
	{
		if (mes.get_message_from() == i)
		{
			continue;
		}

		if (false) // packet loss = 0
		{
			continue;
		}

		int delay = hyperledger::network::medium;

		for (size_t i = 0; i < this->_nodes[mes.get_message_from()].get_latencies().size(); i++)
		{
			if (this->_nodes[mes.get_message_from()].get_latencies()[i].node_id == i)
			{
				delay = this->_nodes[mes.get_message_from()].get_latencies()[i].delay_ms;
			}
		}

		std::random_device rd;

		std::mt19937 gen(rd());

		std::normal_distribution<> dis(delay, 5);

		auto mes_delay = static_cast<__int32>(std::round(dis(gen)));

		mes.set_delay(mes_delay);

		_nodes[i].accept_message(mes);
	}
}
