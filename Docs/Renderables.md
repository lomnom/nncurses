- ***template\<class T\>()*** `abs(T x)`: returns absolute value of x
- ***template\<class T\>()*** `smaller(T a,T b)`: returns the smaller T
- ***template\<class T\>()*** `btwn(T a,T b)`: get the value between a and b
- ***template\<class T\>()*** `midOfst(T a,T b)`: return (a/2)-(b/2)
- ***template\<class T\>()*** `toroid(T a, T b)`: a%b, but supports negative a or b values
- ***virt class*** `Renderable`: a class that all renderables are children of. Has pure virtual function `render(Screen*)`
<!-- - ***class*** `Line(Texture text,int startx,int starty,int endx,int endy)`: Bresenham line renderable
  - ***void()*** `render(Screen* screen)`: render the line
  - ***Texture\**** `texture`: texture used to draw line
  - ***int\**** `startx`
  - ***int\**** `starty`
  - ***int\**** `endx`
  - ***int\**** `endy`
  - [example](../examples/spamGame.cpp) -->
- ***class*** `HollowRectangle(int startx,int starty,int height,int width,Texture texture)`  
  ***class*** `HollowRectangle(int startx,int starty,int height,int width,Texture texture,Texture cornerTexture)`  
  ***class*** `HollowRectangle(int startx,int starty,int height,int width,Texture horizTexture,Texture vertTexture,Texture cornerTexture)`  
  ***class*** `HollowRectangle(int startx,int starty,int height,int width,Texture horizTexture,Texture vertTexture,Texture TLCorner,Texture TRCorner,Texture BLCorner,Texture BRCorner)`: Hollow rectangle renderable  
  - ***void()*** `render(Screen* screen)`: render the rectangle
  - ***Texture*** `top`
  - ***Texture*** `bottom`
  - ***Texture*** `left`
  - ***Texture*** `right`
  - ***Texture*** `TLCorner`
  - ***Texture*** `TRCorner`
  - ***Texture*** `BLCorner`
  - ***Texture*** `BRCorner`
  - ***int*** `startx`
  - ***int*** `starty`
  - ***int*** `height`
  - ***int*** `width`
  - [example](../examples/moveCursor.cpp)
- ***class*** `Text(string text,Style style,int startx,int starty)`
  ***class*** `Text(string text,Style style)` (startX and starty both 0): Text renderable  
  - ***void()*** `render(Screen* screen)`: render text
  - ***string*** `text`
  - ***int*** `startx`
  - ***int*** `starty`
  - ***Style*** `style`
  - [example](../examples/moveCursor.cpp)
- ***class*** `Text(string text,Style style,int startx,int starty)`  
  ***class*** `Text(string text,Style style)` (startX and starty both 0): Text renderable  
  - ***void()*** `render(Screen* screen)`: render text
  - ***string*** `text`
  - ***int*** `startx`
  - ***int*** `starty`
  - ***Style*** `style`
  - [example](../examples/moveCursor.cpp)
- ***class*** `TranspText(string text,Effect effects,short fg,int startx,int starty)`  
  ***class*** `TranspText(string text,Effect effects,short fg)` (startx and starty both 0): `Text`, but it preserves background color.
  - ***void()*** `render(Screen* screen)`: render text
  - ***string*** `text`
  - ***int*** `startx`
  - ***int*** `starty`
  - ***Effect*** `effects`
  - ***short*** `fg`
  - [example](../examples/moveCursor.cpp)