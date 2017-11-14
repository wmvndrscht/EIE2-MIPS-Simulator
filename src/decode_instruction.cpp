uint8_t op, rs, rt, rd, shamt, funct;
uint16_t immediate;
uint32_t instr_field[6];

string decode_instruction(int32_t instruction)
{
	char type=0;
	instr_field[0]= instruction >> 26; // Extract the offset
	
	// Determine the type of the instruction based on the offset:
	if(instr_field[0]==0){								
		type='R';
	}
	else if((instr_field[0]==2)||(instr_field[0]==3)){
		type='J';
	}
	else{
		type='I';
	}
	
	if(type=='R')
	{
		instr_field[1]=(instruction << 6)>>27;  // first source register
		instr_field[2]=(instruction << 11)>>27; // second source register
		instr_field[3]=(instruction << 16)>>27; // destination register
		instr_field[4]=(instruction << 21)>>27; // shift amount
		instr_field[5]=(instruction << 26)>>26;	// function code
		
		if(instr_field[5]==0x100000)
			return "ADD";
		if(instr_field[5]==0x100001)
			return "ADDU";
		if(instr_field[5]==0x100100)
			return "AND";
		if(instr_field[5]==0x011010)
			return "DIV";
		if(instr_field[5]==0x011011)
			return "DIVU";
		if(instr_field[5]==0x001000)
			return "JR";
		if(instr_field[5]==0x010000)
			return "MFHI";
		if(instr_field[5]==0x010010)
			return "MFLO";
		if(instr_field[5]==0x011000)
			return "MULT";
		if(instr_field[5]==0x011001)
			return "MULTU";
		if(instr_field[5]==0x100101)
			return "OR";
		if(instr_field[5]==0x000000)			// it might be a NOOP
			return "SLL"; 
		if(instr_field[5]==0x000100)
			return "SLLV";
		if(instr_field[5]==0x101010)
			return "SLT";
		if(instr_field[5]==0x101011)
			return "SLTU";
		if(instr_field[5]==0x000011)
			return "SRA";
		if(instr_field[5]==0x000010)
			return "SRL";
		if(instr_field[5]==0x000110)
			return "SRLV";
		if(instr_field[5]==0x100010)
			return "SUB";
		if(instr_field[5]==0x100011)
			return "SUBU";
		if(instr_field[5]==0x001100)
			return "SYSCALL";							// WTF is this?
		if(instr_field[5]==0x100110)
			return "XOR";
	}
	
	if(type=='I')
	{
		instr_field[1]=(instruction << 6)>>27;  // first source register
		instr_field[2]=(instruction << 11)>>27; // second source register
		instr_field[3]=(instruction << 16)>>16; // immediate
		
		if(instr_field[0]==0x001110)
			return "XORI";
		if(instr_field[0]==0x101011)
			return "SW";
		if(instr_field[0]==0x001011)
			return "SLTIU";
		if(instr_field[0]==0x001010)
			return "SLTI";
		if(instr_field[0]==0x101000)
			return "SB";
		if(instr_field[0]==0x001101)
			return "ORI";
		if(instr_field[0]==0x100011)
			return "LW";	
		if(instr_field[0]==0x001111)
			return "LUI";
		if(instr_field[0]==0x100000)
			return "LB";
		if(instr_field[0]==0x000101)
			return "BNE";
		if((instr_field[0]==0x000001)&&(instr_field[2]==0x10000))
			return "BLTZAL";
		if((instr_field[0]==0x000001)&&(instr_field[2]==0x0))
			return "BLTZ"; 
		if(instr_field[0]==0x000111)
			return "BGTZ";
		if(instr_field[0]==0x000110)
			return "BLEZ";
		if((instr_field[0]==0x000001)&&(instr_field[2]==0x10001))
			return "BGEZAL";
		if((instr_field[0]==0x000001)&&(instr_field[2]==0x00001))
			return "BGEZ";
		if(instr_field[0]==0x000100)
			return "BEQ";
		if(instr_field[0]==0x001100)
			return "ANDI";
		if(instr_field[0]==0x001001)
			return "ADDIU";
		if(instr_field[0]==0x001000)
			return "ADDI";
	}
	
	if(type=='J')
	{
		instr_field[1]=(instruction<<6); // extract address
		
		if(instr_field[0]==0x000010)
			return "J";
		if(instr_field[0]==0x000011)
			return "JAL";
	}
}

execute_ADD() // check for overflow
{
	REG[instr_field[3]]=REG[instr_field[1]]+REG[instr_field[2]];
	PC+=4;
}
execute_ADDI() // check for overflow
{
	REG[instr_field[2]]=REG[instr_field[1]]+instr_field[3];
	PC+=4;
}
execute_ADDU()
{
	REG[instr_field[3]]=REG[instr_field[1]]+REG[instr_field[2]];
	PC+=4;
}
execute_ADDIU()
{
	REG[instr_field[2]]=REG[instr_field[1]]+instr_field[3];
	PC+=4;
}


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

 	  if(decode_instruction(MEM[PC])=='J')                                          	                                               
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
return 10; }      

  

