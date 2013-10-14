/*
 * Pointer.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#include <Pointer.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace mousewand {

	Pointer::Pointer() {
		this->_display = XOpenDisplay(NULL);
		if (_display == NULL) {
			throw new PointerException("Can't open X-Display");
		}
		this->_rootWindow = DefaultRootWindow(this->_display);
	}

	Pointer::~Pointer() {

	}

	void Pointer::moveTo(int x, int y) {
		Window currentWindow, fromroot, tmpwin;
		XWindowAttributes attr;
		int screenNumber, tmp, currentX, currentY;
		unsigned int ret;

		XQueryPointer(
			this->_display,
			this->_rootWindow,
			&fromroot,
			&tmpwin,
			&currentX,
			&currentY,
			&tmp,
			&tmp,
			&ret
		);
		XGetWindowAttributes(this->_display, fromroot, &attr);
		screenNumber = XScreenNumberOfScreen(attr.screen);
		currentWindow = RootWindow(this->_display, screenNumber);
		XWarpPointer(this->_display, None, currentWindow, 0, 0, 0, 0, x, y);
		XFlush(this->_display);
	}

} /* namespace mousewand */

