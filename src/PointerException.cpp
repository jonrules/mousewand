/*
 * PointerException.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#include <PointerException.h>
#include <cstring>

namespace mousewand {

	PointerException::PointerException(const char *message) {
		int length = std::strlen(message);
		this->_message = new char[length];
		std::strcpy(this->_message, message);
	}

	PointerException::~PointerException() throw() {
		delete[] this->_message;
	}

	const char* PointerException::what() const throw() {
		return this->_message;
	}

}


