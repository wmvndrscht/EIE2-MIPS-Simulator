

#include <cstdint>
#include <string>
#include "rijstructures.hpp"



uint32_t assemble(const uint8_t ADDR_INSTR[0x1000000], const uint32_t& PC){
	uint32_t instruction = (ADDR_INSTR[PC] << 24 | ADDR_INSTR[PC+1] << 16| ADDR_INSTR[PC+2] << 8| ADDR_INSTR[PC+3]);
	return instruction;
};

std::string decode_instructionRIJ(const uint32_t& instruction)
{

	uint32_t opcode;
	opcode = instruction >> 24;

	if(opcode == 0){
		return "R";							
	}
	else if( opcode == 2  ||  opcode == 3 ){
		return "J";
	}
	else{
		return "I";
	}

}

std::string execute_R_type(const instructionR& Rtype, const uint32_t REG[32], ){

	switch(Rtype.opcode){
		case 0b100000:
			// check for overflow
			REG[instr_field[3]]=REG[instr_field[1]]+REG[instr_field[2]];
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

		return "Lalala";

}


std::string execute_I_type(const instructionI& Itype){
	
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
			if(Itype.rt == 0b10000)
				return "BLTZAL";
			if(Itype.rt == 0b0)
				return "BLTZ"; 
			if(Itype.rt == 0b10001)
				return "BGEZAL";
			if(Itype.rt == 0b00001)
				return "BGEZ";
		case 0b000111:
			return "BGTZ";
		case 0b000110:
			return "BLEZ";
		case 0b000100:
			return "BEQ";
		case 0b001100:
			return "ANDI";
		case 0b001001:
			return "ADDIU";
		case 0b001000:
			return "ADDI";
		
		return "Invalid instruction";	
	}
}


std::string execute_J_type(const instructionJ& Jtype){

	switch(Jtype.opcode){
		case 0b000010:
			return "J";
		case 0b000011:
			return "JAL";
	}

	return "Lalala";

}

//** maybe start to add these functions into the case statements above instead of individual functions each time etc
//or there may be a better way?
// execute_ADD(){ // check for overflow
// 	REG[instr_field[3]]=REG[instr_field[1]]+REG[instr_field[2]];
// 	PC+=4;
// }
// execute_ADDI(){ // check for overflow
// 	REG[instr_field[2]]=REG[instr_field[1]]+instr_field[3];
// 	PC+=4;
// }
// execute_ADDU(){
// 	REG[instr_field[3]]=REG[instr_field[1]]+REG[instr_field[2]];
// 	PC+=4;
// }
// execute_ADDIU(){
// 	REG[instr_field[2]]=REG[instr_field[1]]+instr_field[3];
// 	PC+=4;
// }
// execute_AND(){
// 	REG[instr_field[3]]=REG[instr_field[2]]&REG[instr_field[1]];
// 	PC+=4;
// }
// execute_ANDI(){
// 	REG[instr_field[2]]=REG[instr_field[1]]&instr_field[3];
// 	PC+=4;
// }
// execute_BEQ(){ //fuck branches
// 	if(REG[instr_field[1]]==REG[instr_field[2]])
// 		PC=instr_field[3]<<2;
// 	else{
// 		PC+=4;	
// 	}
// }
// execute_BGEZ(){
// 	if(REG[instr_field[1]]==instr_field[3])
		
// }
