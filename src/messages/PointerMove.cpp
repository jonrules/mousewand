/*
 * PointerMove.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: Jonathan Baltazar
 */

#include <messages/PointerMove.h>

namespace mousewand {

	namespace messages {

		PointerMove::PointerMove(): Message() {
			this->_x = this->_y = 0;
		}

		PointerMove::~PointerMove() {

		}

		int PointerMove::getX() {
			return this->_x;
		}

		int PointerMove::getY() {
			return this->_y;
		}

		int PointerMove::readAll(int socket) {
			int n = 0;
			n += this->readInt(socket, &this->_x);
			n += this->readInt(socket, &this->_y);
			return n;
		}

		void PointerMove::reset() {
			this->_x = this->_y = 0;
		}

		int PointerMove::writeAll(int socket) {
			int n = 0;
			n += this->writeInt(socket, &this->_x);
			n += this->writeInt(socket, &this->_y);
			return n;
		}
	}

}


