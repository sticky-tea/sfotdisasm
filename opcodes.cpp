#include "opcodes.hpp"

opcodes::opcodes()
{
	initOpcodes();
}

void opcodes::initOpcodes()
{
	std::stringstream f(getOpcodesList());

	std::string opname;
	std::string curtype;

	for(int i(0); i < 57; i++)
	{
		f >> opname;

		for(int j(0); j < 9; j++)
		{
			f >> curtype;

			if(curtype != "ne")
			{
				opcode_names.push_back(curtype);
				opcode[curtype] = {opname, (OPCODE_TYPE)j};
			}
		}
	}
}

std::string opcodes::getKeyword(std::string name)
{
	auto opc = opcode[name];

	if(opc.first == "")
		return ERROR_ILLEGAL_OPERAND_SIGN_OP;
	else
		return opc.first;
} 

bool opcodes::isOpcode(std::string name)
{
	return std::find(opcode_names.begin(), opcode_names.end(), name) != opcode_names.end();
}

bool opcodes::isRelativeOpcode(std::string name)
{
	return std::find(rel_opcodes.begin(), rel_opcodes.end(), name) != rel_opcodes.end();	
}

size_t opcodes::getBytesCount(std::string name)
{
	OPCODE_TYPE type = opcode[name].second;

	if(type == IMPLIED && isRelativeOpcode(name))
		return 1;

	return byte_counts[(size_t)type];
}

OPCODE_TYPE opcodes::getOpcodeType(std::string name)
{
	return opcode[name].second;
}

std::string opcodes::getOpcodesList()
{
	return"\
ADC 	ne	61 	71 	6D 	7D 	69 	79 	65 	75 \
AND		ne	21 	31 	2D 	3D 	29 	39 	25 	35 \
ASL  	0A 	ne	ne	ne	ne	ne	ne	06 	16 \
BCC 	90 	ne	ne	ne	ne	ne	ne	ne	ne \
BCS  	B0 	ne	ne	ne	ne	ne	ne	ne	ne \
BEQ  	F0 	ne	ne	ne	ne	ne	ne	ne	ne \
BIT 	ne	ne	ne	2C 	ne	ne	ne	24 	ne \
BMI 	30 	ne	ne	ne	ne	ne	ne	ne	ne \
BNE  	D0 	ne	ne	ne	ne	ne	ne	ne	ne \
BPL 	10 	ne	ne	ne	ne	ne	ne	ne	ne \
BVC 	50 	ne	ne	ne	ne	ne	ne	ne	ne \
BVS 	70 	ne	ne	ne	ne	ne	ne	ne	ne \
CLC 	18 	ne	ne	ne	ne	ne	ne	ne	ne \
CLD 	D8 	ne	ne	ne	ne	ne	ne	ne	ne \
CLI 	58 	ne	ne	ne	ne	ne	ne	ne	ne \
CLV 	B8 	ne	ne	ne	ne	ne	ne	ne	ne \
CMP 	ne	C1 	D1 	CD 	DD 	C9 	D9 	C5 	D5 \
CPX 	ne	ne	ne	EC 	ne	E0 	ne	E4 	ne \
CPY 	ne	ne	ne	CC 	ne	C0 	ne	C4 	ne \
\
DEC 	ne	ne	ne	CE 	DE 	ne	ne	C6 	D6 \
DEX 	CA 	ne	ne	ne	ne	ne	ne	ne	ne \
DEY 	88 	ne	ne	ne	ne	ne	ne	ne	ne \
EOR 	ne	41 	51 	4D 	5D 	49 	59 	45 	55 \
INC 	ne	ne	ne	EE 	FE 	ne	ne	E6 	F6 \
INX 	E8 	ne	ne	ne	ne	ne	ne	ne	ne \
INY 	C8 	ne	ne	ne	ne	ne	ne	ne	ne \
JMP 	6C 	ne	ne	4C 	ne	ne	ne	ne	ne \
JSR 	ne 	ne	ne	20	ne	ne	ne	ne	ne \
LDA 	ne	A1 	B1 	AD 	BD 	A9 	B9 	A5 	B5 \
LDX 	ne	ne	ne	AE 	ne	A2 	BE 	A6 	B6 \
LDY 	ne	ne	ne	AC 	BC 	A0 	ne	A4 	B4 \
LSR 	4A 	ne	ne	4E 	5E 	ne	ne	46 	ne \
NOP 	EA 	ne	ne	ne	ne	ne	ne	ne	ne \
ORA 	ne	01 	11 	0D 	1D 	09 	19 	05 	15 \
PHA 	48 	ne	ne	ne	ne	ne	ne	ne	ne \
PHP 	08 	ne	ne	ne	ne	ne	ne	ne	ne \
PLA 	68 	ne	ne	ne	ne	ne	ne	ne	ne \
PLP 	28 	ne	ne	ne	ne	ne	ne	ne	ne \
\
ROL 	2A 	ne	ne	2E 	ne	ne	ne	26 	36 \
ROR 	6A 	ne	ne	6E 	7E 	ne	ne	66 	76 \
RTI 	40 	ne	ne	ne	ne	ne	ne	ne	ne \
RTS 	60 	ne	ne	ne	ne	ne	ne	ne	ne \
SBC 	ne	E1 	F1 	ED 	FD 	E9 	F9 	E5 	F5 \
SEC 	38 	ne	ne	ne	ne	ne	ne	ne	ne \
SED 	F8 	ne	ne	ne	ne	ne	ne	ne	ne \
SEI 	78 	ne	ne	ne	ne	ne	ne	ne	ne \
STA 	ne	81 	91 	8D 	9D 	ne	99 	85 	95 \
STX 	ne	ne	ne	8E 	ne	ne	ne	86 	96 \
STY 	ne	ne	ne	8C 	ne	ne	ne	84 	94 \
TAX 	AA 	ne	ne	ne	ne	ne	ne	ne	ne \
TAY 	A8 	ne	ne	ne	ne	ne	ne	ne	ne \
TSX 	BA 	ne	ne	ne	ne	ne	ne	ne	ne \
TXA 	8A 	ne	ne	ne	ne	ne	ne	ne	ne \
TXS 	9A 	ne	ne	ne	ne	ne	ne	ne	ne \
TYA 	98 	ne	ne	ne	ne	ne	ne	ne	ne \
";
}