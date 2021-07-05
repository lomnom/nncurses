#include "nncurses.hpp"
#include <iostream>

using namespace std;

int main(){
	short red=1;
	short cyan=6;
	short transp=-1;
	short grn=2;

	Col256 Ecolor(&grn,&red);

	vector<string> EeffectsV;
	EeffectsV.push_back("bld");
	EeffectsV.push_back("ital");
	EeffectsV.push_back("uline");
	EeffectsV.push_back("blnk");
	Effect Eeffects(&EeffectsV);

	Style Estyle(&Ecolor,&Eeffects);

	string Estring="E";
	Texture Etexture(&Estring,&Estyle);

	cout << Etexture.getesc() << Esc::crnl;

	return 0;
}
