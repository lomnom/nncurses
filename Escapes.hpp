#ifndef Escapes
#define Escapes

#include <string>

#define string std::string
#define to_string std::to_string

namespace nc{
	namespace esc{
		string bell="\a";
		string bksp="\b"; //backspace
		string ff="\f"; //formfeed
		string del="\e[0x7F"; //delete key???

		string vtab="\v"; //vertical tab
		string tab="\t"; //tab

		string nl="\n"; //newline
		string cr="\r"; //carraige return

		string nlcr="\n\r";
		string crnl=nlcr;

		string esc="\e"; //escape

		string savescr="\e[?47h"; //save current state of screen
		string loadscr="\e[?47l"; //load state of screen

		string savecurs="\e[s"; //save current cursor position without attrs
		string loadcurs="\e[u"; //load from save without attrs, cant load from savecursattr

		string savecursattr="\e7";
		string loadcursattr="\e8";

		string inviscurs="\e[?25l"; //make cursor invisible
		string viscurs="\e[?25h"; //make cursor visible

		// \e[row+1;col+1H
		string homecurs="\e[H"; //move cursor to home (0,0)
		string movcurs(int row,int col){
			return "\e["+to_string(row+1)+";"+to_string(col+1)+"H"; //yes, coords in a terminal start from (1,1), which is comfusing, so i masked it
		};
		string upcurs(int n){
			return "\e["+to_string(n)+"A";
		};
		string downcurs(int n){
			return "\e["+to_string(n)+"B";
		};
		string rightcurs(int n){
			return "\e["+to_string(n)+"C";
		};
		string leftcurs(int n){
			return "\e["+to_string(n)+"D";
		};
		string upstrtcurs(int n){ //move up n lines and go to the start of it
			return "\e["+to_string(n)+"F";
		};
		string downstrtcurs(int n){ //move down n lines and go to the start of it
			return "\e["+to_string(n)+"E";
		};
		string colcurs(int n){
			return "\e["+to_string(n-1)+"G";
		}

		string clrscr="\e[H\e[J"; //yes, i know its \e[J, but it doesnt work for some reason, probably bc curs needs to be home first. it also clears scrollback on iterm2
		string clrscroll="\e[3J"; //clear scrollback
		string clrlnhm="\e[0G\e[K"; //clear currnet line and go to column 0
		string clrln="\e[2K"; //clr ln and not go to column 0
		string clrtoeos="\e[0J"; //clear from cursor to end of screen
		string clrtosos="\e[1J"; //clear from cursor to start of screen
		string clrtoeol="\e[0K"; //clear from cursor to end of line
		string clrtosol="\e[1K"; //clear from cursor to start of line

		string bld="\e[1m"; //bold
		string dim="\e[2m"; //dim text
		string ital="\e[3m"; //italic
		string uline="\e[4m"; //underline
		string blnk="\e[5m"; //blink
		string inv="\e[7m"; //invert
		string hid="\e[8m"; //hide
		string strk="\e[9m"; //strikethrough

		string rst="\e[0m"; //reset style
		string rstfg="\e[39m";
		string rstbg="\e[49m";

		string unblddim="\e[22m"; //unbold and undim
		string undimbld=unblddim; //alias
		string unital="\e[23m";
		string unuline="\e[24m";
		string unblnk="\e[25m";
		string uninv="\e[27m";
		string unhid="\e[28m";
		string unstrk="\e[29m";

		string rstfnt=undimbld+unuline+unblnk+uninv+unhid+unstrk+unital;

		string fgblck="\e[30m"; //foreground black
		string fgred="\e[31m"; //foreground red
		string fggrn="\e[32m"; //foreground green
		string fgylw="\e[33m"; //foreground yellow
		string fgblu="\e[34m"; //foreground blue
		string fgmgn="\e[35m"; //foreground magenta
		string fgcyn="\e[36m"; //foreground cyan
		string fgwhit="\e[37m"; //foreground white

		string bgblck="\e[40m"; //background black
		string bgred="\e[41m"; //background red
		string bggrn="\e[42m"; //background green
		string bgylw="\e[43m"; //background yellow
		string bgblu="\e[44m"; //background blue
		string bgmgn="\e[45m"; //background magenta
		string bgcyn="\e[46m"; //background cyan
		string bgwhit="\e[47m"; //background white

		// https://upload.wikimedia.org/wikipedia/commons/1/15/Xterm_256color_chart.svg
		string fgidcol(uint8_t id){
			return "\e[38;5;"+to_string(id)+"m";
		};
		string bgidcol(uint8_t id){
			return "\e[48;5;"+to_string(id)+"m";
		};

		string wintitle(string title){
			return "\033]0;"+title+"\a";
		};

		string bluarrow="\e]7;m\a";
		string notif(string message){
			return "\e]9;"+message+"\a";
		}

		string freeze="\ec"; //???
		string nothing=""; //ah yes
	}
	namespace Esc=esc;
}

#undef string
#undef to_string

#endif