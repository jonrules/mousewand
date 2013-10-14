/*
 * Server.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#include <Server.h>
#include <Pointer.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace mousewand {

	const unsigned char Server::MOUSE_DOWN = 1;
	const unsigned char Server::MOUSE_MOVE = 2;
	const unsigned char Server::MOUSE_UP = 3;

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
		char headers[2], message[256];
		int length, argsCount;
		unsigned char type;

		while (true) {
			// Read headers
			memset(headers, 0, 2);
			length = read(clientSocket, headers, 2);
			if (length < 0) {
				this->_clientSocketError(
					clientSocket,
					"Error reading client socket"
				);
				break;
			}
			if (length < 1) {
				this->_clientSocketError(
					clientSocket,
					"Error reading message length"
				);
				break;
			}
			type = headers[0];
			argsCount = headers[1];

			// Read message
			memset(message, 0, 256);
			switch (type) {
				case Server::MOUSE_DOWN: {
					break;
				}

				case Server::MOUSE_MOVE: {
					if (argsCount == 2) {
						length = read(clientSocket, message, 8);
						int x = this->_readInt(message, 0);
						int y = this->_readInt(message, 4);
						this->_pointer->moveTo(x, y);
					} else {
						this->_clientSocketError(
							clientSocket,
							"Invalid client MOUSE_MOVE message"
						);
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
