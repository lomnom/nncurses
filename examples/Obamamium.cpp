#include "../Escapes.hpp"
#include <iostream>

#define esc nc::Esc
using std::cout;
using std::endl;
using std::string;

// O B A M A M I U M
int main(){
	cout << esc::bgidcol(94);
	cout << "╔═══════════╗" << endl;
	cout << "║    " << esc::fgylw << "420" << esc::rstfg << "    ║" << endl;
	cout << "║     " << esc::bld << "Ö" << esc::unblddim << "     ║" << endl;
	cout << "║ " << esc::uline << "Obamamium" << esc::unuline << " ║" << endl;
	cout << "║ " << esc::ital << "Metalloid" << esc::unital << " ║" << endl;
	cout << "╚═══════════╝" << endl;
	cout << esc::rstbg;
}