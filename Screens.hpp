#include "Styles.hpp"
#include "Raw.hpp"
#include "EscFunc.hpp"

#ifndef Screens
#define Screens
using namespace std;

class Screen{
public:
	vector< vector<Texture*> > screen={};
	vector< vector<Texture*> > filler={};
	vector<Texture*> fillerRow={};
	Texture* fillerTexture;
	int rows,cols;
	int oldRows,oldCols;
	int* startX;
	int* startY;

	Screen(int rows, int cols,Texture* filler,int* startX,int* startY):
		rows(rows)
		,cols(cols)
		,oldRows(rows-1)
		,oldCols(cols-1)
		,fillerTexture(filler)
		,startX(startX)
		,startY(startY) {
		fill();
	}

	void fill(){
		if (!((oldRows==rows)&&(oldCols==cols))){
			generateFill();
			oldRows=rows;
			oldCols=cols;
		}
		screen=filler;
	}

	void generateFill(){
		filler.erase(filler.begin(),filler.end());
		fillerRow.erase(fillerRow.begin(),fillerRow.end());
		for (int colI=0;colI<cols;colI++){
			fillerRow.push_back(fillerTexture);
		}
		for (int rowI=0;rowI<rows;rowI++){
			filler.push_back(fillerRow);
		};
	}

	void render(Screen* scr){ //ah yes
		for (int row=(*startY);(row<=(rows+(*startY))&&(!(row>=scr->rows)));row++){
			for (int col=(*startX);((col<=(cols+(*startX)))&&(!(col>=scr->rows)));col++){
				scr->screen[row][col]=screen[row-(*startY)][col-(*startX)];
			}
		}
	}
};

class Terminal{
public:
	int zero=0;
	Screen screen;

	Terminal(Texture* fillTexture):screen(1,1,fillTexture,&zero,&zero){
		raw(true);
		updatesize();
		screen.fill();
		pushup(); //culprit
		project();
		cout << Esc::inviscurs;
	}

	~Terminal(){ //remove footpint
		updatesize();
		cout << Esc::homecurs;
		string spacerow="";
		for (int col=0;col<screen.cols;col++){ //generate row of spaces
			spacerow+=" ";
		}
		for (int row=0;row<screen.rows;row++){ // clear terminal
			cout << spacerow;
			if (!(row==screen.rows-1)){
				cout << Esc::crnl;
			}
		}
		cout << Esc::homecurs;
		raw(false);
		cout << Esc::viscurs;
	}

	void updatesize(){
		gettermsize(&screen.cols,&screen.rows);
	}

	void pushup(){
		string pushupStr;
		for (int row=1;row<screen.rows;row++){ // "\n" rows-2 times, screen.rows is int, works as expected
			pushupStr+="\n";
		}
		pushupStr+=Esc::homecurs; 
		cout << pushupStr; 
	}

	void project(){ //currText=screen.screen[rowI][colI]
		int colI=1;
		string projString=Esc::rst+Esc::homecurs+screen.screen[0][0]->getStylEsc()+(*screen.screen[0][0]->character);
		Texture* prevText=screen.screen[0][0];

		for (int rowI=0;rowI<screen.rows;rowI++){
			for (;colI<screen.cols;colI++){
				if (screen.screen[rowI][colI]->style->effect==prevText->style->effect){
					if (screen.screen[rowI][colI]->style->color!=prevText->style->color){
						if (screen.screen[rowI][colI]->style->color->fg!=prevText->style->color->fg){
							projString+=Esc::rstfg;
							projString+=screen.screen[rowI][colI]->style->color->getFgEsc();
						}
						if (screen.screen[rowI][colI]->style->color->bg!=prevText->style->color->bg){
							projString+=Esc::rstbg;
							projString+=screen.screen[rowI][colI]->style->color->getBgEsc();
						}
					}
				}else{
					projString+=Esc::rst+screen.screen[rowI][colI]->getStylEsc();
				}

				projString+= *(screen.screen[rowI][colI]->character);
				prevText=screen.screen[rowI][colI];
			}
			colI=0;
		};
		projString+=Esc::rst;

		cout << projString;
	}
};

#endif