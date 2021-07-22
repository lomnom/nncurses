- ***class*** `RawController()`:
  - ***int()*** `raw()`: turn on raw mode. returns -1 on failure
  - ***int()*** `unraw()`: turn off raw mode. returns -1 on failure
  - ***struct termios*** `unrawterm`: The terminal at the state of object initialisation
  - example:
  ```cpp
  #include "Raw.hpp"
  #include "Escapes.hpp"
  #include "EscFunc.hpp"
  #include <iostream>

  int main(){
    nc::RawController rawCtrl;
    rawCtrl.raw();
    std::cout << "look! its raw mode!\n"
           "\\n doesnt move cursor back to start anymore, like this!\n\r"
           "you need a \\r to move the cursor back to the start!\n\r"
           "I can also get your keystrokes "+nc::Esc::ital+"instantly"+nc::Esc::unital+"!\n\r"
           "Press any button to try it out! (q to quit)\n\r";

    while (1){
      char currCh=nc::cinchr();

      if (currCh=='q'){
        break;
      }else{
        std::cout << "Received key "+nc::Esc::fgblu+currCh+nc::Esc::rstfg+"!\n\r";
      }
    }
    rawCtrl.unraw();
  }
  ```