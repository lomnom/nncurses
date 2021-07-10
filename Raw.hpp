#ifndef Raw
#define Raw

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        return "!@#$%^(&)*_+@FAILED@%#^$&%*^&()*&"; //string that no program will return hopefully
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


void raw(bool state){ //i got tired of trying everything
    if (state){
        exec("stty raw");
        exec("stty -echo");
    }else{
        exec("stty -raw");
        exec("stty echo");
    }
}

#endif