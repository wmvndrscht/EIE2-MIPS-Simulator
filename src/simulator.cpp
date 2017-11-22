#include <iostream>     
#include <fstream>
#include <cstdint>
#include "decode_instruction.hpp"
#include "rijstructures.hpp"
#include <string>

const int Arithmetic_Exception = -10;
const int Memory_Exception = -11;
const int Invalid_Instruction_Exception = -12;
const int Internal_Error = -20; 
const int IO_Error = -21;

// GETC, PUTC ???
// how do we deal with $0?
//1 - INITIALISE MEMORY
//2 - LOAD IN BINARY
//3 - SET PC COUNTER TO START

int main (int argc, char* argv[]) {

	//Data storage variables ADDR_*
	uint8_t ADDR_INSTR[0x1000000] = {0};
	uint8_t ADDR_DATA[0x4000000] = {0};
	int32_t REG[32] = {0};

	const uint32_t offset_N  = 0;
	const uint32_t offset_AI = 0x10000000;
	const uint32_t offset_AD = 0x20000000;
	const uint32_t offset_GC = 0x30000000;
	const uint32_t offset_AP = 0x30000004;


	std::streampos size;
	std::string binin;
	binin = argv[1];
	std::cerr << "File name: " << binin << std::endl;

	//in - allow input, binary:read direct bin, ate: put pointer to end
  std::ifstream file (binin, std::ios::in|std::ios::binary|std::ios::ate);

  if (file.is_open()){

  	size = file.tellg();
  	std::cerr << "file size: " << size << std::endl; //prints size
  	// may need to include size constraint for too large binaries

    file.seekg(0, std::ios::beg);

    file.read( (char*) &ADDR_INSTR, size);
	
    file.close();

    //std::cerr << ADDR_INSTR[0] << ADDR_INSTR[1] << ADDR_INSTR[2] << ADDR_INSTR[3] << std::endl;
    //std::cerr << instruction1 << std::endl;
    std::cerr << "the entire file content is in memory" << std::endl;

  }
  else{ 

  	std::cerr << "Unable to open file" << std::endl;
		exit(IO_Error);																				// IO ERROR 
  	return 0;
  }

  control ctrl;
  initialise_control(ctrl, offset_AI);


  while( ctrl.PC != 0  ){					//if the program runs 

    uint32_t instruction = 0;
    std::string rijtype;
  	instruction = assemble_instruction(ADDR_INSTR, ctrl, offset_AI);

  	rijtype = decode_instructionRIJ(instruction);

  	if(rijtype == "R"){
      instructionR Rtype;
  		initialiseR(instruction, Rtype);
  		execute_R_type(Rtype,REG);
  	}
  	else if(rijtype == "I"){
      instructionI Itype;
  		initialiseI(instruction, Itype);
  		execute_I_type(Itype,REG,ctrl);
  	}
  	else{
      instructionJ Jtype;
  		initialiseJ(instruction, Jtype);
  		execute_J_type(Jtype,ctrl);
  	}
  	
    ctrl.PC += 4;
 }

 uint8_t result = REG[2] & 0x000000FF;
 exit(result);

  return 0;
}
/* list of cases, errors, exceptions to consider:
1) two branches one after the other???
2) do we insert a NOP after a branch???
3) do we get an error if we try to modify REG[0]??
4) exception when PC points to : 
- a memory address which is not in the executable memory?
- a memory address which is in the executable memory, but doesn't contain an instruction???
5) when we try to load/store from/to a memory location that is not in ADDR_DATA[]?
6) when we can't open the file? 
7) 
*/