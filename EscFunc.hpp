#ifndef EscFunc
#define EscFunc
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif // Windows/Linux

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