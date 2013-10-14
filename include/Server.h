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
			static const unsigned char MOUSE_DOWN;
			static const unsigned char MOUSE_MOVE;
			static const unsigned char MOUSE_UP;
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
