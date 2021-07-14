#include "Styles.hpp"
#include "Screens.hpp"

using namespace std;
#ifndef Renderables
#define Renderables

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
			if ((x>=screen->cols)||(y>=screen->rows)){
				break;
			}
			screen->screen[y][x]=texture;
			D += (2*diffY-2*diffX);
		}else{
			if ((x>=screen->cols)||(y>=screen->rows)){
				break;
			}
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

class TextLine: public Renderable{ //h o w to o p t i m i s e
public:
	string* text;
	int* startx;
	int* starty;
	Style* style;
	vector<Texture*> chars;
	TextLine(string* text,Style* style,int* startx,int* starty): startx(startx),starty(starty),text(text),style(style){}

	void render(Screen* screen){
		for (int n=0;n<chars.size();n++){ //dealloc old chars
			delete chars[n]->character;
			delete chars[n];
		}
		chars.erase(chars.begin(),chars.end());

		for (int n=0;(n<text->length())&&(!(((*startx)+n)>(screen->cols-1)));n++){
			chars.push_back(new Texture(new string(1,text->at(n)),style));
			screen->screen[(*starty)][(*startx)+n]=chars[n];
		}
	}
};

class Text: public Renderable{ //gotta do this lmao

};

#endif