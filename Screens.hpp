#include "Styles.hpp"
#include "Raw.hpp"
#include "EscFunc.hpp"

#ifndef Screens
#define Screens

class Terminal{
public:
	vector< vector<Texture*> > screen;
	int rows,cols;
	Texture* filler;

	Terminal(Texture* fillTexture):filler(fillTexture){
		raw(true);
		updatesize();
		fill();
	}

	void updatesize(){
		gettermsize(&cols,&rows);
	}

	void fill(){
		screen.erase(screen.begin(),screen.end());
		vector<Texture*> fillerRow;
		for (int colI=0;colI<cols;colI++){
			fillerRow.push_back(filler);
		}
		for (int rowI=0;rowI<rows;rowI++){
			screen.push_back(fillerRow);
		};
	}

	void project(){
		int colI=0;
		cout << Esc::homecurs;
		for (int rowI=0;rowI<rows;rowI++){
			for (;colI<cols;colI++){
				cout << screen[rowI][colI]->getesc();
			}
			colI=0;
		};
	}
};

#endif