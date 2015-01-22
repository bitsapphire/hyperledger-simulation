#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>
#include "message.h"

namespace hyperledger
{
	namespace network
	{
		enum latency 
		{
			low = 50,
			medium = 100,
			high = 150,
			very_high = 200
		};

		struct node_delay
		{
			int node_id;
			int delay_ms;
			
			node_delay(int id, int delay);
			node_delay();
		};

		class packet
		{
		public:
			packet(int _destination, std::string _hash, int _latency, hyperledger::network::message _message, int _source);
			packet();
			 ~packet();

			int get_destination() const;
			void set_destination(int val);
			std::string get_hash() const;
			void set_hash(std::string val);
			int get_latency() const;
			void set_latency(int val);
			hyperledger::network::message get_message() const;
			void set_message(hyperledger::network::message val);
			int get_source() const;
			void set_source(int val);
		private:
			int _destination;
			std::string _hash;
			int _latency;
			hyperledger::network::message _message;
			int _source;
		};
	}
}	//hyperledger::network

#endif	// !PACKET_H