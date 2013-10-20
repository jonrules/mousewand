/*
 * Response.h
 *
 *  Created on: Oct 19, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef MOUSEWAND_MESSAGES_RESPONSE_H_
#define MOUSEWAND_MESSAGES_RESPONSE_H_


#include <messages/Message.h>

namespace mousewand {

	namespace messages {

		class Response: Message {
			public:
				Response();
				~Response();
				char getStatus();
				void setStatus(char status);
				char getInfo();
				void setInfo(char info);
				int readAll(int socket);
				void reset();
				int writeAll(int socket);
			private:
				char _status, _info;
		};

	}

}


#endif /* MOUSEWAND_MESSAGES_RESPONSE_H_ */
