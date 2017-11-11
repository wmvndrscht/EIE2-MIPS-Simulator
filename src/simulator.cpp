#include <iostream>     
#include <fstream>
#include <cstdint>

//Global variables
//decided to use arrays as replicate memory (hardware cannot magically grow)
//has same functionality as vectors minus dynamic sizing

uint32_t  PC; //PC counter, 32 bits

//Data storage variables ADDR_*
uint8_t ADDR_NULL[0x4] = {0};
uint8_t ADDR_INSTR[0xFFFFFFC] = {0};
uint8_t ADDR_DATA[0x4000000] = {0};
uint8_t ADDR_GETC[0x4] = {0};
uint8_t ADDR_PUTC[0x4] = {0};

//Register                                                                                                            
uint32_t REG[0x20] = {0};; //Size of 32x32

// //data is a char*
// 		//size is an int
// 	    m.size = fileIn.tellg();
// 	    m.data = new char [m.size];
// 	    fileIn.seekg (0, std::ios::beg);
// 	    fileIn.read (m.data, m.size);
// 	    fileIn.close();

// 	// reading an entire binary file
// #include <iostream>
// #include <fstream>
// using namespace std;

int main (int argc, char* argv[]) {

	std::streampos size;

	std::string binin;
	binin = argv[1];
	std::cout << binin << std::endl;

  //in:allow input, binary:read direct bin, ate: put pointer to end
  std::ifstream file (binin, std::ios::in|std::ios::binary|std::ios::ate);


  if (file.is_open()){

  	size = file.tellg(); //number of bytes (end pointer)

  	std::cout << size << std::endl; //prints size

  	// may need to include size constraint for too large binaries

    //memblock = new char [size];

    file.seekg (0, std::ios::beg);

    file.read (&ADDR_INSTR, size);

    file.close();

    // for(int i=0; i++; i<size){
    // 	std::cout << ADDR_INSTR[i] << std::endl;
    // }

    // std::cout << "the entire file content is in memory" << std::endl;

  }
  else{ 
  	std::cout << "Unable to open file" << std::endl;
  }
  return 0;
}



// int main(){

// 	std::string binin;





// 	return 0;
// }













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



// // int main(){
// // 	return 0;
// // }


                                                                               
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
