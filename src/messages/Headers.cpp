/*
 * Headers.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: Jonathan Baltazar
 */

#include <messages/Headers.h>

namespace mousewand {

	namespace messages {

		Headers::Headers(): Message() {
			this->_version = this->_type = 0;
		}

		Headers::~Headers() {

		}

		char Headers::getVersion() {
			return this->_version;
		}

		char Headers::getType() {
			return this->_type;
		}

		int Headers::readAll(int socket) {
			int n = 0;
			n += this->readByte(socket, &this->_version);
			n += this->readByte(socket, &this->_type);
			return n;
		}

		void Headers::reset() {
			this->_version = this->_type = 0;
		}

		int Headers::writeAll(int socket) {
			int n = 0;
			n += this->writeByte(socket, &this->_version);
			n += this->writeByte(socket, &this->_type);
			return n;
		}
	}

}


