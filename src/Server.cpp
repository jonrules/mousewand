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
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace mousewand {

	const char Server::MOUSE_DOWN = 1;
	const char Server::MOUSE_MOVE = 2;
	const char Server::MOUSE_UP = 3;
	const char Server::MSG_OK = 0;
	const char Server::MSG_ERROR = 1;
	const char Server::ERROR_INVALID_PARAMS = 1;

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
//		char headers[2], inBuffer[256], outBuffer[2];
		struct messages::Headers *headers = new messages::Headers;
		struct messages::PointerMove *pointerMove = new messages::PointerMove;
		struct messages::Response *response = new messages::Response;
		int n, messageSize;
		int headersSize = sizeof(messages::Headers);
		int responseSize = sizeof(messages::Response);

		while (true) {
			// Read headers
			memset(headers, 0, headersSize);
			n = read(clientSocket, headers, 2);
			if (n < 2) {
				this->_clientSocketError(
					clientSocket,
					"Error reading client socket"
				);
				break;
			}

			// Read message
			memset(response, 0, sizeof(response));
			switch (headers->type) {
				case Server::MOUSE_DOWN: {
					break;
				}

				case Server::MOUSE_MOVE: {
					messageSize = sizeof(messages::PointerMove);
					memset(pointerMove, 0, messageSize);
					n = read(clientSocket, pointerMove, messageSize);
					if (n == messageSize) {
						pointerMove->x = ntohl(pointerMove->x);
						pointerMove->y = ntohl(pointerMove->y);
						this->_pointer->moveTo(pointerMove->x, pointerMove->y);
						response->status = Server::MSG_OK;
						response->info = 0;
						n = write(clientSocket, response, responseSize);
						if (n < 2) {
							this->_clientSocketError(
								clientSocket,
								"Error sending status message"
							);
							return;
						}
					} else {
						response->status = Server::MSG_ERROR;
						response->info = Server::ERROR_INVALID_PARAMS;
						n = write(clientSocket, response, responseSize);
						if (n < 2) {
							this->_clientSocketError(
								clientSocket,
								"Invalid client MOUSE_MOVE message"
							);
						}
					}
					break;
				}

				case Server::MOUSE_UP: {
					break;
				}

				default: {

				}
			}
		}
	}

	void Server::_clientSocketError(int clientSocket, const char *error) {
		perror("Error reading client socket");
		close(clientSocket);
	}

	int Server::_readInt(const char *input, int offset) {
		int value = (input[offset] << 24 & 0xFF000000)
			| (input[offset+1] << 16 & 0xFF0000)
			| (input[offset+2] << 8 & 0xFF00)
			| (input[offset+3] & 0xFF);
		return value;
	}

} /* namespace mousewand */
