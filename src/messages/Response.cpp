/*
 * Response.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: Jonathan Baltazar
 */

#include <messages/Response.h>

namespace mousewand {

	namespace messages {

		Response::Response(): Message() {
			this->_status = this->_info = 0;
		}

		Response::~Response() {

		}

		char Response::getStatus() {
			return this->_status;
		}

		void Response::setStatus(char status) {
			this->_status = status;
		}

		char Response::getInfo() {
			return this->_info;
		}

		void Response::setInfo(char info) {
			this->_info = info;
		}

		int Response::readAll(int socket) {
			int n = 0;
			n += this->readByte(socket, &this->_status);
			n += this->readByte(socket, &this->_info);
			return n;
		}

		void Response::reset() {
			this->_status = this->_info = 0;
		}

		int Response::writeAll(int socket) {
			int n = 0;
			n += this->writeByte(socket, &this->_status);
			n += this->writeByte(socket, &this->_info);
			return n;
		}
	}

}


