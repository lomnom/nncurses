#include "../nncurses.hpp"
#include <iostream>

//g++ moveCursor.cpp --std=c++17 -O3 -o moveCursor && ./moveCursor

using std::string,std::stoi,std::to_string,std::cout;
using nc::toroid,nc::Effect,nc::Texture,nc::Col256,nc::Style,nc::midOfst,nc::HollowRectangle,nc::Text,nc::Terminal,nc::cinchr,nc::lines;
namespace Esc=nc::Esc;

Texture texture("·",Style(252,256,0));
Texture background(" ",Style(252,256,0));

Texture vertLine("|",Style(252,256,0));
Texture horizLine("-",Style(252,256,0));
Texture corner("+",Style(252,256,0));

HollowRectangle tpWin(
	0,0, //x,y
	4,32, //height,width
	horizLine,
	vertLine,
	corner
);

Text tpText("enter the coordinates to tp to",Style(252,256,0),0,0);
Text inText("",Style(252,256,0),0,0);
Text debText("",Style(252,256,0),0,0); //shows coords

Terminal terminal(background);

Text helpText(
	"w,a,s,d: movement\nq: quit\nt: toggle trippy\nm: teleport\nc: show coords",
	Style(252,256,0),
	0,0
);

HollowRectangle helpWin(0,0,7,19,horizLine,vertLine,corner);

int main(){
	int x=0,y=0;
	bool trippy=false;
	bool debug=false;
	
	while (true){
		terminal.screen.screen[toroid(y,terminal.screen.rows)][toroid(x,terminal.screen.cols)]=texture;
		if (trippy){
			terminal.screen.renderPart(&terminal.screen,2,2,0,0,5,5); //ok
			terminal.screen.renderPart(&terminal.screen,5,5,0,0,terminal.screen.cols-5,terminal.screen.rows-5);
		}
		if(debug){
			debText.text="x: "+to_string(x)+", y: "+to_string(y)+", trippy: "+(trippy ? "true" : "false");
			debText.render(&terminal.screen);
		}
		terminal.project();
		terminal.updatesize();
		terminal.screen.fill();

		char keyCh=cinchr();
		if (keyCh=='w'){
			y--;
			texture.character=lines[0b11010000];
		}else if (keyCh=='s'){
			y++;
			texture.character=lines[0b01110000];
		}else if (keyCh=='d'){
			x++;
			texture.character=lines[0b00000111];
		}else if (keyCh=='a'){
			x--;
			texture.character=lines[0b00001101];
		}else if (keyCh=='q'){
			break;
		}else if (keyCh=='t'){
			trippy= !(trippy);
		}else if (keyCh=='m'){
			tpWin.startx=midOfst(terminal.screen.cols,tpWin.width);
			tpWin.starty=midOfst(terminal.screen.rows,tpWin.height);
			tpText.starty=tpWin.starty+1;
			tpText.startx=midOfst(terminal.screen.cols,(int)tpText.text.size());

			string inX="";
			string inY="";
			uint8_t phase=0;

			while (true){
				if (phase){
					inText.text="x: "+inX+" y: "+inY;
				}else{
					inText.text="x: "+inX;
				}

				inText.starty=tpWin.starty+2;
				inText.startx=midOfst(terminal.screen.cols,(int)tpText.text.size());
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

			y=stoi(inY);
			x=stoi(inX);
		}else if (keyCh=='c'){
			debug= !(debug);
		}else if (keyCh=='h'){
			helpWin.startx=midOfst(terminal.screen.cols,helpWin.width);
			helpWin.starty=midOfst(terminal.screen.rows,helpWin.height);
			helpText.startx=helpWin.startx+1;
			helpText.starty=helpWin.starty+1;
			terminal.screen.fill();
			helpText.render(&terminal.screen);
			helpWin.render(&terminal.screen);
			terminal.project();
			cinchr();
			terminal.screen.fill();
		}else{
			cout << Esc::bell;
		}
	}
	return 0;
}