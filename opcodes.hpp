#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

enum OPCODE_TYPE
{
	IMPLIED = 0, // 1
	INDX, // 2
	INDY, // 2
	ABS, // 2
	ABSX, // 2
	IMM, // 1
	ABSY, // 2
	ZP, // 1
	ZPX, // 1
};

const std::string ERROR_ILLEGAL_OPERAND_SIGN_OP = "eo"; 

class opcodes
{
public:
	opcodes();
	std::string getKeyword(std::string name);
	size_t getBytesCount(std::string name);

	bool isOpcode(std::string name);

	OPCODE_TYPE getOpcodeType(std::string name);

	bool isRelativeOpcode(std::string name);
private:
	void initOpcodes();
	std::map<std::string, std::pair<std::string, OPCODE_TYPE>> opcode;
	std::vector<std::string> opcode_names;
	std::vector<size_t> byte_counts = {0, 2, 2, 2, 2, 1, 2, 1, 1};

	std::vector<std::string> rel_opcodes = {"90", "B0", "F0", "30", "D0", "10", "50", "70"};

	std::string getOpcodesList();
};
// 1 2 2 2 2 1 2 2 2