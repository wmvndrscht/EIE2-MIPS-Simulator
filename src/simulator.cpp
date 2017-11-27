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


// Signed operations, careful with ADDR_DATA, jumps, tests
// GETC, PUTC ???
// how do we deal with $0?
//1 - INITIALISE MEMORY
//2 - LOAD IN BINARY
//3 - SET PC COUNTER TO START

int main(int argc, char *argv[]) {

  std::cerr << "START" << std::endl;
  if( argc < 2){
    std::cerr << "No input binary  :: END PROGRAM" << std::endl;
    exit(IO_Error); //just for the moment
  }

  uint8_t* ADDR_INSTR;
  ADDR_INSTR = new uint8_t[0x1000000];
  uint8_t* ADDR_DATA;
  ADDR_DATA = new uint8_t[0x4000000];


	uint32_t REG[32] = {0};

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

    file.read( (char*) ADDR_INSTR, size);
	
    file.close();

    std::cerr << "the entire file content is in memory" << std::endl;

  }
  else{ 

  	std::cerr << "Unable to open file" << std::endl;
		exit(IO_Error);																				// IO ERROR 
  	return 0;
  }
  
//TEST FOR ctrl initialise = PASS -----------------------------------------------------------
  // control ctrl;
  // initialise_control(ctrl, offset_AI);
  // std::cerr << "ctrl.PC = " << ctrl.PC <<std::endl;
  // std::cerr << "ctrl.nPC = " << ctrl.nPC << std::endl;
  // std::cerr << "ctrl.target = " << ctrl.target << std::endl;
  // std::cerr << "ctrl.delay1 = " << ctrl.delay1 << std::endl;
  // std::cerr << "ctrl.delay2 = " << ctrl.delay2 << std::endl;

//TEST FOR instruction initialise = PASS----------------------------------------------------

  // uint32_t instruction2 = 0;
  // instruction2 = (ADDR_INSTR[0] << 24 | ADDR_INSTR[1] 
  //   << 16| ADDR_INSTR[2] << 8| ADDR_INSTR[3]);

  // std::cerr << "instruction2 = " << instruction2 << std::endl;

  // uint32_t instruction = 0;
  // instruction = assemble_instruction(ctrl, offset_AI);

//-----------------------------------------------------------------------------------------------

  control ctrl;
  initialise_control(ctrl, offset_AI);


  while( ctrl.PC != 0  ){					//if the program runs 

    uint32_t instruction = 0;
    std::string rijtype;
  	instruction = assemble_instruction(ADDR_INSTR, ctrl, offset_AI);

  	rijtype = decode_instructionRIJ(instruction);
    std::cerr << "RIJTYPE = " << rijtype << std::endl;

  	if(rijtype == "R"){
      std::cerr << "Detected I" << std::endl;
      instructionR Rtype;
  		initialiseR(instruction, Rtype);
      std::cerr << "Rtype.data = " <<Rtype.data << std::endl;
      std::cerr << "Rtype.opcode = " << Rtype.opcode << std::endl;
      std::cerr << "Rtype.rs = " << Rtype.rs << std::endl;
      std::cerr << "Rtype.rt = " << Rtype.rt << std::endl;
      std::cerr << "Rtype.rd = " << Rtype.rd << std::endl;
      std::cerr << "Rtype.shamt = " << Rtype.shamt << std::endl;
      std::cerr << "Rtype.function = " << Rtype.funct << std::endl;
      REG[Rtype.rs] = 1;
      REG[Rtype.rt] = 1;

  		execute_R_type(Rtype, REG);
  	}
  	else if(rijtype == "I"){
      std::cerr << "Detected I" << std::endl;
      instructionI Itype;
  		initialiseI(instruction, Itype);
      std::cerr << "Itype.data = " << Itype.data << std::endl;
      std::cerr << "Itype.opcode = " << Itype.opcode << std::endl;
      std::cerr << "Itype.rs = " << Itype.rs << std::endl;
      std::cerr << "Rtype.rd = " << Itype.rd << std::endl;
      std::cerr << "Rtype.IMM = " << Itype.IMM << std::endl;
  		// execute_I_type(Itype,REG,ctrl);
  	}
  	else{
      std::cerr << "Detected J" << std::endl;
//--------------------------currently can't assemble j and jal instructions :( need to find out more)
    //   instructionJ Jtype;
  		// initialiseJ(instruction, Jtype);
  		// execute_J_type(Jtype,ctrl);
  	}

    PC_advance(ctrl);
    std::cerr << "End of while loop hopefully" << std::endl;
  }

  delete[] ADDR_INSTR;  //deleting dynamic memory
  delete[] ADDR_DATA;
  ADDR_INSTR = NULL;
  ADDR_DATA = NULL;

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