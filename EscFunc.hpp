#ifndef EscFunc
#define EscFunc

#include "Escapes.hpp"
#include <termios.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
using namespace std;

streambuf *cinbuf=cin.rdbuf();

char cinchr(){
	return cinbuf->sbumpc();
}

void canon() {
	struct termios currset;
    tcgetattr(0, &currset);
    currset.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &currset);
}

void noecho() {
	struct termios currset;
    tcgetattr(0, &currset);
    currset.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &currset);
}

void nocanon() {
	struct termios currset;
    tcgetattr(0, &currset);
    currset.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &currset);
}

void echo() {
	struct termios currset;
    tcgetattr(0, &currset);
    currset.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &currset);
}

winsize gettermsize(){
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

#endif