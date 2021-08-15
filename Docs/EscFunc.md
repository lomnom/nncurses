- ***void()*** `gettermsize(int* width, int* height)`: get terminal size 
  - example:  
  ```cpp
  #include "EscFunc.hpp"
  int height,width;
  int main(){
      nc::gettermsize(&width,&height);
      std::cout << "width: " << width << "\nheight: " << height;
  }
  ```
- ***char()*** `cinchr()`: reads one char from stdin and returns it
- ***char()*** `ubCinchr()`: reads one char from stdin and returns it. Has a timout of 0.1s.