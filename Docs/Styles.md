- ***class*** `Col256(short fgid,short bgid)`: An object containing Foreground and Background colors.  
  Colrs can be from [-1-256](https://upload.wikimedia.org/wikipedia/commons/1/15/Xterm_256color_chart.svg), where -1 is the default terminal color.
  - ***short*** `fg`: fgid
  - ***short*** `bg`: bgid
  - ***string*** `fgEsc`: escape to change fgcol
  - ***string*** `bgEsc`: escape to change bgcol
  - ***string()*** `getFgEsc()`: get escape to change fg
  - ***string()*** `getBgEsc()`: get escape to change bg
  - ***string()*** `getesc()`: get escape to change fg and bg

- ***namespace*** `EfctMasks`: Bitmasks for `Effect` values
  - ***uint8_t*** `bld`: bold
  - ***uint8_t*** `dim`: dim
  - ***uint8_t*** `ital`: italic
  - ***uint8_t*** `uline`: underline
  - ***uint8_t*** `blnk`: blink
  - ***uint8_t*** `inv`: inverted
  - ***uint8_t*** `hid`: hidden/invisible
  - ***uint8_t*** `strk`: strikethrough
  - ***uint8_t*** `none`: nothing

- ***class***: `Effect(uint8_t effects)`: stores effects (eg. italic, bold)  
  the uint8_t is made by `or`ing the bitmasks of the desired effects. eg: 
  ```c++
  nc::Effect boldUline(EfctMasks::bld|Efctmasks::uline);
  ```  
  - ***uint8_t*** `effects`: effects
  - ***string()*** `getesc()`: get escape code to change effects

- ***class*** `Style(Col256 col, Effect e)`  
  ***class*** `Style(int16_t fg, int16_t bg, Effect e)`: initialise `color` with `fg` and `bg`  
  ***class*** `Style(Col256 col, uint8_t e)`: initialise `effect` with `e`  
  ***class*** `Style(int16_t fg, int16_t bg, uint8_t e)`: initialise `color` with `fg` and `bg` and `effect` with `e`  
  Object containing a Col256 and Effect.
  - ***Col256*** `color`
  - ***Effect*** `effect`
  - ***string()*** `getesc()`: get escape code to change effect and color

- ***class Texture*** `Texture(string* characte,Style* styl)`: An object that contains a `Style` and `String`, basically a representation of a styled character on a terminal screen
  - ***string\**** `character`
  - ***Style\**** `style`
  - ***string()*** `getesc()`: get escape code to print styled character