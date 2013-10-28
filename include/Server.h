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
			Server();
			virtual ~Server();
			void start();
			void stop();
		private:
			Pointer *_pointer;
			void _acceptClient(int clientSocket);
			void _clientSocketError(int clientSocket, const char *error);
	};

} /* namespace mousewand */


#endif /* MOUSEWAND_SERVER_H_ */
