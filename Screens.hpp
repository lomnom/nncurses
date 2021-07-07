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
		pushup();
		project();
	}

	~Terminal(){ //remove footpint
		updatesize();
		cout << Esc::homecurs;
		string spacerow="";
		for (int col=0;col<cols;col++){ //generate row of space
			spacerow+=" ";
		}
		for (int row=0;row<rows;row++){ // clear terminal
			cout << spacerow;
			if (!(row==rows-1)){
				cout << Esc::crnl;
			}
		}
		cout << Esc::homecurs;
	}

	void updatesize(){
		gettermsize(&cols,&rows);
	}

	void pushup(){
		for (int row=1;row<rows;row++){ // "\n" rows-1 times
			cout << '\n';
		}
		cout << Esc::homecurs;
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

	void projfill(){
		project();
		fill();
	}
};

#endif