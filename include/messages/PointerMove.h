/*
 * PointerMove.h
 *
 *  Created on: Oct 19, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef MOUSEWAND_MESSAGES_POINTERMOVE_H_
#define MOUSEWAND_MESSAGES_POINTERMOVE_H_


#include <messages/Message.h>

namespace mousewand {

	namespace messages {

		class PointerMove: Message {
			public:
				PointerMove();
				~PointerMove();
				int getX();
				int getY();
				int readAll(int socket);
				void reset();
				int writeAll(int socket);
			private:
				int _x, _y;
		};

	}

}


#endif /* MOUSEWAND_MESSAGES_POINTERMOVE_H_ */
