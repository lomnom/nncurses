#include "../nncurses.hpp"
#include <iostream>

//g++ moveCursor.cpp --std=c++17 -O3 -o moveCursor && ./moveCursor

using namespace nc;

using namespace nc;
#define string std::string
#define stoi std::stoi
#define to_string std::to_string
#define cout std::cout
#define Esc nc::Esc

short* black=new short(256);
short* white=new short(252);

uint8_t* effectsint=new uint8_t(0);
Effect* effects=new Effect(effectsint);

Texture texture(new string("·"),new Style(new Col256(white,black),effects));
Texture background(new string(" "),new Style(new Col256(black,black),effects));

Texture vertLine(new string("|"),new Style(new Col256(white,black),effects));
Texture horizLine(new string("-"),new Style(new Col256(white,black),effects));
Texture corner(new string("+"),new Style(new Col256(white,black),effects));

int winStartX=0;
int winStartY=0;
int winHeight=4;
int winWidth=32;
HollowRectangle tpWin(&winStartX,&winStartY,&winHeight,&winWidth,&horizLine,&vertLine,&corner);

int txtX=0;
int txtY=0;
string tpTxtStr="enter the coordinates to tp to";
TextLine tpText(&tpTxtStr,white,effects,&txtX,&txtY);

int inTxtX=0;
int inTxtY=0;
string inTxtStr="";
TextLine inText(&inTxtStr,white,effects,&inTxtX,&inTxtY);

string debTxtStr="";
int debTxtX=0;
int debTxtY=0;
TextLine debText(&debTxtStr,white,effects,&debTxtX,&debTxtY);

Terminal terminal(&background);

void teleportHandle(int* x,int* y){
	winStartX=(terminal.screen.cols/2)-(winWidth/2);
	winStartY=(terminal.screen.rows/2)-(winHeight/2);
	txtY=winStartY+1;
	txtX=(terminal.screen.cols/2)-16+1;
	terminal.screen.fill();
	tpText.render(&terminal.screen);
	tpWin.render(&terminal.screen);
	terminal.project();

	char inChar;
	string inX="";
	string inY=inX;
	uint8_t phase=0;

	while (true){
		inChar=cinchr();
		if (std::isdigit(inChar)){
			if (phase){
				inY+=inChar;
			}else{
				inX+=inChar;
			}
		}else{
			if (phase){
				break;
			}else{
				phase++;
			}
		}

		if (phase){
			inTxtStr="x: "+inX+" y: "+inY;
		}else{
			inTxtStr="x: "+inX;
		}

		inTxtY=winStartY+2;
		inTxtX=(terminal.screen.cols/2)-(inTxtStr.size()/2)+1;
		terminal.screen.fill();
		inText.render(&terminal.screen);
		tpText.render(&terminal.screen);
		tpWin.render(&terminal.screen);
		terminal.project();
	}

	terminal.screen.fill();

	*y=stoi(inY)%terminal.screen.rows;
	*x=stoi(inX)%terminal.screen.cols;
}

int main(){
	int x=0,y=0;
	bool ended=false;
	bool trippy=false;
	bool debug=false;
	
	while (!(ended)){
		terminal.screen.screen[y][x]=&texture;
		if (trippy){
			terminal.screen.renderPart(&terminal.screen,2,2,0,0,5,5);
			terminal.screen.render(&terminal.screen,5,5);
		}
		if(debug){
			debTxtStr="x: "+to_string(x)+", y: "+to_string(y)+", trippy: "+(trippy ? "true" : "false");
			debText.render(&terminal.screen);
		}
		terminal.project();
		terminal.updatesize();
		terminal.screen.fill();

		switch (cinchr()){
			case 'w':
				y= 0<y ? y-1 : terminal.screen.rows-1;
				texture.character=&AscBox::lines[0b11010000];
				break;
			case 's':
				y=(y+1)%terminal.screen.rows;
				texture.character=&AscBox::lines[0b01110000];
				break;
			case 'd':
				x=(x+1)%terminal.screen.cols;
				texture.character=&AscBox::lines[0b00000111];
				break;
			case 'a':
				x= 0<x ? x-1 : terminal.screen.cols-1;
				texture.character=&AscBox::lines[0b00001101];
				break;
			case 'Q':
				ended=true;
				break;
			case 'T':
				trippy= !(trippy);
				break;
			case 'M':
				teleportHandle(&x,&y);
				break;
			case 'D':
				debug= !(debug);
				break;
			default:
				cout << Esc::bell;
		}
	}
	return 0;
}

#undef Esc
#undef string 
#undef cout