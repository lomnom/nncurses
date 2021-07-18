#include "../nncurses.hpp"
#include <iostream>
#include <time.h>

//g++ spamGame.cpp --std=c++17 -O3 -o spamgame && ./spamgame

using nc::Col256;
using nc::Effect;
using std::string;
using std::to_string;
using nc::Style;
using nc::Texture;
#define EfctMasks nc::EfctMasks
using nc::TextLine;
using nc::Line;
using nc::cinchr;
using nc::Terminal;

namespace tex{ //textures
	short red=1;
	short cyan=6;
	short black=0;
	short transp=-1;
	short grn=2;

	Col256 bgCol(&cyan,&cyan);
	Effect bgEffect(new uint8_t(0));
	string bgChar(" ");
	Style bgStyle(&bgCol,&bgEffect);
	Texture bgTexture(&bgChar,&bgStyle);

	short textCol=red;
	uint8_t textEffectInt=(EfctMasks::bld);
	Effect textEffect(&textEffectInt);

	uint8_t foldCounterEffectInt=(EfctMasks::bld|EfctMasks::ital);
	Effect foldCounterEffect(&foldCounterEffectInt);

	Col256 lineCol(&red,&red);
	Effect lineEffect(new uint8_t(0));
	string lineChar(" ");
	Style lineStyle(&lineCol,&lineEffect);
	Texture lineTexture(&lineChar,&lineStyle);

	string defaultTextStr="";
	int textStartX=0;

	TextLine msPproj(new string(defaultTextStr),&textCol,&textEffect,&textStartX,new int(0));
	TextLine projPms(new string(defaultTextStr),&textCol,&textEffect,&textStartX,new int(1));
	TextLine frame(new string(defaultTextStr),&textCol,&textEffect,&textStartX,new int(2));

	TextLine foldCounter(new string(defaultTextStr),&textCol,&foldCounterEffect,&textStartX,new int(6));

	int lineLen=0;
	Line spamLine(&lineTexture,new int(0),new int(5),&lineLen,new int(5));
}

#include <iostream>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

int main(){
	Terminal terminal(&tex::bgTexture);
	uint frame=1;
	auto t1 = high_resolution_clock::now();
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> frameTime=t1-t2;

	while (true){
		auto t1 = high_resolution_clock::now();

		terminal.project();
		terminal.updatesize();
		terminal.screen.fill();

		if (!(frame==1)){
			tex::lineLen=frame%(terminal.screen.cols+1);
			tex::spamLine.render(&terminal.screen);

			*(tex::msPproj.text)="msPproj: "+to_string(frameTime.count());
			*(tex::projPms.text)="projPms: "+to_string(1/frameTime.count());
			*(tex::frame.text)="frame: "+to_string(frame);
			*(tex::foldCounter.text)="("+to_string(frame/(terminal.screen.cols+1))+")";

			tex::msPproj.render(&terminal.screen);
			tex::projPms.render(&terminal.screen);
			tex::frame.render(&terminal.screen);
			tex::foldCounter.render(&terminal.screen);
		}

		auto t2 = high_resolution_clock::now();
		frameTime = t2 - t1;

		if (cinchr()=='q'){
			break;
		}

		frame++;
	}

	return 0;
}