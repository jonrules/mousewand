/*
 * PointerUp.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: Jonathan Baltazar
 */

#include <messages/PointerUp.h>

namespace mousewand {

	namespace messages {

		PointerUp::PointerUp(): Message() {
			this->_button = 0;
		}

		PointerUp::~PointerUp() {

		}

		int PointerUp::getButton() {
			return this->_button;
		}

		int PointerUp::readAll(int socket) {
			int n = 0;
			n += this->readInt(socket, &this->_button);
			return n;
		}

		void PointerUp::reset() {
			this->_button = 0;
		}

		int PointerUp::writeAll(int socket) {
			int n = 0;
			n += this->writeInt(socket, &this->_button);
			return n;
		}
	}

}


