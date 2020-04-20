#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "opcodes.hpp"

void writeCode(std::string code, std::string filename)
{
	std::ofstream output(filename);	

	output << code;
}

int main(int argc, char** argv)
{
	std::string inpfilename = "";
	std::string outpfilename = "";

	if(argc > 1)
	{
		inpfilename = std::string(argv[1]);

		if(argc > 2)
			outpfilename = std::string(argv[2]);
		else
			outpfilename = inpfilename + ".asm";
	}
	else
	{
		std::cout << "sfotdisasm input.nes [ouput.asm]" << std::endl;
		return 0;
	}

	opcodes op;
	
	std::string hex;
	unsigned char* buffer;

	struct stat bf;

	if(stat(inpfilename.c_str(), &bf) != 0)
	{
		std::cout << "sfotdisasm: input file not found" << std::endl;
		return 1;
	}

	FILE* fptr = fopen(inpfilename.c_str(), "rb");

	fseek(fptr, 0, SEEK_END);
	unsigned long fileLen = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	buffer = (unsigned char*)malloc(fileLen+1);

	fread(buffer, fileLen, 1, fptr);
	fclose(fptr);

	std::string prog = "";

	size_t real_adr = 0xC000;

	for(size_t i(16); i < fileLen+1;)
	{
		std::stringstream ss;
		ss << std::hex << std::uppercase << (unsigned int)buffer[i];
		hex = ss.str();

		while(hex.length() < 2)
			hex = "0" + hex;

		std::stringstream adrs;
		adrs << std::hex << std::uppercase << real_adr;

		std::string sadr = adrs.str();

		while(sadr.length() < 5)
			sadr = "0" + sadr;

		prog += sadr + ": ";

		std::string kw = op.getKeyword(hex);

		i++;
		real_adr++;

		if(hex == "FF")
		{
			prog += "BRK\n";
			continue;
		}

		if(!op.isOpcode(hex))
		{
			prog += ".db $" + hex + "\n";
			i++;
			real_adr++;
			continue;
		}

		std::string operand = "";

		for(size_t j = 0; j < op.getBytesCount(hex); j++)
		{
			std::string tmp = "";
			std::stringstream ss1;
			ss1 << std::hex << std::uppercase << (unsigned int)buffer[i+j];
			tmp = ss1.str();

			while(tmp.length() < 2)
				tmp = "0" + tmp;
			operand += tmp;
		}

		if(op.getBytesCount(hex) == 2)
		{
			operand = std::string(1, operand[2])+std::string(1, operand[3])+std::string(1, operand[0])+std::string(1, operand[1]);
		}

		if(op.isRelativeOpcode(hex))
		{
			int adr = std::stoi(operand, 0, 16);
			int nadr;

			if(adr > 127)
				nadr = real_adr - (0xFF - adr);
			else
				nadr = real_adr + adr;

			std::stringstream sadr;
			sadr << std::hex << std::uppercase << nadr;
			
			operand = sadr.str();
		}

		if(op.getBytesCount(hex) != 0)
		{
			operand = "$" + operand;

			if(op.getOpcodeType(hex) == IMM)
				operand = "#" + operand;
		}

		switch(op.getOpcodeType(hex))
		{
			case ABSX:
				operand += ", X";
				break;
			case ABSY:
				operand += ", Y";
				break;
			case INDX:
				operand = "(" + operand + ", X)";
				break; 
			case INDY:
				operand = "(" + operand + "), Y";
				break;
		}

		prog += kw + " " + operand + "\n";

		i += op.getBytesCount(hex);
		real_adr += op.getBytesCount(hex);
	}

	free(buffer);

	writeCode(prog, outpfilename);
}