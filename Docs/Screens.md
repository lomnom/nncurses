- ***class Screen***: `Screen(int rows, int cols,Texture filler)` a representation of the terminal screen that is commited to the screen by `Terminal`. its like a piece of drawing paper for `Renderable`s.  
  filler is the thing `Screen` would be filled with when .fill() is called  
  .fill is called on init
  - ***void()*** `fill()`: fill the screen with fillerTexture.
  - ***void()*** `generateFill()` refresh `fill()`'s filler cache 
  - ***void()*** `render(Screen* scr,int startX,int startY)`: renders this screen onto another screen
  - ***void()*** `renderPart(Screen* scr,int startX,int startY,int partStartX,int partStartY,int sizeX,int sizeY)`: render part if this screen onto another screen
  ***vector< vector\<Texture\> >*** `screen`
  ***vector< vector\<Texture\> >*** `filler` fill()'s cache'
  ***vector\<Texture\>*** `fillerRow`: a row of fill()'s cache
  ***Texture*** `fillerTexture`
  ***int*** `rows`,`cols`
  ***int*** `oldRows`,`oldCols`: ints for fill() to detect changes in rows/cols

- ***class Terminal*** `Terminal(Texture fillTexture)`: An object with an internal `Screen` that it can project onto the real screen.  
  on init, it will push all text in the terminal up and turn on raw mode.  
  On uninit, it will remove it's footprint
  - ***Screen*** `screen` internal screen;
  - ***void()*** `updatesize`: update size of internal screen. screen should be resized with fill() after this.
  - ***void()*** `project()`: refresh the real screen

