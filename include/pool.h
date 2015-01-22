#ifndef POOL_H
#define POOL_H

#include <string>
#include <vector>
#include <random>
#include <cmath>
#include "node.h"
#include "packet.h"
#include "message.h"


namespace hyperledger
{
	namespace server
	{
		class pool
		{
		public:
			pool(std::vector<hyperledger::server::node> _nodes, int _total_nodes, int _request_cooldown, int _time_step_ms, int _transactions_per_second);
			pool();
			 ~pool();

			std::vector<hyperledger::server::node> get_nodes() const;
			void set_nodes(std::vector<hyperledger::server::node> val);
			int get_total_nodes() const;
			void set_total_nodes(int val);
			void initialize_nodes(int number_of_nodes, bool automatic_fit);
			int get_request_cooldown() const;
			void set_request_cooldown(int val);
			int get_time_step_ms() const;
			void set_time_step_ms(int val);
			int get_transactions_per_second() const;
			void set_transactions_per_second(int val);

			void start_pool(int transactions_per_second, int time_step_ms, int time_seconds);
			
		private:
			void new_request(int id);
			void broadcast_message(hyperledger::network::message mes);
			std::vector<hyperledger::server::node> _nodes;
			int _total_nodes;
			int _request_cooldown;
			int _time_step_ms;
			int _transactions_per_second;
			int _mtx_dim;
			int* _mtx;
		};
	}
}	//hyperledger::server

#endif	// !POOL_H