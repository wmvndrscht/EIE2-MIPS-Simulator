#include <iostream>     
#include <fstream>
#include <cstdint>

//Global variables
uint32_t  PC;

uint8_t ADDR_NULL[0x4];
uint8_t ADDR_INSTR[0xFFFFFFC];
uint8_t ADDR_DATA[0x4000000];
uint8_t ADDR_GETC[0x4];
uint8_t ADDR_PUTC[0x4];
                                                                                                            
uint32_t REG[32];

//Declare functions

void execute_J_type(uint32_t instr[])
{
	uint32_t offset=instr&0x3FFFFFF;
	offset=offset<<2;

	if(offset&0x8000000){
		offset+=0xF0000000;
	}
	PC=(PC&0xF0000000)+offset;
}

void execute_R_type(uint32_t instr[]){
}

void execute_I_type(uint32_t instr[]){}

int main(){            
	while(PC!=0){

	  if(decode_instruction(MEM[PC])=='J'){                                            	                                               
	    execute_J_type(MEM[PC]);                                                       
		}

		if(decode_instruction(MEM[PC])=='R'){
			execute_R_type(MEM[PC]);			
		}

		if(decode_instruction(MEM[PC])=='I'){
			execute_I_type(MEM[PC]);
		}
	}                                                                               
 std::cout << "HELLO ANDREI" << std::endl;                                      
 std::cout << "HELLO WIM!" << std::endl;                                        
 return 10;                                                                     
}      



// int main(){
// 	return 0;
// }


                                                                               
int main(){            
while(PC!=0)
{
	if(decode_instruction(MEM[PC])=='J'){                                            	                                               
    execute_J_type(MEM[PC]);                                                       
	}
	if(decode_instruction(MEM[PC])=='R'){
		execute_R_type(MEM[PC]);			
	}
	if(decode_instruction(MEM[PC])=='I'){
		execute_I_type(MEM[PC]);
	}
}                                                                               
 std::cout << "HELLO ANDREI" << std::endl;                                      
 std::cout << "HELLO WIM!" << std::endl;                                        
 return 10;                                                                     
}            
