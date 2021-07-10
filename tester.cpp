#include "nncurses.hpp"
#include <iostream>
#include <time.h>

//g++ tester.cpp --std=c++17 -O3 -o tester && ./tester

using namespace std;

int sleep(int sec,int msec,int mcrsec,int nsec){
	struct timespec timeSec;
	struct timespec timeNsec;
	timeSec.tv_sec=sec;
	timeNsec.tv_nsec=nsec+(((msec*1000)+mcrsec)*1000);
	return nanosleep(&timeSec,&timeNsec);
}

namespace tex{ //textures
	short red=1;
	short cyan=6;
	short black=0;
	short transp=-1;
	short grn=2;

	Col256 transpCol(&transp,&transp);
	Effect transpEffects(new uint8_t(0));
	Style transpStyle(&transpCol,&transpEffects);
	string transpString=" ";
	Texture transpTexture(&transpString,&transpStyle);

	Col256 cyanCol(&cyan,&cyan);
	Style cyanStyle(&cyanCol,&transpEffects);
	Col256 cyanBgCol(&black,&cyan);
	Style cyanBgStyle(&cyanBgCol,&transpEffects);
	Col256 redBgCol(&black,&red);
	Style redBgStyle(&redBgCol,&transpEffects);
	Texture redTexture(&transpString,&redBgStyle);
	Texture cyanTexture(&transpString,&cyanStyle);

	int linelen=0;
	HorizLine line(&redTexture,new int(0),new int(5),&linelen);

	int textStartX=0;
	TextLine mspf(new string(""),&cyanBgStyle,&textStartX,new int(0));
	TextLine fpms(new string(""),&cyanBgStyle,&textStartX,new int(1));
	TextLine frm(new string(""),&cyanBgStyle,&textStartX,new int(2)); //frame
	int crossovers=0;
	TextLine flds(new string(""),&cyanBgStyle,&textStartX,new int(6));
}

#include <iostream>
#include <chrono>

int main(){
	Terminal terminal(&tex::cyanTexture);
	uint frame=0;
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	auto t1 = high_resolution_clock::now();
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms = t2 - t1;

	while (true){
		frame++;

		auto t1 = high_resolution_clock::now();

		terminal.project();
		terminal.updatesize();
		terminal.screen.fill();

		auto t2 = high_resolution_clock::now();
		duration<double, std::milli> ms = t2 - t1;

		if (cinchr()=='q'){
			break;
		}

		*(tex::mspf.text)=to_string(ms.count())+"ms/p";
		tex::mspf.render(&terminal.screen);

		*(tex::fpms.text)=to_string(1/ms.count())+"p/ms";
		tex::fpms.render(&terminal.screen);

		*(tex::frm.text)="frame: "+to_string(frame);
		tex::frm.render(&terminal.screen);

		if (((tex::linelen)%terminal.screen.cols)==0){
			tex::crossovers++;
		}

		tex::linelen=((tex::linelen)%terminal.screen.cols)+1;
		tex::line.render(&terminal.screen);

		*(tex::flds.text)="("+to_string(tex::crossovers)+")";
		tex::flds.render(&terminal.screen);
	}

	return 0;
}