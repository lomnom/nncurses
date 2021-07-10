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
		return getFgEsc()+getBgEsc();
	}

	string getFgEsc(){
		if (*fg>=0){
			return Esc::fgidcol(*fg);
		}else{
			return Esc::rstfg;
		}
	}

	string getBgEsc(){
		if (*bg>=0){
			return Esc::bgidcol(*bg);
		}else{
			return Esc::rstbg;
		}
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

namespace EfctMasks{
	uint8_t bld=	0b10000000;
	uint8_t dim=	0b01000000;
	uint8_t ital=	0b00100000;
	uint8_t uline=	0b00010000;
	uint8_t blnk=	0b00001000;
	uint8_t inv=	0b00000100;
	uint8_t hid=	0b00000010;
	uint8_t strk=	0b00000001;
}

class Effect{
public: 
	uint8_t* effects;
	Effect(uint8_t* effects):effects(effects){};

	string getesc(){
		string escape="";
		if ((*effects)&EfctMasks::bld){
			escape+=Esc::bld;
		}
		if ((*effects)&EfctMasks::dim){
			escape+=Esc::dim;
		}
		if ((*effects)&EfctMasks::ital){
			escape+=Esc::ital;
		}
		if ((*effects)&EfctMasks::uline){
			escape+=Esc::uline;
		}
		if ((*effects)&EfctMasks::blnk){
			escape+=Esc::blnk;
		}
		if ((*effects)&EfctMasks::inv){
			escape+=Esc::inv;
		}
		if ((*effects)&EfctMasks::hid){
			escape+=Esc::hid;
		}
		if ((*effects)&EfctMasks::strk){
			escape+=Esc::strk;
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

class Texture{
public:
	string* character;
	Style* style;
	Texture(string* characte,Style* styl):style(styl),character(characte){};

	string getesc(){
		return style->getesc() + *character + Esc::rst;
	}

	string getStylEsc(){
		return style->getesc();
	}
};

#endif