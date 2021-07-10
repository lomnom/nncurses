#include "Styles.hpp"
#include "Screens.hpp"

using namespace std;
#ifndef Renderables
#define Renderables

class Renderable{
public:
	virtual void render(Screen*)=0;
};

class HorizLine: public Renderable{
public:
	Texture* texture;
	int startx,starty;
	int* len;
	HorizLine(Texture* text,int x,int y,int* length):startx(x),starty(y),len(length),texture(text){}
	void render(Screen* screen){
		for (int x=startx;(!(x==startx+(*len)));x++){
			if (x>(screen->cols-1)){
				break;
			}
			screen->screen[starty][x]=texture;
		}
	}
};

class TextLine: public Renderable{
public:
	string text;
	Texture templateTexture;
	vector<Texture> textures={};
	vector<string> chars={};
	int startx,starty;
	TextLine(string text,Style* style,int startx,int starty): startx(startx),starty(starty),text(text),templateTexture(&Esc::nothing,style){}

	void render(Screen* screen){
		textures.clear();
		chars.clear();
		for (int n=0;n<text.length();n++){
			chars.push_back(string(1, text.at(n)));
		}
		string*charsBeg=chars.data();

		for (int n=0;n<text.length();n++){
			templateTexture.character=charsBeg+n;
			textures.push_back(templateTexture);
		}
		Texture* textureBeg=textures.data();

		for (int n=0;n<text.length();n++){
			if ((startx+n)>(screen->cols-1)){
				break;
			}
			screen->screen[starty][startx+n]=textureBeg+n;
		}
	}
};

#endif