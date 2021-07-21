#include "Styles.hpp"
#include "Raw.hpp"
#include "EscFunc.hpp"

#ifndef Screens
#define Screens

#define cout std::cout
#define vector std::vector
#define string std::string
#define RawController nc::RawController

namespace nc{
	class Screen{
	public:
		vector< vector<Texture*> > screen={};
		vector< vector<Texture*> > filler={};
		vector<Texture*> fillerRow={};
		Texture* fillerTexture;
		int rows,cols;
		int oldRows,oldCols;

		Screen(int rows, int cols,Texture* filler):
			rows(rows)
			,cols(cols)
			,oldRows(rows-1)
			,oldCols(cols-1)
			,fillerTexture(filler)
		{
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

		void render(Screen* scr,int startX,int startY){ //ah yes
			for (int row=0;row<rows;row++){
				for (int col=0;col<cols;col++){
					scr->screen[row+startY][col+startX]=screen[row][col];
				}
			}
		}

		void renderPart(Screen* scr,int startX,int startY,int partStartX,int partStartY,int sizeX,int sizeY){ //lmao
			for (int row=0;row<sizeY;row++){
				for (int col=0;col<sizeX;col++){
					scr->screen[row+startY][col+startX]=screen[partStartY+row][partStartX+col];
				}
			}
		}
	};

	class Terminal{
	public:
		Screen screen;
		RawController raw;

		Terminal(Texture* fillTexture):screen(1,1,fillTexture){
			raw.raw();
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
			raw.unraw();
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
			string projString=Esc::rst+Esc::homecurs+screen.screen[0][0]->stylEsc+(*screen.screen[0][0]->character);
			Texture* prevText=screen.screen[0][0];

			for (int rowI=0;rowI<screen.rows;rowI++){
				for (;colI<screen.cols;colI++){
					if (screen.screen[rowI][colI]->style->effect==prevText->style->effect){
						if (screen.screen[rowI][colI]->style->color!=prevText->style->color){
							if (screen.screen[rowI][colI]->style->color->fg!=prevText->style->color->fg){
								projString+=Esc::rstfg;
								projString+=screen.screen[rowI][colI]->style->color->fgEsc;
							}
							if (screen.screen[rowI][colI]->style->color->bg!=prevText->style->color->bg){
								projString+=Esc::rstbg;
								projString+=screen.screen[rowI][colI]->style->color->bgEsc;
							}
						}
					}else{
						projString+=Esc::rst+screen.screen[rowI][colI]->stylEsc;
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
}

#undef cout
#undef vector
#undef string
#undef RawController

#endif