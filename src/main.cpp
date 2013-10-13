/*
 * main.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: Jonathan Baltazar
 */

#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <iostream>
#include "Pointer.h"
using namespace mousewand;

int main(int argc, char **argv) {
	char *input = new char[100];
	int x, y;
	Pointer pointer;

	std::cout << "Enter coordinates x y:" << std::endl;
	while (std::strcmp("exit", input) != 0) {
		std::cin >> x >> y;
		if (std::cin.fail()) {
			exit(0);
		}
		pointer.moveTo(x, y);
		std::cout << "Moving to (" << x << "," << y << ")" << std::endl;
	}

	delete[] input;
	return (0);
}



