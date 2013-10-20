/*
 * Headers.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: Jonathan Baltazar
 */

#include <messages/Message.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

namespace mousewand {

	namespace messages {

		Message::Message() {

		}

		Message::~Message() {

		}

		int Message::readByte(int socket, void *data) {
			int n = read(socket, data, 1);
			return n;
		}

		int Message::readAll(int socket) {
			return 0;
		}

		int Message::readInt(int socket, void *data) {
			int buffer = 0;
			int n = read(socket, &buffer, 4);
			buffer = ntohl(buffer);
			memcpy(data, &buffer, 4);
			return n;
		}

		void Message::reset() {

		}

		int Message::writeByte(int socket, const void *data) {
			int n = write(socket, data, 1);
			return n;
		}

		int Message::writeInt(int socket, const void *data) {
			int buffer = 0;
			memcpy(&buffer, data, 4);
			buffer = htonl(buffer);
			int n = write(socket, &buffer, 4);
			return n;
		}

		int Message::writeAll(int socket) {
			return 0;
		}
	}

}


