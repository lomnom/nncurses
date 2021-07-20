#ifndef EscFunc
#define EscFunc
#include <iostream>
#include <sys/ioctl.h>
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
    	return cinbuf->sbumpc();
    }
}

#endif