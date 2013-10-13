/*
 * PointerException.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#include "PointerException.h"
#include <cstring>
using namespace mousewand;

PointerException::PointerException(const char *message) {
	int length = std::strlen(message);
	this->message = new char[length];
	std::strcpy(this->message, message);
}

PointerException::~PointerException() throw() {
	delete[] this->message;
}

const char* PointerException::what() const throw() {
	return this->message;
}



