#include "../Escapes.hpp"
#include <iostream>

#define esc nc::Esc
using std::cout;
using std::string;

string info(string header,string info){
	return esc::bld + header + esc::unblddim + " " + info;
}

// O B A M A M I U M
int main(){
	cout << esc::bgidcol(94) //make it obamacolored
		 << "╔═══════════╗" 
		 << esc::rstbg //undo obamacolor
		 << '\n';

	cout << esc::bgidcol(94)
		 << "║    "
		 << esc::fgylw //yellow text
		 << "420"
		 << esc::rstfg //unyellow text
		 << "    ║"
		 << esc::rstbg
		 << '\n';

	cout << esc::bgidcol(94)
		 << "║     "
		 << esc::bld //bold text
		 << "Ö"
		 << esc::unblddim //ansi only has esc code to unbold and undim
		 << "     ║" 
		 << esc::rstbg 
		 << '\n';

	cout << esc::bgidcol(94) 
		 << "║ Obamamium ║" 
		 << esc::rstbg 
		 << '\n';

	cout << esc::bgidcol(94) 
		 << "║ "       
		 << esc::ital  //italic
		 << "Metalloid" 
		 << esc::unital //unitalic   
		 <<     " ║" 
		 << esc::rstbg 
		 << '\n';

	cout << esc::bgidcol(94) 
		 << "╚═══════════╝" 
		 << esc::rstbg 
		 << '\n';
	
	cout << info("Standard State","solid") << '\n';
	cout << info("Atomic Mass","991.2629 u") << '\n';
	cout << info("Electron Configuration","[Rn]69s21f7") << '\n';
	cout << info("Oxidation States","+21, +69, +420") << '\n';
	cout << info("Electronegativity (Pauling Scale)","6.9") << '\n';
	cout << info("Atomic Radius (van der Waals)","420 pm") << '\n';
	cout << info("Ionization Energy","5.993 eV") << '\n';
	cout << info("Melting Point","6969 K") << '\n';
	cout << info("Boiling Point","42069 K") << '\n';
	cout << info("Density","69.69 g/cm³") << '\n';
	cout << info("Year Discovered","2069") << '\n';
}