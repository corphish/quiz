/* This unit defines some commonly used functions in TurboC which are not available in modern compilers.*/

#include <stdlib.h>
#include <iostream>

extern void clrscr () {
	system("clear");
}

extern char getch() {
	int ch = std::cin.get();
	return (char)ch;
}