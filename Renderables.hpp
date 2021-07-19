#include "Styles.hpp"
#include "Screens.hpp"
#include "Escapes.hpp"

#ifndef Renderables
#define Renderables

#define string std::string
#define vector std::vector

namespace nc{
	template<class T>
	T abs(T x){
		return (x>0 ? x : -x);
	}

	template<class T>
	T smaller(T a,T b){
		return a>b ? b : a;
	}

	template<class T>
	T btwn(T a,T b){ //get between of 2 vals
		return smaller(a,b)+(abs(a-b)/2);
	}

	template<class T>
	T midOfst(T a,T b){ //get middle val with an offset of 2nd arg/2
		return (a/2)-(b/2);
	}

	template<class T>
	T toroid(T a, T b) {
		if(b < 0) return toroid(-a, -b);
		int result = a % b;
		return result >= 0 ? result : result + b;
	}

	void bresenham(Screen* screen,Texture* texture,int startX,int startY,int endX,int endY){
		int biggerX=startX>endX ? startX : endX;
		int smallerX=startX<endX ? startX : endX;

		int biggerY=startY>endY ? startY : endY;
		int smallerY=startY<endY ? startY : endY;

		int diffX=biggerX-smallerX;
		int diffY=biggerY-smallerY;

		int D=2*diffY-diffX;
		screen->screen[smallerY][smallerX]=texture;
		int y=startY>endY ? endY : startY;

		for (int x=smallerX;x<biggerX;x++){
			if (D>0){
				y++;
				screen->screen[y][x]=texture;
				D += (2*diffY-2*diffX);
			}else{
				screen->screen[y][x]=texture;
				D += 2*diffY;
			}
		}
	}

	class Renderable{
	public:
		virtual void render(Screen*)=0;
	};

	class Line: public Renderable{
	public:
		Texture* texture;
		int* startx;
		int* starty;
		int* endx;
		int* endy;
		Line(Texture* text,int* startx,int* starty,int* endx,int* endy):startx(startx),starty(starty),endx(endx),endy(endy),texture(text){}

		void render(Screen* screen){
			bresenham(screen,texture,*startx,*starty,*endx,*endy);
		}
	};

	class HollowRectangle: public Renderable{
	public:
		Texture* top;
		Texture* bottom;
		Texture* left;
		Texture* right;
		Texture* TLCorner;
		Texture* TRCorner;
		Texture* BLCorner;
		Texture* BRCorner;
		int* startx;
		int* starty;
		int* height;
		int* width;
		HollowRectangle(int* startx,int* starty,int* height,int* width,Texture* texture):
			top(texture),
			bottom(texture),
			left(texture),
			right(texture),
			TLCorner(texture),
			TRCorner(texture),
			BLCorner(texture),
			BRCorner(texture),
			startx(startx),
			starty(starty),
			height(height),
			width(width){}

		HollowRectangle(int* startx,int* starty,int* height,int* width,Texture* texture,Texture* cornerTexture):
			top(texture),
			bottom(texture),
			left(texture),
			right(texture),
			TLCorner(cornerTexture),
			TRCorner(cornerTexture),
			BLCorner(cornerTexture),
			BRCorner(cornerTexture),
			startx(startx),
			starty(starty),
			height(height),
			width(width){}

		HollowRectangle(int* startx,int* starty,int* height,int* width,Texture* horizTexture,Texture* vertTexture,Texture* cornerTexture):
			top(horizTexture),
			bottom(horizTexture),
			left(vertTexture),
			right(vertTexture),
			TLCorner(cornerTexture),
			TRCorner(cornerTexture),
			BLCorner(cornerTexture),
			BRCorner(cornerTexture),
			startx(startx),
			starty(starty),
			height(height),
			width(width){}

		HollowRectangle(int* startx,int* starty,int* height,int* width,Texture* horizTexture,Texture* vertTexture,Texture* TLCorner,Texture* TRCorner,Texture* BLCorner,Texture* BRCorner):
			top(horizTexture),
			bottom(horizTexture),
			left(vertTexture),
			right(vertTexture),
			TLCorner(TLCorner),
			TRCorner(TRCorner),
			BLCorner(BLCorner),
			BRCorner(BRCorner),
			startx(startx),
			starty(starty),
			height(height),
			width(width){}

		void render(Screen* screen){
			int endx= *startx+ *width-1;
			int endy= *starty+ *height-1;
			for (int x= *startx;x<=endx;x++){
				screen->screen[ *starty][x]=top;
				screen->screen[endy][x]=bottom;
			}
			for (int y= *starty;y<=endy;y++){
				screen->screen[y][ *startx]=left;
				screen->screen[y][endx]=right;
			}
			screen->screen[ *starty][ *startx]=TLCorner;
			screen->screen[endy][endx]=BRCorner;
			screen->screen[ *starty][endx]=TRCorner;
			screen->screen[endy][ *startx]=BLCorner;
		}
	};

	class TextLine: public Renderable{ //MEMLEAKKKKKK (gone)
	public:
		string* text;
		int* startx;
		int* starty;
		short* color;
		vector<Texture*> chars;
		Effect* effects;
		TextLine(string* text,short* color,Effect* effects,int* startx,int* starty): startx(startx),starty(starty),text(text),color(color),effects(effects){}

		void render(Screen* screen){ //preserves bg col!!!!!!
			deallocChars();

			for (int n=0;n<text->length();n++){
				chars.push_back(
					new Texture(
						new string(1,text->at(n))
						,new Style(
							new Col256(color,screen->screen[(*starty)][(*startx)+n]->style->color->bg),
							effects
						)
					)
				);
				screen->screen[(*starty)][(*startx)+n]=chars[n];
			}
		}

		void deallocChars(){
			for (int n=0;n<chars.size();n++){ //dealloc old chars
				delete chars[n]->character;
				delete chars[n]->style->color;
				delete chars[n]->style;
				delete chars[n];
			}
			chars.erase(chars.begin(),chars.end());
		}

		~TextLine(){
			deallocChars();
		}
	};
}

#undef string
#undef vector

#endif