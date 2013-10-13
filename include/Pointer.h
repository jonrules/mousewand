/*
 * Pointer.h
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef MOUSEWAND_POINTER_H_
#define MOUSEWAND_POINTER_H_


#include "PointerException.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace mousewand {
	class Pointer {
		public:
			Pointer();
			~Pointer();
			void moveTo(int x, int y);
		private:
			Display *display;
			Window rootWindow;
	};
}


#endif /* MOUSEWAND_POINTER_H_ */
