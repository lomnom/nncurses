#ifndef Asciichrs
#define Asciichrs

#include <map>
#include <string>
using namespace std;

namespace AscBlok{
	uint8_t tpL  	=0b1000;
	uint8_t tpR  	=0b0100;
	uint8_t btmL 	=0b0010;
	uint8_t btmR 	=0b0001;
	map<uint8_t,string> block={
		{0b0010,"▖",},
		{0b0001,"▗",},
		{0b1000,"▘",},
		{0b0100,"▝",},
		{0b1011,"▙",},
		{0b1001,"▚",},
		{0b1110,"▛",},
		{0b1101,"▜",},
		{0b0110,"▞",},
		{0b0111,"▟",},
		{0b1100,"▀",},
		{0b0011,"▄",},
		{0b1010,"▌",},
		{0b0101,"▐",},
		{0b1111,"█",},
		{0b0000," "}
	};

	map<uint8_t,string> shades={
		{0," "},
		{1,"░"},
		{2,"▒"},
		{3,"▓"}
	};

	map<uint8_t,string> horizBar={
		{8,"█"},
		{7,"▉"},
		{6,"▊"},
		{5,"▋"},
		{4,"▌"},
		{3,"▍"},
		{2,"▎"},
		{1,"▏"},
		{0," "}
	};

	map<uint8_t,string> vertBar={
		{0," "},
		{1,"▁"},
		{2,"▂"},
		{3,"▃"},
		{4,"▄"},
		{5,"▅"},
		{6,"▆"},
		{7,"▇"},
		{8,"█"}
	};
}

namespace AscBox{
	// SKREEEE
	// why are there soo manyyyy
	// ─━│┃┄┅┆┇┈┉┊┋┌┍┎┏┐┑┒┓└┕┖┗┘┙┚┛├┝┞┟┠┡┢┣┤┥┦┧┨┩┪┫┬┭┮┯┰┱┲┳┴┵┶┷┸┹┺┻┼┽┾┿╀╁╂╃╄╅╆╇╈╉╊╋╌╍╎╏═║╒╓╔╕╖╗╘╙╚╛╜╝╞╟╠╡╢╣╤╥╦╧╨╩╪╫╬╭╮╯╰╱╲╳╴╵╶╷╸╹╺╻╼╽╾╿
}

#endif