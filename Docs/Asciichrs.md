- ***namespace*** `AscBlok`: This namespace contains many block and block elements.
  - ***map\<uint8_t,string\>*** `block`: std::map with block elements 
    block keys follow the following format:  
    ```cpp
    0bXXXX
      |||^bottomRight
      ||^bottomLeft
      |^topRight
      ^topLeft
    ```
    for example: 
      - `block[0b1010]` yields "▌"
      - `block[0b0110]` yields "▞"
  - ***string\[5\]*** `shades`: an array of block shades  
    ```cpp
    {" ","░","▒","▓","█"}
    ```
  - ***string\[9\]*** `horizBar`: an array of horizontal bars  
    ```cpp
    {" ","▏","▎","▍","▌","▋","▊","▉","█"}
    ```
  - ***string\[9\]*** `vertBar`: an array of vertical bars  
    ```cpp
    {" ","▁","▂","▃","▄","▅","▆","▇","█"}
    ```
- ***namespace*** `AscBox`: many box drawing chars
  - ***map\<uint8_t,string\>*** `lines`: std::map with all unicode box drawing chars besides dotted and angled  
    line keys follow the following format:  
    ```
    0b XX XX XX XX
               ^right line
            ^left line
         ^bottom line
      ^top line
    00 - nothing ( )
    01 - thin line (│)
    10 - double line (║)
    11 - thick line (┃)
    ```
    for example:
      - `lines[0b01010101]` yields `┼`
      - `lines[0b00010111]` yields `┮`
