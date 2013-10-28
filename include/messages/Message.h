/*
 * Message.h
 *
 *  Created on: Oct 19, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef MOUSEWAND_MESSAGES_MESSAGE_H_
#define MOUSEWAND_MESSAGES_MESSAGE_H_


namespace mousewand {

	namespace messages {

		class Message {
			public:
				static const char TYPE_POINTER_DOWN = 1;
				static const char TYPE_POINTER_MOVE = 2;
				static const char TYPE_POINTER_MOVE_RELATIVE = 3;
				static const char TYPE_POINTER_UP = 4;
				static const char STATUS_OK = 0;
				static const char STATUS_ERROR = 1;
				static const char ERROR_INVALID_PARAMS = 1;

				Message();
				virtual ~Message();
				virtual int readAll(int socket);
				int readByte(int socket, void *data);
				int readInt(int socket, void *data);
				virtual void reset();
				virtual int writeAll(int socket);
				int writeByte(int socket, const void *data);
				int writeInt(int socket, const void *data);
		};

	}

}


#endif /* MOUSEWAND_MESSAGES_MESSAGE_H_ */
