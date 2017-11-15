uint8_t op, rs, rt, rd, shamt, funct;
uint16_t immediate;
uint32_t instr_field[6];

string decode_instructionRIJ(const uint32_t& instruction)
{

	uint32_t opcode;
	opcode = instruction >> 24;

	if(opcode == 0){
		return 'R';							
	}
	else if( opcode == 2  ||  opcode == 3 ){
		return 'J';
	}
	else{
		return 'I';
	}

}

void execute_R_type(const instructionR& Rtype){

	switch(Rtype.opcode){
		case 0b100000:
			return "ADD";
		case 0b100001:
			return "ADDU";
		case 0b100100:
			return "AND";
		case 0b011010:
			return "DIV";
		case 0b011011:
			return "DIVU";
		case 0b001000:
			return "JR";
		case 0b010000:
			return "MFHI";
		case 0b010010:
			return "MFLO";
		case 011000:
			return "MULT";
		case 0b011001:
			return "MULTU";
		case 0b100101:
			return "OR";		// it might be a NOOP
		case 0b000000:			// it might be a NOOP
			return "SLL"; 
		case 0b000100:
			return "SLLV";
		case 0b101010:
			return "SLT";
		case 0b101011:
			return "SLTU";
		case 0b000011:
			return "SRA";
		case 0b000010:
			return "SRL";
		case 0b000110:
			return "SRLV";
		case 0b100010:
			return "SUB";
		case 0b100011:
			return "SUBU";
		case 0b001100:
			return "SYSCALL";							// WTF is this?
		case 0b100110:
			return "XOR";
		}

}


void execute_I_type(const instructionI& Jtype){
	
	switch(Itype.opcode){
		case 0b001110:
			return "XORI";
		case 0b101011:
			return "SW";
		case 0b001011:
			return "SLTIU";
		case 0b001010:
			return "SLTI";
		case 0b101000:
			return "SB";
		case 0b001101:
			return "ORI";
		case 0b100011:
			return "LW";	
		case 0b001111:
			return "LUI";
		case 0b100000:
			return "LB";
		case 0b000101:
			return "BNE";
		case 0b000001:
			if(opcode.rt == 0b10000)
				return "BLTZAL";
			if(opcode.rt == 0b0)
				return "BLTZ"; 
			if(opcode.rt == 0b10001)
				return "BGEZAL"
			if(opcode.rt == 0b00001)
				return "BGEZ"
		case 0b000111:
			return "BGTZ";
		case 0b000110:
			return "BLEZ";
		case 0b000100: //cool
			return "BEQ";
		case 0b001100:
			return "ANDI";
		case 0b001001:
			return "ADDIU";
		case 0b001000:
			return "ADDI";
		
		return "Invalid instruction";	
}


void execute_J_type(const instructionJ& Jtype){
	switch(Jtype->opcode){
		case 0b000010:
			return "J";
		case 0b000011:
			return "JAL";
	}

}

execute_ADD(){ // check for overflow
	REG[instr_field[3]]=REG[instr_field[1]]+REG[instr_field[2]];
	PC+=4;
}
execute_ADDI(){ // check for overflow
	REG[instr_field[2]]=REG[instr_field[1]]+instr_field[3];
	PC+=4;
}
execute_ADDU(){
	REG[instr_field[3]]=REG[instr_field[1]]+REG[instr_field[2]];
	PC+=4;
}
execute_ADDIU(){
	REG[instr_field[2]]=REG[instr_field[1]]+instr_field[3];
	PC+=4;
}
execute_AND(){
	REG[instr_field[3]]=REG[instr_field[2]]&REG[instr_field[1]];
	PC+=4;
}
execute_ANDI(){
	REG[instr_field[2]]=REG[instr_field[1]]&instr_field[3];
	PC+=4;
}
execute_BEQ(){ //fuck branches
	if(REG[instr_field[1]]==REG[instr_field[2]])
		PC=instr_field[3]<<2;
	else{
		PC+=4;	
	}
}
execute_BGEZ(){
	if(REG[instr_field[1]]==instr_field[3])
		
}


// int main()
// {            
 

//  while(PC!=0){
// 	string tp = decode_instruction(MEM[PC]);
//  if(tp=="J")                                          	                                           
//  	  execute_J();                                                       
//  if(tp=="ADD")
// 		execute_ADD();
// if(tp=="ADDI")
// 	execute_ADDI();
// if(tp=="ADDU")
// 	execute_ADDU();
// if(tp=="ADDIU")
// 	execute_ADDIU();
	

//  		if(decode_instruction(MEM[PC])=='R'){
//  			execute_R_type(MEM[PC]);			
//  		}
//  		if(decode_instruction(MEM[PC])=='I'){
//  			execute_I_type(MEM[PC]);
//  		}
//  	}                                                                               
//   std::cout << "HELLO ANDREI" << std::endl;                                      
//   std::cout << "HELLO WIM!" << std::endl;                                        
// return 10; }      

  

	// if(type=='R')
	// {
	// 	instr_field[1]=(instruction << 6)>>27;  // first source register
	// 	instr_field[2]=(instruction << 11)>>27; // second source register
	// 	instr_field[3]=(instruction << 16)>>27; // destination register
	// 	instr_field[4]=(instruction << 21)>>27; // shift amount
	// 	instr_field[5]=(instruction << 26)>>26;	// function code