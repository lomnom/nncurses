# nncurses: ncurses but better
Rescources:
  - (comfusing) [Docs](Docs/Docs.md)
  - [Examples](examples)
## Simple hello world
```cpp
#include "nncurses.hpp"
#define helloLen 14
using namespace nc;

int main(){
  Terminal terminal(Texture("#",Style(6,2,EfctMasks::ital))); //initialise virtual terminal and real terminal
  Text hello("Hello world!!!",Style(17,2,EfctMasks::bld|EfctMasks::ital)); //initialise text object
  hello.startx=midOfst(terminal.screen.cols,helloLen); //center the text horizontally
  hello.starty=terminal.screen.rows/2; //center the text vertically
  hello.render(&terminal.screen); //render text onto virtual screen
  terminal.project(); //show the text
  cinchr(); //wait for keypress to continue
}
```
## Hello world but you can move around
```cpp
#include "nncurses.hpp"
#define helloLen 14
using namespace nc;
using std::cout;

int main(){
  Terminal terminal(Texture("#",Style(6,2,EfctMasks::ital))); //initialise virtual terminal and real terminal
  Text hello("Hello world!!!",Style(17,2,EfctMasks::bld|EfctMasks::ital)); //initialise text object
  hello.startx=midOfst(terminal.screen.cols,helloLen); //center the text horizontally
  hello.starty=terminal.screen.rows/2; //center the text vertically
  while (true){
    hello.render(&terminal.screen); //render text onto virtual screen
    terminal.project(); //show the text
    char inCh=cinchr(); //wait for keypress to continue
    if (inCh=='q') break; //exit program is q pressed
    else if (inCh=='w') hello.starty--; //move text up
    else if (inCh=='s') hello.starty++; //move text down
    else if (inCh=='a') hello.startx--; //move text left
    else if (inCh=='d') hello.startx++; //move text right
    else if (inCh=='c') terminal.screen.fill(); //clear remnants of old hello worlds (pretty fast)
    else cout << Esc::bell; //make noise if invalid char
  }
}
```
**This library is C++20**