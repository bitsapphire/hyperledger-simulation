#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include <fstream>
#include "message.h"
#include "packet.h"

namespace hyperledger
{
	namespace server
	{
		class node
		{
		public:
			node(std::vector<hyperledger::network::message> _message_que, int _node_id, std::vector<int> _number_signatures, std::string _signature);
			node(int _node_id, int _signatures_requiered);
			node();
			 ~node();

			std::vector<hyperledger::network::message> get_temp_message_que() const;
			void set_temp_message_que(std::vector<hyperledger::network::message> val);
			std::vector<hyperledger::network::message> get_message_que() const;
			void set_message_que(std::vector<hyperledger::network::message> val);
			int get_node_id() const;
			void set_node_id(int val);
			std::vector<int> get_number_signatures() const;
			void set_number_signatures(std::vector<int> val);
			std::string get_signature() const;
			void set_signature(std::string val);
			std::vector<hyperledger::network::node_delay> get_latencies() const;
			void set_latencies(std::vector<hyperledger::network::node_delay> val);
			void append_latencies(hyperledger::network::node_delay val);
			void accept_message(hyperledger::network::message val);
			friend std::ostream& operator<<(std::ostream& os, const node& _node);
			std::vector<hyperledger::network::message> message_responses(int time_step_ms);

		private:
			std::vector<hyperledger::network::message> _message_que;
			std::vector<hyperledger::network::message> _temp_message_que;
			void write_to_file(hyperledger::network::message);
			int _node_id;
			int _node_time = 0;
			int _signatures_required;
			std::vector<int> _number_signatures;
			std::string _signature;
			std::vector<hyperledger::network::node_delay> _latencies;
		};
	}
}	//hyperledger::server

#endif	// !NODE_H