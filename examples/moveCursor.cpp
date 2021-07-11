#include "../nncurses.hpp"
#include <iostream>

//g++ tester.cpp --std=c++17 -O3 -o tester && ./tester

using namespace std;

Texture texture(
	new string(" ")
	,new Style(
		new Col256(
			new short(4)
			,new short(4)
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
	
	while (!(ended)){
		terminal.screen.screen[y][x]=&texture;
		// terminal.screen.render(&terminal.screen,5,5); //cool

		terminal.project();
		terminal.updatesize();
		terminal.screen.fill();

		switch (cinchr()){
			case 'w':
				if (!(y==0)){
					y--;
				}
				break;
			case 's':
				if (!(y+1==terminal.screen.rows)){
					y++;
				}
				break;
			case 'd':
				if (!(x+1==terminal.screen.cols)){
					x++;
				}
				break;
			case 'a':
				if (!(x==0)){
					x--;
				}
				break;
			case 'q':
				ended=true;
				break;
			default:
				cout << Esc::bell;
		}
	}
	return 0;
}