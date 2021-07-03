#ifndef Escapes
#define Escapes

#include <iostream>
#define sick static inline //ehehhehehe

using namespace std;

class Esc{
public:
	sick string bell="\a";
	sick string bksp="\b"; //backspace
	sick string ff="\f"; //formfeed
	sick string del="\e[0x7F"; //delete key???

	sick string vtab="\v"; //vertical tab
	sick string tab="\t"; //tab

	sick string nl="\n"; //newline
	sick string cr="\r"; //carraige return

	sick string esc="\e"; //escape

	sick string savescr="\e[?47h"; //save current state of screen
	sick string loadscr="\e[?47l"; //load state of screen

	sick string savecurs="\e[s"; //save current cursor position
	sick string loadcurs="\e[u"; //load from save

	sick string inviscurs="\e[?25l"; //make cursor invisible
	sick string viscurs="\e[?25h"; //make cursor visible

	sick string homecurs="\e[H"; //move cursor to home (0,0)
	sick string movcurs(int row,int col){
		return "\e["+to_string(row+1)+";"+to_string(col+1)+"H"; //yes, coords in a terminal start from (1,1), which is comfusing, so i masked it
	};
	sick string upcurs(int n){
		return "\e["+to_string(n)+"A";
	};
	sick string downcurs(int n){
		return "\e["+to_string(n)+"B";
	};
	sick string rightcurs(int n){
		return "\e["+to_string(n)+"C";
	};
	sick string leftcurs(int n){
		return "\e["+to_string(n)+"D";
	};
	sick string upstrtcurs(int n){ //move up n lines and go to the start of it
		return "\e["+to_string(n)+"F";
	};
	sick string downstrtcurs(int n){ //move down n lines and go to the start of it
		return "\e["+to_string(n)+"E";
	};
	sick string colcurs(int n){
		return "\e["+to_string(n-1)+"G";
	}

	sick string clrscrscroll="\e[H\e[J"; //yes, i know its \e[J, but it doesnt work for some reason, probably bc curs needs to be home first
	sick string clrscrollstr=clrscrscroll; //alias
	sick string pushup="\e[H\e[2J"; //puch all previous output into top of terminal
	sick string clrscroll="\e[3J"; //clear scrollback
	sick string clrln="\e[0G\e[K"; //clear currnet line, not replacing with spaces
	sick string clrlnsp="\e[2K"; //this one replaces with spaces, and keeps cursor pos
	sick string clrtoeos="\e[0J"; //clear from cursor to end of screen
	sick string clrtosos="\e[1J"; //clear from cursor to start of screen
	sick string clrtoeol="\e[0K"; //clear from cursor to end of line
	sick string clrtosol="\e[1K"; //clear from cursor to start of line

	sick string bld="\e[1m"; //bold
	sick string dim="\e[2m"; //dim text
	sick string ital="\e[3m"; //italic
	sick string uline="\e[4m"; //underline
	sick string blnk="\e[5m"; //blink
	sick string inv="\e[7m"; //invert
	sick string hid="\e[8m"; //hide
	sick string strk="\e[9m"; //strikethrough

	sick string rst="\e[0m"; //reset style
	sick string unblddim="\e[22m"; //unbold and undim
	sick string undimbld=unblddim; //alias
	sick string unuline="\e[24m";
	sick string unblnk="\e[25m";
	sick string uninv="\e[27m";
	sick string unhid="\e[28m";
	sick string unstrk="\e[29m";

	sick string fgblck="\e[30m"; //foreground black
	sick string fgred="\e[31m"; //foreground red
	sick string fggrn="\e[32m"; //foreground green
	sick string fgylw="\e[33m"; //foreground yellow
	sick string fgblu="\e[34m"; //foreground blue
	sick string fgmgn="\e[35m"; //foreground magenta
	sick string fgcyn="\e[36m"; //foreground cyan
	sick string fgwhit="\e[37m"; //foreground white

	sick string bgblck="\e[40m"; //background black
	sick string bgred="\e[41m"; //background red
	sick string bggrn="\e[42m"; //background green
	sick string bgylw="\e[43m"; //background yellow
	sick string bgblu="\e[44m"; //background blue
	sick string bgmgn="\e[45m"; //background magenta
	sick string bgcyn="\e[46m"; //background cyan
	sick string bgwhit="\e[47m"; //background white

	// https://upload.wikimedia.org/wikipedia/commons/1/15/Xterm_256color_chart.svg
	sick string fgidcol(short id){
		return "\e[38;5;"+to_string(id)+"m";
	};
	sick string bgidcol(short id){
		return "\e[48;5;"+to_string(id)+"m";
	};
};

#endif