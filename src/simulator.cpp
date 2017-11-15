#include <iostream>     
#include <fstream>
#include <cstdint>

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
	uint32_t REG[32] = {0};

	const uint32_t offset_NULL=0;
	const uint32_t offset_ADDR_INSTR=0x10000000;
	const uint32_t offset_ADDR_DATA=0x20000000;
	const uint32_t offset_ADDR_GETC=0x30000000;
	const uint32_t offset_ADDR_PUTC=0x30000004;

	uint32_t  PC =0x10000000;
	uint32_t instruction = 0;

	instructionR Rtype;
	instructionR Itype;
	instructionR Jtype;


	string type;

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
  	return 0;
  }


  while(PC != 0 && PC < 0x11000001){

  	instruction = assemble(const uint32_t& PC);

  	type = decode_instructionRIJ(const uint32_t& instruction);

  	if(type == 'R'){
  		initialiseR(instructionR& Rtype);
  		execute_R_type(const instructionJ& Jtype);
  	}
  	else if(type == 'I'){
  		initialiseI(instructionI& Itype);
  		execute_I_type(const instructionJ& Jtype);
  	}
  	else{
  		initialiseJ(instructionJ& Jtype);
  		execute_J_type(const instructionJ& Jtype);
  	}

  }


  return 0;
}


uint32_t assemble(){

	instruction = 
}



/* after we read and store the info from the binary into memory
PC=offset_ADDR_INSTR  // PC pointing to the first element of 
*/


//Declare functions

// void execute_J_type(uint32_t instr[])
// {
// 	uint32_t offset=instr&0x3FFFFFF;
// 	offset=offset<<2;

// 	if(offset&0x8000000){
// 		offset+=0xF0000000;
// 	}
// 	PC=(PC&0xF0000000)+offset;
// }

// void execute_R_type(uint32_t instr[]){
// }

// void execute_I_type(uint32_t instr[]){}

// int main(){            
// 	while(PC!=0){

// 	  if(decode_instruction(MEM[PC])=='J'){                                            	                                               
// 	    execute_J_type(MEM[PC]);                                                       
// 		}

// 		if(decode_instruction(MEM[PC])=='R'){
// 			execute_R_type(MEM[PC]);			
// 		}

// 		if(decode_instruction(MEM[PC])=='I'){
// 			execute_I_type(MEM[PC]);
// 		}
// 	}                                                                               
//  std::cout << "HELLO ANDREI" << std::endl;                                      
//  std::cout << "HELLO WIM!" << std::endl;                                        
//  return 10;                                                                     
// }      


                                                                               
// int main(){            
// while(PC!=0)
// {
// 	if(decode_instruction(MEM[PC])=='J'){                                            	                                               
//     execute_J_type(MEM[PC]);                                                       
// 	}
// 	if(decode_instruction(MEM[PC])=='R'){
// 		execute_R_type(MEM[PC]);			
// 	}
// 	if(decode_instruction(MEM[PC])=='I'){
// 		execute_I_type(MEM[PC]);
// 	}
// }                                                                               
//  std::cout << "HELLO ANDREI" << std::endl;                                      
//  std::cout << "HELLO WIM!" << std::endl;                                        
//  return 10;                                                                     
// }            