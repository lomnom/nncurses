#include "nncurses.hpp"
#include <iostream>

using namespace std;

int main(){
	short red=1;
	short cyan=6;
	short transp=-1;
	short grn=2;

	Col256 cyanfg(&cyan,&transp);
	Col256 redbg(&transp,&red);
	Col256 grnbg(&transp,&grn);

	Col256 cyanred=cyanfg;
	cyanred.layerontop(redbg);

	vector<string> ital;
	ital.push_back("ital");
	ital.push_back("bld");
	Effect effects(&ital);

	Style Estyle(&cyanred,&effects);

	cout << Estyle.getesc() + "lmao" + Esc::rst + " ";

	Style grnbgstyle(&grnbg,Estyle.effect);
	Estyle.layerontop(grnbgstyle);

	cout << Estyle.getesc() << "wut" + Esc::rst + Esc::crnl;

	return 0;
}
