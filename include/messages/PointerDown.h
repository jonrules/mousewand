/*
 * PointerDown.h
 *
 *  Created on: Oct 28, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef MOUSEWAND_MESSAGES_POINTERDOWN_H_
#define MOUSEWAND_MESSAGES_POINTERDOWN_H_


#include <messages/Message.h>

namespace mousewand {

	namespace messages {

		class PointerDown: Message {
			public:
				PointerDown();
				~PointerDown();
				int getButton();
				int readAll(int socket);
				void reset();
				int writeAll(int socket);
			private:
				int _button;
		};

	}

}


#endif /* MOUSEWAND_MESSAGES_POINTERDOWN_H_ */
