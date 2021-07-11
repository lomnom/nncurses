#include "nncurses.hpp"
#include <iostream>
#include <time.h>

//g++ tester.cpp --std=c++17 -O3 -o tester && ./tester

using namespace std;

#include <iostream>

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
	Screen screen(terminal.screen.rows,terminal.screen.cols,&background,new int(0),new int(0));

	line.render(&screen);
	screen.render(&terminal.screen);

	terminal.project();

	cinchr();
	return 0;
}