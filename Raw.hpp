#ifndef Raw
#define Raw

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

namespace nc{
	int unraw() {
		struct termios rawterm;
		tcgetattr(fileno(stdin), &rawterm);
		rawterm.c_iflag |= (BRKINT | ICRNL | INPCK | ISTRIP | IXON);
		rawterm.c_oflag |= (OPOST);
		rawterm.c_lflag |= (ECHO | ICANON | IEXTEN | ISIG);
		return tcsetattr(fileno(stdin), TCSAFLUSH, &rawterm);
	}
	int raw() {
		struct termios unrawterm;
		tcgetattr(fileno(stdin), &unrawterm);
		unrawterm.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
		unrawterm.c_oflag &= ~(OPOST);
		unrawterm.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		return tcsetattr(fileno(stdin), TCSAFLUSH, &unrawterm);
	}
}

#endif