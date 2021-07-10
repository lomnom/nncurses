#include "nncurses.hpp"
#include <iostream>
#include <time.h>

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
	short transp=-1;
	short grn=2;

	Col256 transpCol(&transp,&transp);
	vector<string> transpEffectsV;
	Effect transpEffects(&transpEffectsV);
	Style transpStyle(&transpCol,&transpEffects);
	string transpString=" ";
	Texture transpTexture(&transpString,&transpStyle);

	Col256 cyanCol(&cyan,&cyan);
	Style cyanStyle(&cyanCol,&transpEffects);
	Texture cyanTexture(&transpString,&cyanStyle);

	int linelen=5;
	HorizLine line(&transpTexture,0,5,&linelen);

	TextLine mspf("",&transpStyle,0,0);
	TextLine fpms("",&transpStyle,0,1);
	TextLine frm("",&transpStyle,0,2);
}

#include <iostream>
#include <chrono>

int main(){
	Terminal terminal(&tex::cyanTexture);
	uint frame=0;

	while (true){
		frame++;
		using std::chrono::high_resolution_clock;
		using std::chrono::duration_cast;
		using std::chrono::duration;
		using std::chrono::milliseconds;

		auto t1 = high_resolution_clock::now();

		terminal.project();
		terminal.updatesize();
		terminal.screen.fill();

		auto t2 = high_resolution_clock::now();
		duration<double, std::milli> ms = t2 - t1;

		if (cinchr()=='q'){
			break;
		}

		tex::mspf.text=to_string(ms.count())+"ms/p";
		tex::mspf.render(&terminal.screen);

		tex::fpms.text=to_string(1/ms.count())+"p/ms";
		tex::fpms.render(&terminal.screen);

		tex::frm.text="frame: "+to_string(frame);
		tex::frm.render(&terminal.screen);

		tex::linelen++;
		tex::line.render(&terminal.screen);
	}

	return 0;
}