/*
 * Server.h
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef MOUSEWAND_SERVER_H_
#define MOUSEWAND_SERVER_H_


#include <Pointer.h>

namespace mousewand {

	class Server {
		public:
			static const char MOUSE_DOWN;
			static const char MOUSE_MOVE;
			static const char MOUSE_UP;
			static const char MSG_OK;
			static const char MSG_ERROR;
			static const char ERROR_INVALID_PARAMS;
			Server();
			virtual ~Server();
			void start();
			void stop();
		private:
			Pointer *_pointer;
			void _acceptClient(int clientSocket);
			void _clientSocketError(int clientSocket, const char *error);
			int _readInt(const char *input, int offset);
	};

} /* namespace mousewand */


#endif /* MOUSEWAND_SERVER_H_ */
