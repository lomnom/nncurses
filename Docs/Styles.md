- ***class Col256*** `Col256(short* fgid,short* bgid)`: An object containing Foreground and Background colors.  
  Colrs can be from [-1-256](https://upload.wikimedia.org/wikipedia/commons/1/15/Xterm_256color_chart.svg), where -1 is the default terminal color.
  - ***short\**** `fg`: fgid
  - ***short\**** `bg`: bgid
  - ***string*** `escape`: escape to change fgcol and bgcol
  - ***string*** `fgEsc`: escape to change fgcol
  - ***string*** `bgEsc`: escape to change bgcol
  - ***void()*** `getFgEsc()`: update foreground escape
  - ***void()*** `getBgEsc()`: update background escape
  - ***void()*** `getesc()`: set `escape` to fgesc+bgesc
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
- ***class Effect***: `Effect(uint8_t* effects)`: stores effects (eg. italic, bold)  
  the uint8_t is made by `or`ing the bitmasks of the desired effects. eg: 
  ```c++
  uint8_t effectInt=(EfctMasks::bld|Efctmasks::uline);
  Effect boldUline(&effectInt);
  ```  
  - ***uint8_t\**** `effects`: effects
  - ***string*** `escape`: escape code for the effects
  - ***void()*** `getesc()`: update internal escape code
- ***class Style***: `Style(Col256* col, Effect* e)`: Object containing a Col256 and Effect
  - ***Col256\**** `color`
  - ***Effect\**** `effect`
  - ***string*** `escape`
  - ***void()*** `getesc()`: set internal escape to `color->escape+effect->escape`
- ***class Texture*** `Texture(string* characte,Style* styl)`: An object that contains a `Style` and `String`, basically a representation of a styled character on a terminal screen
  - ***string\**** `character`
  - ***Style\**** `style`
  - ***string*** `escape`: `style->escape`+`character`+`Esc::rst`
  - ***string*** `stylEsc`: escape for the styling
  - ***void()*** `getesc()`: update `escape`
  - ***void()*** `getStylEsc()` :update `stylEsc`