#include "Styles.hpp"
#include "Screens.hpp"

using namespace std;
#ifndef Renderables
#define Renderables

class HorizLine{
public:
	Texture* texture;
	int startx,starty;
	int* len;
	HorizLine(Texture* text,int x,int y,int* length):startx(x),starty(y),len(length),texture(text){}
	void render(Screen* screen){
		for (int x=startx;(!(x==startx+(*len)));x++){
			if (x>(screen->size->cols-1)){
				break;
			}
			screen->screen[starty][x]=texture;
		}
	}
};

#endif