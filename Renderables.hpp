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
	T diff(T a,T b){
		return abs(a-b);
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

	void bresenham(Screen* screen,Texture texture,int startx, int starty, int endx, int endy){
		int dx, dy, p, x, y;
		dx=endx-startx;
		dy=endy-starty;
		
		x=startx;
		y=starty;
		screen->screen[x][y]=texture;
		
		p=2*dy-dx;
		
		while(x<endx){
			if(p>=0){
				screen->screen[x][y]=texture;
				y=y+1;
				p= p+ 2*dy - 2*dx ;
			} else{
				screen->screen[x][y]=texture;
				p= p+ 2*dy;
			}
			x=x+1;
		}
	}

	class Renderable{
	public:
		virtual void render(Screen*)=0;
	};

	// class Line: public Renderable{ //NOT WORKING SKRE
	// public:
	// 	Texture texture;
	// 	int startx;
	// 	int starty;
	// 	int endx;
	// 	int endy;
	// 	Line(Texture text,int startx,int starty,int endx,int endy):startx(startx),starty(starty),endx(endx),endy(endy),texture(text){}

	// 	void render(Screen* screen){ // FLAWED, DOESNT WORK TODO: FIX
	// 		bresenham(screen,texture,startx,starty,endx,endy);
	// 	}
	// };

	class HollowRectangle: public Renderable{
	public:
		Texture top;
		Texture bottom;
		Texture left;
		Texture right;
		Texture TLCorner;
		Texture TRCorner;
		Texture BLCorner;
		Texture BRCorner;
		int startx;
		int starty;
		int height;
		int width;
		HollowRectangle(int startx,int starty,int height,int width,Texture texture):
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

		HollowRectangle(int startx,int starty,int height,int width,Texture texture,Texture cornerTexture):
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

		HollowRectangle(int startx,int starty,int height,int width,Texture horizTexture,Texture vertTexture,Texture cornerTexture):
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

		HollowRectangle(int startx,int starty,int height,int width,Texture horizTexture,Texture vertTexture,Texture TLCorner,Texture TRCorner,Texture BLCorner,Texture BRCorner):
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
			int endx= startx+ width-1;
			int endy= starty+ height-1;
			for (int x= startx ; x<=endx ; x++){
				screen->screen[starty][x]=top;
				screen->screen[endy][x]=bottom;
			}
			for (int y= starty;y<=endy;y++){
				screen->screen[y][startx]=left;
				screen->screen[y][endx]=right;
			}
			screen->screen[starty][startx]=TLCorner;
			screen->screen[endy][endx]=BRCorner;
			screen->screen[starty][endx]=TRCorner;
			screen->screen[endy][startx]=BLCorner;
		}
	};

	class Text: public Renderable{
	public:
		string text;
		int startx;
		int starty;
		Style style;
		Text(string text,Style style,int startx,int starty): startx(startx),starty(starty),text(text),style(style){}
		Text(string text,Style style): startx(0),starty(0),text(text),style(style){}

		void render(Screen* scr){
			int y=starty;
			int x=startx;
			for (int n=0;n<text.size();n++){
				string currCh(1,text.at(n));

				if (currCh=="\n"){
					y++;
					x=startx;
					continue;
				}else{
					scr->screen[y][x]=Texture(currCh,style);
				}
				x++;
			}
		}
	};

	class TranspText: public Renderable{
	public:
		string text;
		int startx;
		int starty;
		Effect effects;
		short fg;
		TranspText(string text,Effect effects,short fg,int startx,int starty): startx(startx),starty(starty),text(text),fg(fg),effects(effects){}
		TranspText(string text,Effect effects,short fg): startx(0),starty(0),text(text),fg(fg),effects(effects){}

		void render(Screen* scr){
			int y=starty;
			int x=startx;
			for (int n=0;n<text.size();n++){
				string currCh(1,text.at(n));

				if (currCh=="\n"){
					y++;
					x=startx;
					continue;
				}else{
					scr->screen[y][x]=Texture(
						currCh,
						Style(
							Col256(
								fg,
								scr->screen[y][x].style.color.bg
							),
							effects
						)
					);
				}
				x++;
			}
		}
	};
}

#undef string
#undef vector

#endif