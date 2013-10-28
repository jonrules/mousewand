/*
 * Server.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#include <Server.h>
#include <Pointer.h>
#include <messages/Headers.h>
#include <messages/PointerMove.h>
#include <messages/Response.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace mousewand {

	Server::Server() {
		this->_pointer = new Pointer();
	}

	Server::~Server() {
		delete this->_pointer;
	}

	void Server::start() {
		int serverSocket, clientSocket, port;
		struct sockaddr_in serverAddress, clientAddress;

		serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (serverSocket < 0) {
			perror("Error opening host socket");
			exit(1);
		}

		memset((char *) &serverAddress, 0, sizeof(serverAddress));
		port = 2185;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = INADDR_ANY;
		serverAddress.sin_port = htons(port);

		int bound = bind(
			serverSocket,
			(struct sockaddr *) &serverAddress,
			sizeof(serverAddress)
		);
		if (bound < 0) {
			perror("Error binding host socket");
			exit(1);
		}

		std::cout << "Listening to port " << port << "..." << std::endl;
		listen(serverSocket, 10);
		unsigned int clientLength = sizeof(clientAddress);

		clientSocket = accept(
			serverSocket,
			(struct sockaddr *)&clientAddress,
			&clientLength
		);
		if (clientSocket < 0) {
			perror("Error accepting client socket");
		}
		std::cout << "Accepting client " << clientSocket << "..." << std::endl;
		struct timeval timeout;
		timeout.tv_sec = 10;
		setsockopt(
			clientSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)
		);
		int receive = 256;
		setsockopt(
			clientSocket, SOL_SOCKET, SO_RCVLOWAT, &receive, sizeof(receive)
		);
		this->_acceptClient(clientSocket);
		close(clientSocket);
	}

	void Server::stop() {

	}

	void Server::_acceptClient(int clientSocket) {
		int n = 0;
		messages::Headers *headers = new messages::Headers;
		messages::PointerMove *pointerMove = new messages::PointerMove;
		messages::Response *response = new messages::Response;

		while (true) {
			// Read headers
			headers->reset();
			n = headers->readAll(clientSocket);
			if (n < 1) {
				this->_clientSocketError(
					clientSocket,
					"Error reading message"
				);
				break;
			}

			// Read message
			switch (headers->getType()) {
				case messages::Message::TYPE_POINTER_DOWN: {
					break;
				}

				case messages::Message::TYPE_POINTER_MOVE: {
					pointerMove->reset();
					n = pointerMove->readAll(clientSocket);
					if (n > 0) {
						this->_pointer->moveTo(pointerMove->getX(), pointerMove->getY());
						response->reset();
						response->setStatus(0);
						response->setInfo(0);
						response->writeAll(clientSocket);
					} else {

					}
					break;
				}

				case messages::Message::TYPE_POINTER_MOVE_RELATIVE: {
					pointerMove->reset();
					n = pointerMove->readAll(clientSocket);
					if (n > 0) {
						this->_pointer->moveRelative(pointerMove->getX(), pointerMove->getY());
						response->reset();
						response->setStatus(0);
						response->setInfo(0);
						response->writeAll(clientSocket);
					} else {

					}
					break;
				}

				case messages::Message::TYPE_POINTER_UP: {
					break;
				}

				default: {

				}
			}
		}

		delete headers;
		delete pointerMove;
		delete response;
	}

	void Server::_clientSocketError(int clientSocket, const char *error) {
		perror(error);
		close(clientSocket);
	}

} /* namespace mousewand */
