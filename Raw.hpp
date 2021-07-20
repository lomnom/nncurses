#ifndef Raw
#define Raw

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

namespace nc{
	class RawController{
	public:
		struct termios unrawterm;
		RawController(){
			tcgetattr(fileno(stdin), &unrawterm);
		}
		int unraw() {
			return tcsetattr(fileno(stdin), TCSAFLUSH, &unrawterm);
		}
		int raw() {
			struct termios rawterm = unrawterm;
			rawterm.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
			rawterm.c_oflag &= ~(OPOST);
			rawterm.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
			return tcsetattr(fileno(stdin), TCSAFLUSH, &rawterm);
		}
	};
}

#endif