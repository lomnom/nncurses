- ***void()*** `gettermsize(int* width, int* height)`: get terminal size 
  example:  
  ```cpp
  #include<nncurses.hpp>
  int height,width;
  nc::gettermsize(&width,&height);
  std::cout << "width: " << width << "\nheight: " << height;
  ```
- ***char()*** `cinchr()`: reads one char from stdin and returns it