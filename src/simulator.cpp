#include <iostream>     
#include <fstream>
#include <cstdint>

#include "decode_instruction.hpp"
#include "rijstructures.hpp"

#include <string>

//steps
//1 - INITIALISE MEMORY
//2 - LOAD IN BINARY
//3 - SET PC COUNTER TO START

int main (int argc, char* argv[]) {

	//Data storage variables ADDR_*
	uint8_t ADDR_NULL[0x4] = {0};
	uint8_t ADDR_INSTR[0x1000000] = {0};
	uint8_t ADDR_DATA[0x4000000] = {0};
	uint8_t ADDR_GETC[0x4] = {0};
	uint8_t ADDR_PUTC[0x4] = {0};
	int32_t REG[32] = {0};

	const uint32_t offset_N  = 0;
	const uint32_t offset_AI = 0x10000000;
	const uint32_t offset_AD = 0x20000000;
	const uint32_t offset_GC = 0x30000000;
	const uint32_t offset_AP = 0x30000004;

	control ctrl;
	initialise_control(ctrl, offset_AI);

	uint32_t instruction = 0;

	instructionR Rtype;
	instructionR Itype;
	instructionR Jtype;


	std::string rijtype;

	std::streampos size;
	std::string binin;
	binin = argv[1];
	std::cout << "File name: " << binin << std::endl;

	//in - allow input, binary:read direct bin, ate: put pointer to end
  std::ifstream file (binin, std::ios::in|std::ios::binary|std::ios::ate);

  if (file.is_open()){

  	size = file.tellg();
  	std::cout << "file size: " << size << std::endl; //prints size
  	// may need to include size constraint for too large binaries

    file.seekg(0, std::ios::beg);

    file.read( (char*) &ADDR_INSTR, size);
	
    file.close();

    std::cout << ADDR_INSTR[0] << ADDR_INSTR[1] << ADDR_INSTR[2] << ADDR_INSTR[3] << std::endl;
    std::cout << instruction1 << std::endl;
    std::cout << "the entire file content is in memory" << std::endl;

  }
  else{ 

  	std::cout << "Unable to open file" << std::endl;
		std::exit(-21);																				// IO ERROR 
  	return 0;
  }


  while( check_PC(ctrl) ){					//if the program runs 

  	instruction = assemble(ADDR_INSTR[0x1000000], ctrl, offset_AI);

  	type = decode_instructionRIJ(instruction);

  	if(type == 'R'){
  		initialiseR(instruction, Rtype);
  		execute_R_type(Rtype,REG[32]);
  	}
  	else if(type == 'I'){
  		initialiseI(instruction, Itype);
  		execute_I_type(Itype,REG[32]);
  	}
  	else{
  		initialiseJ(instruction, Jtype);
  		execute_J_type(Jtype,REG[32]);
  	}
  	
    ctrl.PC += 4;
 }

 uint8_t result = REG[2] & 0x000000FF;
 std::exit(result);

  return 0;
}