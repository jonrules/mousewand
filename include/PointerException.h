/*
 * PointerException.h
 *
 *  Created on: Oct 13, 2013
 *      Author: jonathan
 */

#ifndef MOUSEWAND_POINTEREXCEPTION_H_
#define MOUSEWAND_POINTEREXCEPTION_H_


#include <exception>

namespace mousewand {

	class PointerException: std::exception {
		public:
			PointerException(const char *message);
			~PointerException() throw();
			virtual const char* what() const throw();
		private:
			char *_message;
	};

} /* namespace mousewand */


#endif /* MOUSEWAND_POINTEREXCEPTION_H_ */
