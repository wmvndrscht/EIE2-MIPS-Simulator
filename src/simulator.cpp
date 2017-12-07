#include <iostream>     
#include <fstream>
#include <cstdint>
#include "decode_instruction.hpp"
#include "rijstructures.hpp"
#include <string>

// const int Arithmetic_Exception = -10;
// const int Memory_Exception = -11;
// const int Invalid_Instruction_Exception = -12;
// const int Internal_Error = -20; 
// const int IO_Error = -21;


// Signed operations, careful with ADDR_DATA, jumps, tests
// GETC, PUTC ???
// how do we deal with $0?
//1 - INITIALISE MEMORY
//2 - LOAD IN BINARY
//3 - SET PC COUNTER TO START


//--------------ASK DT MONDAY----------------------------------
//1. How to disable the optimiser in compiling assembly file
//2. Testbench, saw we use jr but it doesn't work then they fail all tests

//------------------------To do--------------------------------
//1. Check all instructions, comment edge cases
//2. NOOP: r, i, or j, or undefined etc
//3. Memory offset
//4. Ensure no out of bounds
//5. Testbench interface + layout
//6. What do we do with all invalid instructions etc, e.g in SRA, rs = 0
//7. ADDIU does not trap overflow, so wrap around or not
//8. Can you have a branch then jump, or branch followed by branch

int main(int argc, char *argv[]) {

  std::cerr << "---------------BEGIN------------------" << std::endl;
  if( argc < 2){
    //std::cerr << "No input binary  ::  END PROGRAM" << std::endl;
    std::exit(-21); //IO ERROR
  }

  uint8_t* ADDR_INSTR;
  ADDR_INSTR = new uint8_t[0x1000000]();
  uint8_t* ADDR_DATA;
  ADDR_DATA = new uint8_t[0x4000000]();


  int32_t REG[32] = {};

  for(int tr=0; tr<32; tr++){
    //std::cerr << REG[tr] << " ";
  }
  //std::cerr << "\n"; 

  const uint32_t offset_N  = 0;
  const uint32_t offset_AI = 0x10000000;
  const uint32_t limit_AI =  0x11000000;
  const uint32_t offset_AD = 0x20000000;
  const uint32_t offset_GC = 0x30000000;
  const uint32_t offset_AP = 0x30000004;


  std::streampos size;
  std::string binin;
  binin = argv[1];
  //std::cerr << "File name: " << binin << std::endl;

  //in - allow input, binary:read direct bin, ate: put pointer to end
  std::ifstream file (binin, std::ios::in|std::ios::binary|std::ios::ate);

  if (file.is_open()){

    size = file.tellg();
    //std::cerr << "file size: " << size << std::endl; //prints size
    // may need to include size constraint for too large binaries

    if(size > 0x1000000){
      //std::cerr << "Input binary too large, max = 0x1000000" << std::endl;
      std::exit(-21); //IO ERROR
    }

    file.seekg(0, std::ios::beg);

    file.read( (char*) ADDR_INSTR, size);
  
    file.close();

    //std::cerr << "the entire file content is in memory" << std::endl;

  }
  else{ 
    //std::cerr << "Unable to open file" << std::endl;
    std::exit(-21); // IO ERROR 
    return 0;
  }
  
// TEST FOR ctrl initialise = PASS -----------------------------------------------------------
  //  control ctrl;
  //  initialise_control(ctrl, offset_AI);
  // std::cerr << "ctrl.PC = " << (0x)ctrl.PC <<std::endl;
  // std::cerr << "ctrl.nPC = " << ctrl.nPC << std::endl;
  // std::cerr << "ctrl.target = " << ctrl.branch_delay << std::endl;
  // int ns;
  // std::cin >>ns; 
//TEST FOR instruction initialise = PASS----------------------------------------------------

  // uint32_t instruction2 = 0;
  // instruction2 = (ADDR_INSTR[0] << 24 | ADDR_INSTR[1] 
  //   << 16| ADDR_INSTR[2] << 8| ADDR_INSTR[3]);

  // //std::cerr << "instruction2 = " << instruction2 << std::endl;

  // uint32_t instruction = 0;
  // instruction = assemble_instruction(ctrl, offset_AI);

//-----------------------------------------------------------------------------------------------

  control ctrl;
  initialise_control(ctrl, offset_AI);


  //while( ctrl.PC != 0 ){          //if the program runs 
  while (ctrl.PC != 0){
    //std::cerr << "Start of while loop" << std::endl;
    std::cerr << "PC = " << ctrl.PC << std::endl;
    uint32_t instruction = 0;
    std::string rijtype;
    instruction = assemble_instruction(ADDR_INSTR, ctrl, offset_AI);

    rijtype = decode_instructionRIJ(instruction);
    //std::cerr << "RIJTYPE = " << rijtype << std::endl;

    if(rijtype == "R"){
      //std::cerr << "Detected R" << std::endl;
      instructionR Rtype;
      initialiseR(instruction, Rtype);
      std::cerr << "Rtype.data = " <<Rtype.data << std::endl;
      std::cerr << "Rtype.opcode = " << Rtype.opcode << std::endl;
      std::cerr << "Rtype.rs = " << Rtype.rs << std::endl;
      std::cerr << "Rtype.rt = " << Rtype.rt << std::endl;
      std::cerr << "Rtype.rd = " << Rtype.rd << std::endl;
      std::cerr << "Rtype.shamt = " << Rtype.shamt << std::endl;
      std::cerr << "Rtype.function = " << Rtype.funct << std::endl;
      execute_R_type(Rtype, REG, ctrl);
    }
    else if(rijtype == "I"){
      //std::cerr << "Detected I" << std::endl;
      instructionI Itype;
      initialiseI(instruction, Itype);
      std::cerr << "Itype.data = " << Itype.data << std::endl;
      std::cerr << "Itype.opcode = " << Itype.opcode << std::endl;
      std::cerr << "Itype.rs = " << Itype.rs << std::endl;
      std::cerr << "Itype.rd = " << Itype.rd << std::endl;
      std::cerr << "Itype.IMM = " << Itype.IMM << std::endl;
      std::cerr << "Itype.IMMs = " << Itype.IMMs << std::endl;
      execute_I_type(Itype,REG,ctrl,ADDR_DATA);
    }
    else{
      //std::cerr << "Detected J" << std::endl;
      instructionJ Jtype;
      initialiseJ(instruction, Jtype);
      //std::cerr << "Jtype.data = " << Jtype.data << std::endl;
      //std::cerr << "Jtype.opcode = " << Jtype.opcode << std::endl;
      //std::cerr << "Jtype.address = " << Jtype.address << std::endl;
      execute_J_type(Jtype, REG, ctrl);
    }

    for(int tr=0; tr<32; tr++){
      std::cerr << REG[tr] << " ";
    }
    //std::cerr << "\n";
    std::cerr << "\n"; 

    if(REG[0]!=0){
      REG[0]=0;
    }



    PC_advance(ctrl);

    // ctrl.PC = 0;
    ////std::cerr << "End of while loop hopefully" << std::endl << std::endl;
  }



  delete[] ADDR_INSTR;  //deleting dynamic memory
  delete[] ADDR_DATA;
  ADDR_INSTR = NULL;
  ADDR_DATA = NULL;

  // for(int tri=0; tri<32; tri++)
    //std::cerr << REG[tri] << " ";
  //std::cerr << "\n";
  uint8_t result = REG[2] & 0x000000FF;
  //std::cerr << int(result) << std::endl;
  std::exit(result);

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