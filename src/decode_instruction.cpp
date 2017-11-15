

#include <cstdint>
#include <string>
#include "rijstructures.hpp"


int ERROR_CODE;
uint32_t assemble(const uint8_t ADDR_INSTR[0x1000000], const uint32_t& PC){
	uint32_t instruction = (ADDR_INSTR[PC] << 24 | ADDR_INSTR[PC+1] << 16| ADDR_INSTR[PC+2] << 8| ADDR_INSTR[PC+3]);
	return instruction;
};

void overflow(const int& result, const int& val1, const int& val2)
{
	if((val1 > 0) && (val2 > 0) && (result <= 0)){
		ERROR_CODE=-10;
		std::cout << "Arithmetic exception (-10) "; // std::exit(-10)
	}
	if((val1 < 0) && (val2 < 0) && (result >= 0)){
		ERROR_CODE=-10;
		std::cout << "Arithmetic exception (-10) "; // std::exit(-10)
	}
}

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

		cout << "Invalid instruction \n";
		ERROR_CODE=-12;			
		return "Invalid instruction";			// std::exit(-12);
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


 ** maybe start to add these functions into the case statements above instead of individual functions each time etc
or there may be a better way?
void execute_ADD(const instructionR& instr, uint32_t& nextPC){
 	REG[instr.rd]=REG[instr.rs]+REG[instr.rt];
	overflow(REG[instr.rd],REG[instr.rs],REG[instr.rt])
 	nextPC+=4;
 }
 void execute_ADDI(const instructionI& instr, uint32_t& nextPC){ // check for overflow
 	REG[instr_field[2]]=REG[instr.rs]+instr.IMM;
	overflow(REG[instr.rd],REG[instr.rs],instr.IMM)
 	nextPC+=4;
 }
void execute_ADDU(const instructionR& instr, uint32_t& nextPC){
 	REG[instr.rd]=REG[instr.rs]+REG[instr.rt];
 	nextPC+=4;
 }
void execute_ADDIU(const instructionI& instr, uint32_t& nextPC){
 	REG[instr.rd]=REG[instr.rs]+instr.IMM;
 	nextPC+=4;
 }
void execute_AND(const instructionR& instr, uint32_t& nextPC){
 	REG[instr.rd]=REG[instr.rs]&REG[instr.rt];
 	nextPC+=4;
 }
void execute_ANDI(const instructionI& instr, uint32_t& nextPC){
 	REG[instr.rd]=REG[instr.rs]&instr.IMM;
 	nextPC+=4;
 }
void execute_BEQ(const instructionI& instr, uint32_t& nextPC){ 
 	if(REG[instr.rs]==REG[instr.rt])
 		nextPC=instr.IMM;
 	else{
 		nextPC+=4;	
 	}
 }
void execute_BGEZ(const instructionI& instr, uint32_t& nextPC){
 	if(REG[instr.rs]>=0)
		nextPC=instr.IMM;
	else{
		nextPC+=4;}	
 }
void execute_BGEZAL(const instructionI& instr, uint32_t& nextPC){
	if(REG[instr.rs]>=0){
		REG[31]=PC+8; // ????
		nextPC=instr.IMM;
	}
	else
	 	nextPC+=4;
}
void execute_BGTZ(const instructionI& instr, uint32_t& nextPC){
	if(REG[instr.rs]>0)
		nextPC=instr.IMM;
	else
		nextPC+=4;
}
void execute_BLEZ(const instructionI& instr, uint32_t& nextPC){
	if(REG[instr.rs]<=0)
		nextPC=instr.IMM;
	else
		nextPC+=4;
}
void execute_BLTZ(const instructionI& instr, uint32_t& nextPC){
	if(REG[instr.rs]<0)
		nextPC=instr.IMM;
	else
		nextPC+=4;
}
void execute_BLTZAL(const instructionI& instr, uint32_t& nextPC){
	if(REG[instr.rs]<0)
		nextPC=instr.IMM;
	else
		nextPC+=4;
}
void execute_BNE(const instructionI& instr, uint32_t& nextPC){
	if(REG[instr.rs]!=REG[instr.rd])
		nextPC=instr.IMM;
	else
		nextPC+=4;
}
/*void execute_DIV(const instructionR& instr, uint32_t& nextPC, uint32_t& LO, uint32_t& HI){	//signed division
	LO=instr.rs/instr.rt;	
	HO=instr.rs%instr.rt;
	nextPC+=4;
}*/
void execute_DIVU(const instructionR& instr, uint32_t& nextPC){
	LO=instr.rs/instr.rt;	
	HO=instr.rs%instr.rt;
	nextPC+=4;
} 
