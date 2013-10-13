/*
 * Pointer.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#include "Pointer.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
using namespace mousewand;

Pointer::Pointer() {
	this->display = XOpenDisplay(NULL);
	if (display == NULL) {
		throw new PointerException("Can't open X-Display");
	}
	this->rootWindow = DefaultRootWindow(this->display);
}

Pointer::~Pointer() {

}

void Pointer::moveTo(int x, int y) {
	Window currentWindow, fromroot, tmpwin;
	XWindowAttributes attr;
	int screenNumber, tmp, currentX, currentY;
	unsigned int ret;

	XQueryPointer(
		this->display,
		this->rootWindow,
		&fromroot,
		&tmpwin,
		&currentX,
		&currentY,
		&tmp,
		&tmp,
		&ret
	);
	XGetWindowAttributes(this->display, fromroot, &attr);
	screenNumber = XScreenNumberOfScreen(attr.screen);
	currentWindow = RootWindow(this->display, screenNumber);
	XWarpPointer(this->display, None, currentWindow, 0, 0, 0, 0, x, y);
	XFlush(this->display);
}


