#include "Styles.hpp"
#include "Raw.hpp"
#include "EscFunc.hpp"

#ifndef Screens
#define Screens
using namespace std;

class ScrSize{
public:
	int cols,rows,maxy,maxx;
	ScrSize(int cols,int rows): cols(cols), rows(rows) ,maxx(cols-1), maxy(rows-1){}
};

ScrSize square(1,1);

class Screen{
public:
	vector< vector<Texture*> > screen;
	Texture* filler;
	ScrSize* size;
	Screen(ScrSize* size,Texture* filler):size(size),filler(filler) {
		fill();
	}

	void fill(){
		screen.erase(screen.begin(),screen.end());
		vector<Texture*> fillerRow;
		for (int colI=0;colI<size->cols;colI++){
			fillerRow.push_back(filler);
		}
		for (int rowI=0;rowI<size->rows;rowI++){
			screen.push_back(fillerRow);
		};
	}
};

class Terminal{
public:
	Screen screen;

	Terminal(Texture* fillTexture):screen(&square,fillTexture){
		raw(true);
		updatesize();
		screen.fill();
		pushup();
		project();
		cout << Esc::inviscurs;
	}

	~Terminal(){ //remove footpint
		updatesize();
		cout << Esc::homecurs;
		string spacerow="";
		for (int col=0;col<screen.size->cols;col++){ //generate row of spaces
			spacerow+=" ";
		}
		for (int row=0;row<screen.size->rows;row++){ // clear terminal
			cout << spacerow;
			if (!(row==screen.size->rows-1)){
				cout << Esc::crnl;
			}
		}
		cout << Esc::homecurs;
		raw(false);
		cout << Esc::viscurs;
	}

	void updatesize(){
		gettermsize(&screen.size->cols,&screen.size->rows);
	}

	void pushup(){
		for (int row=1;row<screen.size->rows;row++){ // "\n" rows-1 times
			cout << '\n';
		}
		cout << Esc::homecurs;
	}

	void project(){
		int colI=0;
		cout << Esc::homecurs;
		for (int rowI=0;rowI<screen.size->rows;rowI++){
			for (;colI<screen.size->cols;colI++){
				cout << screen.screen[rowI][colI]->getesc();
			}
			colI=0;
		};
	}
};

#endif