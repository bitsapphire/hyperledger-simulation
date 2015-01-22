#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <map>

namespace hyperledger
{
	namespace network
	{
		class message
		{
		public:
			message(int _message_type, std::map<std::string,std::string> _parameters, std::string _signature, int _delay);
			message(int _message_type, int _signature, int _delay, int _message_id, int _message_from);
			message();
			 ~message();

			int get_message_type() const;
			void set_message_type(int val);
			std::map<std::string,std::string> get_parameters() const;
			void set_parameters(std::map<std::string,std::string> val);
			std::string get_signature() const;
			void set_signature(std::string val);
			int get_delay() const;
			void set_delay(int val);
			int get_message_id() const;
			void set_message_id(int val);
			int get_message_from() const;
			void set_message_from(int val);
			friend std::ostream& operator<<(std::ostream& os, const message& _message);
		private:
			int _message_from;
			int _message_id;
			int _delay;
			int _message_type;
			std::map<std::string,std::string> _parameters;
			std::string _signature;
		};
	}
}	//hyperledger::network

#endif	// !MESSAGE_H