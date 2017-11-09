//This is the first comment                                                     
#include <iostream>                                                                                                        
uint_t32  pc;

char decode_instruction(uint_t32 instr)
{
	uint_t32 opcode=instr&0xFC000000;
	if(opcode==0x0){
	  return 'R';
	}
	if(opcode==0x08000000||opcode==0x0C000000){
		return 'J';
  }
	return 'I';
}

void execute_J_type(uint_t32 instr)
{
	uint_t32 offset=instr&0x3FFFFFF;
	offset=offset<<2;
	if(offset&0x8000000){
		offset+=0xF0000000;
	}
	pc=(pc&0xF0000000)+offset;
}
                                                                               
int main(){            
uint_t32 MEM[344];                                                                                                                
unit_t32 reg[32];
while(pc!=0)
{
	if(decode_instruction(MEM[pc])=='J'){                                            	                                               
    execute_J_type(MEM[pc]);                                                       
	}
	if(decode_instruction(MEM[pc])=='R'){
		execute_R_type(MEM[pc]);			
	}
	if(decode_instruction(MEM[pc])=='I'){
		execute_I_type(MEM[pc]);
	}
}                                                                               
 std::cout << "HELLO ANDREI" << std::endl;                                      
 std::cout << "HELLO WIM!" << std::endl;                                        
 return 10;                                                                     
}            
