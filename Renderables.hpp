#include "Styles.hpp"
#include "Screens.hpp"

using namespace std;
#ifndef Renderables
#define Renderables

//todo: make everything a pointer hehe

class Renderable{
public:
	virtual void render(Screen*)=0;
};

class HorizLine: public Renderable{
public:
	Texture* texture;
	int* startx;
	int* starty;
	int* len;
	HorizLine(Texture* text,int* x,int* y,int* length):startx(x),starty(y),len(length),texture(text){}
	void render(Screen* screen){
		for (int x=(*startx);(!(x==(*startx)+(*len)));x++){
			if (x>(screen->cols-1)){
				break;
			}
			screen->screen[(*starty)][x]=texture;
		}
	}
};

class TextLine: public Renderable{
public:
	string* text;
	int* startx;
	int* starty;
	Style* style;
	TextLine(string* text,Style* style,int* startx,int* starty): startx(startx),starty(starty),text(text),style(style){}

	void render(Screen* screen){
		for (int n=0;n<text->length();n++){
			if (((*startx)+n)>(screen->cols-1)){
				break;
			}
			screen->screen[(*starty)][(*startx)+n]=new Texture(new string(1,text->at(n)),style);
		}
	}
};

#endif