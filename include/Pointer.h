/*
 * Pointer.h
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#ifndef MOUSEWAND_POINTER_H_
#define MOUSEWAND_POINTER_H_


#include <PointerException.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace mousewand {

	class Pointer {
		public:
			Pointer();
			~Pointer();
			void moveRelative(int x, int y);
			void moveTo(int x, int y);
			void buttonDown(int button);
			void buttonUp(int button);
		private:
			Display *_display;
			Window _currentWindow;
			Window _rootWindow;
			Window _getCurrentWindow();
	};

} /* namespace mousewand */


#endif /* MOUSEWAND_POINTER_H_ */
