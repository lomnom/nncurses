#ifndef EscFunc
#define EscFunc
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace nc{
    void gettermsize(int* width, int* height) {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        *width=w.ws_col;
        *height=w.ws_row;
    }

    std::streambuf *cinbuf=std::cin.rdbuf();

    char cinchr(){
        char c;
        read(STDIN_FILENO, &c, 1);
    	return c;
    }

    char ubCinchr(){
        struct termios orig_termios;
        tcgetattr(STDIN_FILENO, &orig_termios);
        struct termios raw=orig_termios;

        raw.c_cc[VTIME] = 1;
        raw.c_cc[VMIN] = 0;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

        char c='\0';
        read(STDIN_FILENO, &c, 1);

        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);

        return c;
    }
}

#endif