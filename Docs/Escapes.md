- ***namespace*** `Esc`:  
  These are Escape codes or return escape codes.    
  Escape codes are printed to have effect.  
  Support varies between terminals.
  - ***string*** `bell`: produces a ring sound
  - ***string*** `bksp`: backspace (delete character to the left and shift rest of line left) 
    ```cpp
    #include "Escapes.hpp"
    #include <iostream>
    int main(){
      std::cout << "lmao" << nc::Esc::bksp << nc::Esc::bksp << "fao"; //shows as lmfao
    }
    ```
  - ***string*** `vtab`: `newline`, but it doesnt move your cursor to the start of the next line even in cooked mode.
    ```cpp
    #include "Escapes.hpp"
    #include <iostream>
    int main(){
      std::cout << "lmao" << nc::Esc::vtab << "haha"; 
      /*
      shows as
      lmao
          haha
      */
    }
    ```
  - ***string*** `tab`: moves your cursor x position to `((cursX/8)+1)*8`
  - ***string*** `nl`: moves to the start of the next line (in raw mode it will not move to the start) 
  - ***string*** `cr`: moves cursor to the start of the line
  - ***string*** `nlcr`, `crnl`: moves your cursor to the start of the next line, even in raw mode.
  - ***string*** `esc`: the character that preceeds most escape codes
  - ***string*** `savescr`: saves state of the terminal except cursor pos and attrs
  - ***string*** `loadscr`: loads state of terminal
  - ***string*** `savecurs`: saves the cursor position
  - ***string*** `loadcurs`: loads the cursor position
  - ***string*** `savecursattr`: saves the cursor position and atributes. will not work with loadcurs
  - ***string*** `loadcursattr`: loads the cursor position and atributes. will not work with savecurs
  - ***string*** `inviscurs`: makes the cursor invisible
  - ***string*** `viscurs`: undoes `inviscurs`
  - ***string*** `homecurs`: set cursor to (0,0)
  - ***string()*** `movcurs(int row,int col)`: returns escape to move cursor
  - ***string()*** `upcurs(int n)`: returns escape that moves cursor up `n` lines
  - ***string*** `downcurs(int n)`: returns escape that moves cursor down `n` lines
  - ***string*** `leftcurs(int n)`: returns escape that moves cursor left `n` lines
  - ***string*** `rightcurs(int n)`: returns escape that moves cursor right `n` lines
  - ***string*** `upstrtcurs(int n)`: move up `n` lines and go to column 0
  - ***string*** `downstrtcurs(int n)`: move down `n` lines and go to column 0
  - ***string*** `colcurs(int n)`: move cursor to column `n`
  - ***string*** `clrscr`: clears the terminal. Also clears scrollback on iterm2.
  - ***string*** `clrscroll`: clears the scrollback
  - ***string*** `clrlnhm`: clears current line and goes to the start of the line.
  - ***string*** `clrln`: clears current line without homing
  - ***string*** `clrtoeos`: clear from cursor to end of screen
  - ***string*** `clrtosos`: clear from cursor to start of screen
  - ***string*** `clrtoeol`: clear from cursor to end of line
  - ***string*** `clrtosol`: clear from cursor to start of line
  - ***string*** `bld`: bold
  - ***string*** `dim`: dim text
  - ***string*** `ital`: italic
  - ***string*** `uline`: underline
  - ***string*** `blnk`: blink
  - ***string*** `inv`: invert
  - ***string*** `hid`: hide
  - ***string*** `strk`: strikethrough
  - ***string*** `rst`: reset style
  - ***string*** `rstfg`: reset foreground color
  - ***string*** `rstbg`: reset background color
  - ***string*** `unblddim`, `undimbld`: unbold and undim, it doesnt exixt seperately for some reason
  - ***string*** `unital`: undo ital
  - ***string*** `unuline`: undo uline
  - ***string*** `unblnk`: undo blnk
  - ***string*** `uninv`: undo inv
  - ***string*** `unhid`: undo hid
  - ***string*** `unstrk`: undo strk
  - ***string*** `rstfnt`: reset bld,dim,ital,uline,blnk,inv,hid,strk. Innefecient.
  - ***string*** `fgblck`: foreground black
  - ***string*** `fgred`: foreground red
  - ***string*** `fggrn`: foreground green
  - ***string*** `fgylw`: foreground yellow
  - ***string*** `fgblu`: foreground blue
  - ***string*** `fgmgn`: foreground magenta
  - ***string*** `fgcyn`: foreground cyan
  - ***string*** `fgwhit`: foreground white
  - ***string*** `bgblck`: background black
  - ***string*** `bgred`: background red
  - ***string*** `bggrn`: background green
  - ***string*** `bgylw`: background yellow
  - ***string*** `bgblu`: background blue
  - ***string*** `bgmgn`: background magenta
  - ***string*** `bgcyn`: background cyan
  - ***string*** `bgwhit`: background white
  - ***string()*** `fgidcol(uint8_t id)`: returns a escape that [changes the foreground color to id](https://upload.wikimedia.org/wikipedia/commons/1/15/Xterm_256color_chart.svg).
  - ***string()*** `bgidcol(uint8_t id)`: returns a escape that [changes the background color to id](https://upload.wikimedia.org/wikipedia/commons/1/15/Xterm_256color_chart.svg).
  - ***string()*** `wintitle(string title)`: changes the title of the terminal window in *some* terminals.
  - ***string*** `notif(string message)`: sends a notification in *very few* terminals
  - ***string*** `freeze`: im not sure what it does, but it freezes my terminal.
  - ***string*** `nothing`: literally nothing