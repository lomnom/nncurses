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
		int16_t fg;
		int16_t bg;
		Col256(int16_t fgid,int16_t bgid): fg(fgid),bg(bgid){}

		string getesc(){
			return getFgEsc()+getBgEsc();
		}

		string getFgEsc(){
			return fg>=0 ? Esc::fgidcol(fg) : Esc::rstfg;
		}

		string getBgEsc(){
			return bg>=0 ? Esc::bgidcol(bg) : Esc::rstfg;
		}

		Col256 operator+(Col256 othcol){ //layer another color onto self
			Col256 resultCol(othcol.fg>=0 ? othcol.fg : fg,othcol.bg>=0 ? othcol.bg : bg);
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
		uint8_t none=	0b00000000;
	}

	class Effect{
	public: 
		uint8_t effects;
		Effect(uint8_t effects):effects(effects){};

		string getesc(){
			string escape="";
			if ((effects)&EfctMasks::bld){
				escape+=Esc::bld;
			}
			if ((effects)&EfctMasks::dim){
				escape+=Esc::dim;
			}
			if ((effects)&EfctMasks::ital){
				escape+=Esc::ital;
			}
			if ((effects)&EfctMasks::uline){
				escape+=Esc::uline;
			}
			if ((effects)&EfctMasks::blnk){
				escape+=Esc::blnk;
			}
			if ((effects)&EfctMasks::inv){
				escape+=Esc::inv;
			}
			if ((effects)&EfctMasks::hid){
				escape+=Esc::hid;
			}
			if ((effects)&EfctMasks::strk){
				escape+=Esc::strk;
			};
			return escape;
		}
		
		Effect operator+(Effect othEffect){
			uint8_t resEffects=(effects|othEffect.effects);
			Effect resEffect(resEffects);
			return resEffect;
		}
	};

	class Style{
	public:
		Col256 color;
		Effect effect;
		Style(Col256 col, Effect e): color(col),effect(e){}

		Style(int16_t fg, int16_t bg, Effect e): color(Col256(fg,bg)),effect(e){}

		Style(Col256 col, uint8_t e): color(col),effect(Effect(e)){}

		Style(int16_t fg, int16_t bg, uint8_t e): color(Col256(fg,bg)),effect(Effect(e)){}

		string getesc(){
			return color.getesc()+effect.getesc();
		}
	};

	class Texture{
	public:
		string character;
		Style style;
		Texture(string characte,Style styl):style(styl),character(characte){};

		string getesc(){
			return style.getesc() + character + Esc::rst;
		}
	};
}

#undef Esc
#undef string 
#undef vector 

#endif