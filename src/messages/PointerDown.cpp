/*
 * PointerDown.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: Jonathan Baltazar
 */

#include <messages/PointerDown.h>

namespace mousewand {

	namespace messages {

		PointerDown::PointerDown(): Message() {
			this->_button = 0;
		}

		PointerDown::~PointerDown() {

		}

		int PointerDown::getButton() {
			return this->_button;
		}

		int PointerDown::readAll(int socket) {
			int n = 0;
			n += this->readInt(socket, &this->_button);
			return n;
		}

		void PointerDown::reset() {
			this->_button = 0;
		}

		int PointerDown::writeAll(int socket) {
			int n = 0;
			n += this->writeInt(socket, &this->_button);
			return n;
		}
	}

}


