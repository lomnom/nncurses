#ifndef Styles
#define Styles

#include <string>
#include <vector>
#include "Escapes.hpp"

#define Esc nc::Esc
#define string std::string
#define vector std::vector

namespace nc{
	class Col256{ //less than 0 is transparent
	public:
		short* fg;
		short* bg;
		string escape,fgEsc,bgEsc;
		Col256(short* fgid,short* bgid): fg(fgid),bg(bgid){
			getFgEsc();
			getBgEsc();
			getesc();
		}

		void getesc(){
			escape=fgEsc+bgEsc;
		}

		void getFgEsc(){
			fgEsc= *fg>=0 ? Esc::fgidcol(*fg) : "";
		}

		void getBgEsc(){
			bgEsc= *bg>=0 ? Esc::bgidcol(*bg) : "";
		}

		Col256 operator+(Col256 othcol){ //layer another color onto self
			Col256 resultCol(*(othcol.fg)>=0 ? othcol.fg : fg,*(othcol.bg)>=0 ? othcol.bg : bg);
			return resultCol;
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
		string escape;
		Effect(uint8_t* effects):effects(effects){
			getesc();
		};

		void getesc(){
			escape="";
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
		}
		
		Effect operator+(Effect othEffect){ //yay memleak
			uint8_t resEffects=(*effects|*othEffect.effects);
			Effect resEffect(&resEffects);
			return resEffect;
		}
	};

	class Style{
	public:
		Col256* color;
		Effect* effect;
		string escape;
		Style(Col256* col, Effect* e): color(col),effect(e){
			getesc();
		}

		void getesc(){
			escape=color->escape+effect->escape;
		}
	};

	class Texture{
	public:
		string* character;
		Style* style;
		string escape,stylEsc;
		Texture(string* characte,Style* styl):style(styl),character(characte){
			getesc();
			getStylEsc();
		};

		void getesc(){
			escape=style->escape + *character + Esc::rst;
		}

		void getStylEsc(){
			stylEsc=style->escape;
		}
	};
}

#undef Esc
#undef string 
#undef vector 

#endif