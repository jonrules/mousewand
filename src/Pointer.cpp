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
		this->_currentWindow = this->_rootWindow;
	}

	Pointer::~Pointer() {

	}

	void Pointer::buttonDown(int button) {
		int button1 = Button1;
		int button2 = Button2;
		int button3 = Button3;
		XEvent event;
		event.type = ButtonPress;
		event.xbutton.button = button;
		event.xbutton.same_screen = True;
		XQueryPointer(
			this->_display,
			this->_rootWindow,
			&event.xbutton.root,
			&event.xbutton.window,
			&event.xbutton.x_root,
			&event.xbutton.y_root,
			&event.xbutton.x,
			&event.xbutton.y,
			&event.xbutton.state
		);
		event.xbutton.subwindow = event.xbutton.window;

		XSendEvent(this->_display, PointerWindow, True, 0xfff, &event);
		XFlush(this->_display);
	}

	void Pointer::buttonUp(int button) {
		XEvent event;
		event.type = ButtonRelease;
		event.xbutton.button = button;
		event.xbutton.same_screen = True;
		XQueryPointer(
			this->_display,
			this->_rootWindow,
			&event.xbutton.root,
			&event.xbutton.window,
			&event.xbutton.x_root,
			&event.xbutton.y_root,
			&event.xbutton.x,
			&event.xbutton.y,
			&event.xbutton.state
		);
		event.xbutton.subwindow = event.xbutton.window;
		event.xbutton.state = 0x100;

		XSendEvent(this->_display, PointerWindow, True, 0xfff, &event);
		XFlush(this->_display);
	}

	void Pointer::moveRelative(int x, int y) {
		XWarpPointer(this->_display, None, None, 0, 0, 0, 0, x, y);
		XFlush(this->_display);
	}

	void Pointer::moveTo(int x, int y) {
		XWarpPointer(this->_display, None, this->_getCurrentWindow(), 0, 0, 0, 0, x, y);
		XFlush(this->_display);
	}

	Window Pointer::_getCurrentWindow() {
		Window fromroot, tmpwin;
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
		this->_currentWindow = RootWindow(this->_display, screenNumber);
		return this->_currentWindow;
	}

} /* namespace mousewand */

