#include "nncurses.hpp"
#include <iostream>

using namespace std;

int main(){
	canon();
	noecho();

	cinchr();
	cinchr();

	nocanon();
	echo();
	return 0;
}