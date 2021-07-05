#ifndef Styles
#define Styles

#include <string>
#include <vector>
#include "Escapes.hpp"
using namespace std;

class Col256{ //less than 0 is transparent
public:
	short* fg;
	short* bg;
	Col256(short* fgid,short* bgid): fg(fgid),bg(bgid){}

	string getesc(){
		string escape="";
		if (*fg>=0){
			escape=Esc::fgidcol(*fg);
		}
		if (*bg>=0){
			escape+=Esc::bgidcol(*bg);
		}
		return escape;
	}

	void layerontop(Col256 othcol){ //layer another color onto self
		if (*(othcol.fg)>=0){
			fg=othcol.fg;
		}
		if (*(othcol.bg)>=0){
			bg=othcol.bg;
		}
	}
};

class Effect{
public: 
	vector<string>* effects;
	string escape;

	Effect(vector<string>* v):effects(v){};

	string getesc(){
		escape="";
		for (int i=0;!(i==(*effects).size());i++){
			if ((*effects)[i]=="bld"){
				escape+=Esc::bld;
			}
			if ((*effects)[i]=="dim"){
				escape+=Esc::dim;
			}
			if ((*effects)[i]=="ital"){
				escape+=Esc::ital;
			}
			if ((*effects)[i]=="uline"){
				escape+=Esc::uline;
			}
			if ((*effects)[i]=="blnk"){
				escape+=Esc::blnk;
			}
			if ((*effects)[i]=="inv"){
				escape+=Esc::inv;
			}
			if ((*effects)[i]=="hid"){
				escape+=Esc::hid;
			}
			if ((*effects)[i]=="strk"){
				escape+=Esc::strk;
			}
		};
		return escape;
	}
};

class Style{
public:
	Col256* color;
	Effect* effect;
	Style(Col256* col, Effect* e){
		color=col;
		effect=e;
	}

	void layerontop(Style style){
		color->layerontop(*(style.color));
		effect=style.effect;
	};

	string getesc(){
		return color->getesc()+effect->getesc();
	}
};

// class Texture{
// public:
// 	string character;
// 	Style style;
// 	Texture(String character,Style sty)
// };

#endif