#include "../Raw.hpp"
#include "../Escapes.hpp"
#include "../EscFunc.hpp"
#include "../Utils.hpp"
#include <thread>
#include <vector>
#include <iostream>

using std::cout;
namespace esc=nc::Esc;
using nc::RawController,std::vector,std::thread,nc::cinchr;

bool earbleeding=true;
int cores=std::thread::hardware_concurrency();

void earBleed(){
	while (earbleeding){
		cout << '\a';
	}
}

int main(){
	cout << "Press " << esc::bld << "q" << esc::unblddim << " to end this " << esc::fgred << "hell" <<esc::rstfg;
	cout << '\n';

	RawController rawctrl;
	rawctrl.raw();

	thread threads[cores];
	for (int n=0;n<cores;n++){
		threads[n]=thread(earBleed);
	}

	while (!(cinchr()=='q')){
	}

	earbleeding=false;
	for (int n=0;n<cores;n++){
		threads[n].join();
	}

	rawctrl.unraw();
}