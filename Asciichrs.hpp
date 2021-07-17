#ifndef Asciichrs
#define Asciichrs

#include <map>
#include <string>
#include <vector>
using namespace std;

namespace AscBlok{
	uint8_t tpL  	=0b1000;
	uint8_t tpR  	=0b0100;
	uint8_t btmL 	=0b0010;
	uint8_t btmR 	=0b0001;
	map<uint8_t,string> block={ //they dont have to be in a map but more readable
		{0b0010,"▖",},
		{0b0001,"▗",},
		{0b1000,"▘",},
		{0b0100,"▝",},
		{0b1011,"▙",},
		{0b1001,"▚",},
		{0b0110,"▞",},
		{0b1110,"▛",},
		{0b1101,"▜",},
		{0b0111,"▟",},
		{0b1100,"▀",},
		{0b0011,"▄",},
		{0b1010,"▌",},
		{0b0101,"▐",},
		{0b1111,"█",},
		{0b0000," "}
	};

	vector<string> shades={" ","░","▒","▓","█"};

	vector<string> horizBar={" ""▏","▎","▍","▌","▋","▊","▉","█"};

	vector<string> vertBar={" ","▁","▂","▃","▄","▅","▆","▇","█"};
}

namespace AscBox{
	// SKREEEE
	// why are there soo manyyyy

	//0b XX XX XX XX
	//            ^right line
	//         ^left line
	//      ^bottom line
	//   ^top line

	// 00 - nothing
	// 01 - thin line
	// 10 - double line
	// 11 - thick line

	//follows convention of top, bottom, left, right
	vector<uint8_t> thnLn={
		0b01000000, 
		0b00010000,
		0b00000100,
		0b00000001
	};
	vector<uint8_t> dblLn={
		0b10000000, 
		0b00100000,
		0b00001000,
		0b00000010
	};
	vector<uint8_t> thkLn={
		0b11000000, 
		0b00110000,
		0b00001100,
		0b00000011
	};
	
	//used this, who would suffer through categorising? https://gist.github.com/lomnom/96af7e2da44fbc02ac66285b5c9f55c4
	map<uint8_t,string> lines={
		{0b11010011,"┡"},
		{0b01110011,"┢"},
		{0b11110011,"┣"},
		{0b01010100,"┤"},
		{0b01011100,"┥"},
		{0b11010100,"┦"},
		{0b01110100,"┧"},
		{0b11110100,"┨"},
		{0b11011100,"┩"},
		{0b01111100,"┪"},
		{0b11111100,"┫"},
		{0b00010101,"┬"},
		{0b00011101,"┭"},
		{0b00010111,"┮"},
		{0b00011111,"┯"},
		{0b00110101,"┰"},
		{0b00111101,"┱"},
		{0b00110111,"┲"},
		{0b00111111,"┳"},
		{0b01000101,"┴"},
		{0b01001101,"┵"},
		{0b01000111,"┶"},
		{0b01001111,"┷"},
		{0b11000101,"┸"},
		{0b11001101,"┹"},
		{0b11000111,"┺"},
		{0b11001111,"┻"},
		{0b01010101,"┼"},
		{0b01011101,"┽"},
		{0b01010111,"┾"},
		{0b01011111,"┿"},
		{0b00000101,"─"},
		{0b00001111,"━"},
		{0b01010000,"│"},
		{0b11110000,"┃"},
		{0b00010001,"┌"},
		{0b00010011,"┍"},
		{0b00110001,"┎"},
		{0b00110011,"┏"},
		{0b00010100,"┐"},
		{0b00011100,"┑"},
		{0b00110100,"┒"},
		{0b00111100,"┓"},
		{0b01000001,"└"},
		{0b01000011,"┕"},
		{0b11000001,"┖"},
		{0b11000011,"┗"},
		{0b01000100,"┘"},
		{0b01001100,"┙"},
		{0b11000100,"┚"},
		{0b11001100,"┛"},
		{0b01010001,"├"},
		{0b01010011,"┝"},
		{0b11010001,"┞"},
		{0b01110001,"┟"},
		{0b11110001,"┠"},
		{0b10101000,"╣"},
		{0b00011010,"╤"},
		{0b00100101,"╥"},
		{0b00101010,"╦"},
		{0b01001010,"╧"},
		{0b10000101,"╨"},
		{0b10001010,"╩"},
		{0b01011010,"╪"},
		{0b10100101,"╫"},
		{0b10100000,"╬"},
		{0b00000100,"╴"},
		{0b01000000,"╵"},
		{0b00000001,"╶"},
		{0b00010000,"╷"},
		{0b00001100,"╸"},
		{0b11000000,"╹"},
		{0b00000011,"╺"},
		{0b00110000,"╻"},
		{0b00000111,"╼"},
		{0b01110000,"╽"},
		{0b00001101,"╾"},
		{0b11010000,"╿"},
		{0b11010101,"╀"},
		{0b01110101,"╁"},
		{0b11110101,"╂"},
		{0b11011101,"╃"},
		{0b11010111,"╄"},
		{0b01111101,"╅"},
		{0b01110111,"╆"},
		{0b11011111,"╇"},
		{0b01111111,"╈"},
		{0b11111101,"╉"},
		{0b11110111,"╊"},
		{0b11110101,"╋"},
		{0b00001010,"═"},
		{0b01010000,"║"},
		{0b00010010,"╒"},
		{0b00100001,"╓"},
		{0b00100010,"╔"},
		{0b00011000,"╕"},
		{0b00100100,"╖"},
		{0b00101000,"╗"},
		{0b01000010,"╘"},
		{0b10000001,"╙"},
		{0b10000010,"╚"},
		{0b01001000,"╛"},
		{0b10000100,"╜"},
		{0b10001000,"╝"},
		{0b01010010,"╞"},
		{0b10100001,"╟"},
		{0b10100010,"╠"},
		{0b01011000,"╡"},
		{0b10100100,"╢"}
	};
}

#endif