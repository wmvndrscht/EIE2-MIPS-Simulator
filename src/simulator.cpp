#include <iostream>     
#include <fstream>
#include <cstdint>

uint32_t  PC; //PC counter, 32 bits

//Data storage variables ADDR_*
uint8_t ADDR_NULL[0x4] = {0};
int8_t ADDR_INSTR[0x1000000] = {0};
uint8_t ADDR_DATA[0x4000000] = {0};
uint8_t ADDR_GETC[0x4] = {0};
uint8_t ADDR_PUTC[0x4] = {0};

const uint32_t offset_NULL=0;
const uint32_t offset_ADDR_INSTR=0x10000000;
const uint32_t offset_ADDR_DATA=0x20000000;
const uint32_t offset_ADDR_GETC=0x30000000;
const uint32_t offset_ADDR_PUTC=0x30000004;

int main (int argc, char* argv[]) {

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

    int8_t b = 8;

    std::cout << "int8_t = " << b << std::endl;

    //Example of instruction assemble
    uint32_t instruction1 = (ADDR_INSTR[0] << 24 | ADDR_INSTR[1] << 16| ADDR_INSTR[2] << 8| ADDR_INSTR[3]);

    std::cout << ADDR_INSTR[0] << ADDR_INSTR[1] << ADDR_INSTR[2] << ADDR_INSTR[3] << std::endl;
    std::cout << instruction1 << std::endl;

    std::cout << "the entire file content is in memory" << std::endl;

  }
  else{ 
  	std::cout << "Unable to open file" << std::endl;
  }
  return 0;
}




// //Global variables
// //decided to use arrays as replicate memory (hardware cannot magically grow)
// //has same functionality as vectors minus dynamic sizing

// uint32_t  PC; //PC counter, 32 bits

// //Data storage variables ADDR_*
// uint8_t ADDR_NULL[0x4] = {0};
// uint8_t ADDR_INSTR[0x1000000] = {0};
// uint8_t ADDR_DATA[0x4000000] = {0};
// uint8_t ADDR_GETC[0x4] = {0};
// uint8_t ADDR_PUTC[0x4] = {0};

// uint32_t offset_NULL=0;
// uint32_t offset_ADDR_INSTR=0x10000000;
// uint32_t offset_ADDR_DATA=0x20000000;
// uint32_t offset_ADDR_GETC=0x30000000;
// uint32_t offset_ADDR_PUTC=0x30000004;


// //Register                                                                                                            
// uint32_t REG[0x20] = {0};; //Size of 32x32


// int main (int argc, char* argv[]) {

// 	std::streampos size;
// 	char * memblock;

// 	std::string binin;
// 	binin = argv[1];
// 	std::cout << binin << std::endl;

//   //in - allow input, binary:read direct bin, ate: put pointer to end
//   std::ifstream file (binin, std::ios::in|std::ios::binary|std::ios::ate);


//   if (file.is_open()){

//     //for(int i=0; i < 16; i++){
//     	// ADDR_INSTR[i] = uint8_t(memblock[i]) ;
//     	// std::cout << i<< " == " << memblock[i] << std::endl;
//     	//std::cout << i<< " = " << ADDR_INSTR[i] << std::endl;
//     //}

//   	size = file.tellg(); //number of bytes (end pointer)

//   	std::cout << "file size: " << size << std::endl; //prints size

//   	// may need to include size constraint for too large binaries

//     memblock = new char [size];

//     file.seekg(0, std::ios::beg);

//     file.read(memblock, size);

//     // file.read( (char*) &ADDR_INSTR, size);
//     // fin.read((char*) &A[0], 4);
	
//     file.close();

//     for(int i=0; i < size; i++){
//     	ADDR_INSTR[i] = (uint8_t) memblock[i] ;
//     	// std::cout << i<< " == " << memblock[i] << std::endl;
//     	//std::cout << i<< " = " << ADDR_INSTR[i]+0 << std::endl;
// 	if(sizeof(ADDR_INSTR[i])!=sizeof(uint8_t))
// 		std::cout << "Bad\n"; 
// 	}
// 	std::cout << "size of uint8_t: " <<  sizeof(uint8_t) << "\n";

// 		// for(int i=0; i < (int) size; i++){
// 		// 	// memblock[i] = ADDR_INSTR[i];
// 		// 	// std::cout << i << std::endl;
// 		// 	std::cout << (uint8_t) ADDR_INSTR[i] << std::endl;
// 		// }


//     std::cout << "the entire file content is in memory" << std::endl;

//     delete[] memblock;

//   }
//   else{ 
//   	std::cout << "Unable to open file" << std::endl;
//   }
//   return 0;
// }

/* after we read and store the info from the binary into memory
PC=offset_ADDR_INSTR  // PC pointing to the first element of 

index=PC-offset_" "_" ";

uint32_t instr = (ADDR_INSTR[index]<<24) + (ADDR_INSTR[index+1]<<16) + (ADDR_INSTR[index+2]<<8) + ADDR_INSTR[index+3];

PC=PC+4; // PC=PC+address_offset




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
