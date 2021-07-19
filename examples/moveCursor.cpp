#include "../nncurses.hpp"
#include <iostream>

//g++ moveCursor.cpp --std=c++17 -O3 -o moveCursor && ./moveCursor

using std::string,std::stoi,std::to_string,std::cout;
using nc::toroid,nc::Effect,nc::Texture,nc::Col256,nc::Style,nc::midOfst,nc::HollowRectangle,nc::TextLine,nc::Terminal,nc::cinchr;
namespace AscBox=nc::AscBox;
namespace Esc=nc::Esc;

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
	winStartX=midOfst(terminal.screen.cols,winWidth);
	winStartY=midOfst(terminal.screen.rows,winHeight);
	txtY=winStartY+1;
	txtX=midOfst(terminal.screen.cols,(int)tpTxtStr.size());

	string inX="";
	string inY=inX;
	uint8_t phase=0;

	while (true){
		if (phase){
			inTxtStr="x: "+inX+" y: "+inY;
		}else{
			inTxtStr="x: "+inX;
		}

		inTxtY=winStartY+2;
		inTxtX=midOfst(terminal.screen.cols,(int)inTxtStr.size());
		terminal.screen.fill();
		inText.render(&terminal.screen);
		tpText.render(&terminal.screen);
		tpWin.render(&terminal.screen);
		terminal.project();

		char inChar=cinchr();
		if (std::isdigit(inChar)){
			if (phase){
				inY+=inChar;
			}else{
				inX+=inChar;
			}
		}else{
			if (phase){
				if (!(inY.size()==0)){
					break;
				}
			}else{
				if (!(inX.size()==0)){
					phase++;
				}
			}
		}
	}

	terminal.screen.fill();

	*y=stoi(inY)%terminal.screen.rows;
	*x=stoi(inX)%terminal.screen.cols;
}

string helpTxtStr="w,a,s,d: movement, Q: quit, T: toggle trippy, M: teleport, D: show coords";
int helpTxtX=0;
int helpTxtY=0;
TextLine helpText(&helpTxtStr,white,effects,&helpTxtX,&helpTxtY);

int helpWinStartX=0;
int helpWinStartY=0;
int helpWinHeight=3;
int helpWinWidth=75;
HollowRectangle helpWin(&helpWinStartX,&helpWinStartY,&helpWinHeight,&helpWinWidth,&horizLine,&vertLine,&corner);

void help(){
	helpWinStartX=midOfst(terminal.screen.cols,helpWinWidth);
	helpWinStartY=midOfst(terminal.screen.rows,helpWinHeight);
	helpTxtX=helpWinStartX+1;
	helpTxtY=helpWinStartY+1;
	terminal.screen.fill();
	helpText.render(&terminal.screen);
	helpWin.render(&terminal.screen);
	terminal.project();
	cinchr();
	terminal.screen.fill();
}

int main(){
	int x=0,y=0;
	bool ended=false;
	bool trippy=false;
	bool debug=false;
	
	while (!(ended)){
		terminal.screen.screen[toroid(y,terminal.screen.rows)][toroid(x,terminal.screen.cols)]=&texture;
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
				y--;
				texture.character=&AscBox::lines[0b11010000];
				break;
			case 's':
				y++;
				texture.character=&AscBox::lines[0b01110000];
				break;
			case 'd':
				x++;
				texture.character=&AscBox::lines[0b00000111];
				break;
			case 'a':
				x--;
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
			case 'H':
				help();
			default:
				cout << Esc::bell;
		}
	}
	return 0;
}