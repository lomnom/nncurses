#include "../nncurses.hpp"
#include <iostream>

//g++ moveCursor.cpp --std=c++17 -O3 -o moveCursor && ./moveCursor

using namespace nc;

using namespace nc;
#define string std::string
#define cout std::cout
#define Esc nc::Esc

Texture texture(
	new string("·")
	,new Style(
		new Col256(
			new short(2)
			,new short(3)
		)
		,new Effect(
			new uint8_t(0)
		)
	)
);

Texture background(
	new string(" ")
	,new Style(
		new Col256(
			new short(3)
			,new short(3)
		)
		,new Effect(
			new uint8_t(0)
		)
	)
);

Line line(
	&texture,
	new int(0),
	new int(0),
	new int(40),
	new int(23)
);

int main(){
	Terminal terminal(&background);
	int x=0,y=0;
	bool ended=false;
	bool trippy=false;
	
	while (!(ended)){
		terminal.screen.screen[y][x]=&texture;
		if (trippy){
			terminal.screen.renderPart(&terminal.screen,2,2,0,0,5,5);
			terminal.screen.render(&terminal.screen,5,5);
		}

		terminal.project();
		terminal.updatesize();
		terminal.screen.fill();

		switch (cinchr()){
			case 'w':
				if (!(y==0)){
					y--;
					texture.character=&AscBox::lines[0b11010000];
				}
				break;
			case 's':
				if (!(y+1==terminal.screen.rows)){
					y++;
					texture.character=&AscBox::lines[0b01110000];
				}
				break;
			case 'd':
				if (!(x+1==terminal.screen.cols)){
					x++;
					texture.character=&AscBox::lines[0b00000111];
				}
				break;
			case 'a':
				if (!(x==0)){
					x--;
					texture.character=&AscBox::lines[0b00001101];
				}
				break;
			case 'q':
				ended=true;
				break;
			case 't':
				trippy= !(trippy);
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