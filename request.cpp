#include "pool.h"

void hyperledger::server::pool::new_request(int id)
{
	auto max = this->_mtx_dim * this->_mtx_dim;

	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(0, max - 1);

	std::normal_distribution<> normal_low(hyperledger::network::latency::low, 10);

	std::normal_distribution<> normal_medium(hyperledger::network::latency::medium, 10);

	std::normal_distribution<> normal_high(hyperledger::network::latency::high, 10);

	std::normal_distribution<> normal_very_high(hyperledger::network::latency::very_high, 10);

	auto current_position = dis(gen);

	int current_i = floor(static_cast<double>(current_position) / this->_mtx_dim);
	
	int current_j = current_position - current_i * this->_mtx_dim;

	for (size_t i = 0; i < this->_mtx_dim; i++)
	{
		for (size_t j = 0; j < this->_mtx_dim; j++)
		{
			int linear_position = j + i * this->_mtx_dim;

			if (this->_mtx[linear_position] < 0)
			{
				continue;
			}

			auto x = current_i - i;

			auto y = current_j - j;

			auto distance = sqrt(x*x + y*y);

			distance = distance / (sqrt(2) * this->_mtx_dim);

			if (distance < 0.25)
			{
				auto delay = static_cast<__int32>(std::round(normal_low(gen)));

				if (delay < 10)
				{
					delay = 10;
				}

				auto mes = hyperledger::network::message(5, -1, delay, id,-1);

				this->_nodes[this->_mtx[linear_position]].accept_message(mes);

			}
			else if (distance < 0.50)
			{
				auto delay = static_cast<__int32>(std::round(normal_medium(gen)));

				if (delay < 20)
				{
					delay = 20;
				}

				auto mes = hyperledger::network::message(5, -1, delay, id,-1);

				this->_nodes[this->_mtx[linear_position]].accept_message(mes);

			}
			else if (distance < 0.75)
			{
				auto delay = static_cast<__int32>(std::round(normal_high(gen)));

				if (delay < 30)
				{
					delay = 30;
				}

				auto mes = hyperledger::network::message(5, -1, delay, id,-1);

				this->_nodes[this->_mtx[linear_position]].accept_message(mes);

			}
			else
			{
				auto delay = static_cast<__int32>(std::round(normal_very_high(gen)));

				if (delay < 40)
				{
					delay = 40;
				}

				auto mes = hyperledger::network::message(5, -1, delay, id,-1);

				this->_nodes[this->_mtx[linear_position]].accept_message(mes);

			}


		}
	}
}