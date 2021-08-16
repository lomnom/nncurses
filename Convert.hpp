#ifndef ncConvert
#define ncConvert

#include <array>
using std::array,std::pair;

namespace nc{
	/////////////math
	int16_t minC(array<int16_t,3> col){
		int16_t x= col[0]>col[1] ? col[1] : col[0];
		return x>col[2] ? col[2] : x;
	}

	int16_t maxC(array<int16_t,3> col){
		int16_t x= col[0]<col[1] ? col[1] : col[0];
		return x<col[2] ? col[2] : x;
	}

	int16_t abs(int16_t n){ 
		int16_t const mask = n >> (sizeof(int16_t) * 8 - 1); 
		return ((n + mask) ^ mask);
	} 

	int16_t diff(int16_t a,int16_t b){
		return abs(a-b);
	}

	//how equal all the values in color are
	int16_t greyness(array<int16_t,3> col){ //lmao nonlinear go brrr
		int16_t rDiff=diff(col[0],(col[1]+col[2])/2);
		rDiff=(rDiff*rDiff)/255;
		int16_t gDiff=diff(col[1],(col[0]+col[2])/2);
		gDiff=(gDiff*gDiff)/255;
		int16_t bDiff=diff(col[2],(col[1]+col[0])/2);
		bDiff=(bDiff*bDiff)/255;
		return (rDiff+gDiff+bDiff)/3;
	}

	int16_t brightness(array<int16_t,3> color){ //basically greyscale
		return (0.2126*(float)color[0])+(0.7152*(float)color[1])+(0.0722*(float)color[2]);
	}

	/////////////216 xterm-256color added colors
	int16_t approxNc(int16_t val){ //approx new colors to indexes in xtVals
		if (val<=55) return 0;
		val-=55;
		return val/40;
	}

	int16_t approxNc(array<int16_t,3> color){ //approximate rgb to nearest new color
		return 16+(approxNc(color[0])*36)+(approxNc(color[1])*6)+approxNc(color[2]);
	}

	int16_t xtVals[16]{0,95,135,175,215,255}; //possible r,g or b vals for xterm-256col's extra 116 cols
	array<int16_t,3> ncTOrgb(int16_t nc){
		nc-=16;
		return {xtVals[nc/36],xtVals[(nc%36)/6],xtVals[nc%6]};
	}

	/////////////24 xterm-256 greyscale colors
	int16_t approxGs(int16_t val){
		int16_t res=(val-8)/10;
		if (res>=24) return 231;
		return 232+res;
	}

	int16_t approxGs(array<int16_t,3> color){ //approximate rgb to nearest greyscale
		return approxGs(brightness(color));
	}

	//noneed gsVals, its n*10+8
	array<int16_t,3> gsTOrgb(int16_t gs){
		if (gs==231) return {255,255,255};
		gs-=232;
		int16_t val=gs*10+8;
		return {val,val,val};
	}

	/////////////16 classic colors SKRERERRERERRRERRRRRREEEEE, TODO
	//color also depends on terminal!
	// array<int16_t,4> an8Vals{0,128,192,155};
	// array<int16_t,3> ansi8[16]{ //doesnt deserve to exist
	// 	{0,0,0},
	// 	{128,0,0},
	// 	{0,128,0},
	// 	{128,128,0},
	// 	{0,0,128},
	// 	{128,0,128},
	// 	{0,128,128},
	// 	{192,192,192},
	// 	{128,128,128},
	// 	{255,0,0},
	// 	{0,255,0},
	// 	{255,255,0},
	// 	{0,0,255},
	// 	{255,0,255},
	// 	{0,255,255},
	// 	{255,255,255}
	// };

	/////////////rgb to xterm
	int16_t approxXt(bool gsBlack,uint8_t greynessTresh,uint8_t brightnessTresh,array<int16_t,3> color){ 
		int16_t bright=brightness(color);
		return (gsBlack && (color[0]<95 && color[1]<95 && color[2]<95)) || //change completely black pixels with greyscale
			   bright<brightnessTresh || //make colors darker than brightnessTresh greyscale
			   greyness(color)>greynessTresh //make color grey if greyness > greynessTresh
			   ? approxGs(bright) : approxNc(color);
	}

	array<int16_t,3> xtTOrgb(int16_t xt){
		if (xt>=16){
			if (xt<231){
				return ncTOrgb(xt);
			}else{
				return gsTOrgb(xt);
			}
		}
		throw -1;
	}
}

#undef pair
#undef array
#endif