/*
 * Headers.h
 *
 *  Created on: Oct 19, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef MOUSEWAND_MESSAGES_HEADERS_H_
#define MOUSEWAND_MESSAGES_HEADERS_H_


#include <messages/Message.h>

namespace mousewand {

	namespace messages {

		class Headers: Message {
			public:
				Headers();
				~Headers();
				char getType();
				char getVersion();
				int readAll(int socket);
				void reset();
				int writeAll(int socket);
			private:
				char _version, _type;
		};

	}

}


#endif /* MOUSEWAND_MESSAGES_HEADERS_H_ */
