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
}

int main(){
	Terminal terminal(&tex::cyanTexture);

	while (true){
		tex::line.render(&terminal.screen);
		terminal.project();
		sleep(0,0,16666,0);
		if (cinchr()=='q'){
			break;
		}else{
			tex::linelen++;
		}
	}

	return 0;
}