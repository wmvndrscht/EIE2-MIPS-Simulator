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
		
		if(instr_field[5]==0b100000)
			return "ADD";
		if(instr_field[5]==0b100001)
			return "ADDU";
		if(instr_field[5]==0b100100)
			return "AND";
		if(instr_field[5]==0b011010)
			return "DIV";
		if(instr_field[5]==0b011011)
			return "DIVU";
		if(instr_field[5]==0b001000)
			return "JR";
		if(instr_field[5]==0b010000)
			return "MFHI";
		if(instr_field[5]==0b010010)
			return "MFLO";
		if(instr_field[5]==011000)
			return "MULT";
		if(instr_field[5]==0b011001)
			return "MULTU";
		if(instr_field[5]==0b100101)
			return "OR";
		if(instr_field[5]==0b000000)			// it might be a NOOP
			return "SLL"; 
		if(instr_field[5]==0b000100)
			return "SLLV";
		if(instr_field[5]==0b101010)
			return "SLT";
		if(instr_field[5]==0b101011)
			return "SLTU";
		if(instr_field[5]==0b000011)
			return "SRA";
		if(instr_field[5]==0b000010)
			return "SRL";
		if(instr_field[5]==0b000110)
			return "SRLV";
		if(instr_field[5]==0b100010)
			return "SUB";
		if(instr_field[5]==0b100011)
			return "SUBU";
		if(instr_field[5]==0b001100)
			return "SYSCALL";							// WTF is this?
		if(instr_field[5]==0b100110)
			return "XOR";
	}
	
	if(type=='I')
	{
		instr_field[1]=(instruction << 6)>>27;  // first source register
		instr_field[2]=(instruction << 11)>>27; // second source register
		instr_field[3]=(instruction << 16)>>16; // immediate
		
		if(instr_field[0]==0b001110)
			return "XORI";
		if(instr_field[0]==0b101011)
			return "SW";
		if(instr_field[0]==0b001011)
			return "SLTIU";
		if(instr_field[0]==0b001010)
			return "SLTI";
		if(instr_field[0]==0b101000)
			return "SB";
		if(instr_field[0]==0b001101)
			return "ORI";
		if(instr_field[0]==0b100011)
			return "LW";	
		if(instr_field[0]==0b001111)
			return "LUI";
		if(instr_field[0]==0b100000)
			return "LB";
		if(instr_field[0]==0b000101)
			return "BNE";
		if((instr_field[0]==0b000001)&&(instr_field[2]==0b10000))
			return "BLTZAL";
		if((instr_field[0]==0b000001)&&(instr_field[2]==0b0))
			return "BLTZ"; 
		if(instr_field[0]==0b000111)
			return "BGTZ";
		if(instr_field[0]==0b000110)
			return "BLEZ";
		if((instr_field[0]==0b000001)&&(instr_field[2]==0b10001))
			return "BGEZAL";
		if((instr_field[0]==0b000001)&&(instr_field[2]==0b00001))
			return "BGEZ";
		if(instr_field[0]==0b000100)
			return "BEQ";
		if(instr_field[0]==0b001100)
			return "ANDI";
		if(instr_field[0]==0b001001)
			return "ADDIU";
		if(instr_field[0]==0b001000)
			return "ADDI";
		
		return "Invalid instruction";	
}
	
	if(type=='J')
	{
		instr_field[1]=(instruction<<6); // extract address
		
		if(instr_field[0]==0b000010)
			return "J";
		if(instr_field[0]==0b000011)
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
execute_AND()
{
	REG[instr_field[3]]=REG[instr_field[2]]&REG[instr_field[1]];
	PC+=4;
}
execute_ANDI()
{
	REG[instr_field[2]]=REG[instr_field[1]]&instr_field[3];
	PC+=4;
}
execute_BEQ() //fuck branches
{
	if(REG[instr_field[1]]==REG[instr_field[2]])
		PC=instr_field[3]<<2;
	else{
		PC+=4;	
	}
}
execute_BGEZ()
{
	if(REG[instr_field[1]]==instr_field[3])
		
}


int main()
{            
 while(PC!=0){
	string tp=decode_instruction(MEM[PC]);
 if(tp=="J")                                          	                                           
 	  execute_J();                                                       
 if(tp=="ADD")
		execute_ADD();
if(tp=="ADDI")
	execute_ADDI();
if(tp=="ADDU")
	execute_ADDU();
if(tp=="ADDIU")
	execute_ADDIU();
	

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

  

