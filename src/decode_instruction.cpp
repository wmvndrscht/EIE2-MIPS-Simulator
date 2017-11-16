#include <cstdint>
#include <string>
#include <iostream>
#include "rijstructures.hpp"
#include "decode_instruction.hpp"

//current errors when compiling:

/*decode_instruction.cpp: In function ‘void execute_DIVU(const instructionR&, uint32_t*)’:
decode_instruction.cpp:214:2: error: ‘LO’ was not declared in this scope
  LO=Rtype.rs/Rtype.rt; 
  ^
decode_instruction.cpp:215:2: error: ‘HO’ was not declared in this scope
  HO=Rtype.rs%Rtype.rt;
  ^
*/


int ERROR_CODE;

uint32_t assemble(const uint8_t ADDR_INSTR[0x1000000], const control& ctrl, const uint32_t& offset_AI){
	
	uint32_t offset_PC = ctrl.PC - offset_AI;

	uint32_t instruction = (ADDR_INSTR[offset_PC] << 24 | ADDR_INSTR[offset_PC+1] 
		<< 16| ADDR_INSTR[offset_PC+2] << 8| ADDR_INSTR[offset_PC+3]);

	return instruction;
}

bool check_PC(control& ctrl, const uint32_t& offset_AI){

	if( ctrl.PC == 0){
		return false;
	}
	else if( ctrl.PC <  offset_AI || ctrl.PC >  0x11000000){
		std::cout << "Memory Exception";
		std::exit(-11);
	}
	else{

		if(ctrl.delay2 == 1){		
		  ctrl.PC = ctrl.nPC;
      ctrl.nPC = 0;
      ctrl.delay2 = 0;
    }
    if(ctrl.delay1 == 1){
      ctrl.delay2 = 1;
      ctrl.delay1 = 0;
    }

    return true;
	}

}

void initialise_control(control& ctrl, const uint32_t& offset_AI){
	ctrl.PC = offset_AI;
	ctrl.nPC = offset_AI;
	ctrl.target = 0;
	ctrl.delay1 = 0;
	ctrl.delay2 = 0;
}


void overflow(const int& result, const int& val1, const int& val2){

	if((val1 > 0) && (val2 > 0) && (result <= 0)){
		ERROR_CODE=-10;
		std::cout << "Arithmetic exception (-10) "; // std::exit(-10)
	}
	if((val1 < 0) && (val2 < 0) && (result >= 0)){
		ERROR_CODE=-10;
		std::cout << "Arithmetic exception (-10) "; // std::exit(-10)
	}
}

std::string decode_instructionRIJ(const uint32_t& instruction){

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

std::string execute_R_type(const instructionR& Rtype, uint32_t REG[32] ){

	switch(Rtype.opcode){
		case 0b100000:
			execute_ADD(Rtype, REG);
		case 0b100001:
			execute_ADDU(Rtype, REG);
		case 0b100100:
			execute_AND(Rtype, REG);
		case 0b011010:
			// execute_DIV(Rtype, REG);
		case 0b011011:
			execute_DIVU(Rtype, REG);
		case 0b001000:
			// execute_JR();
		case 0b010000:
			// execute_MFHI();
		case 0b010010:
			// execute_MFLO();
		case 011000:
			// execute_MULT();
		case 0b011001:
			// execute_MULTU();
		case 0b100101:
			// execute_OR();		// it might be a NOOP
		case 0b000000:			// it might be a NOOP
			// execute_SLL(); 
		case 0b000100:
			// execute_SLLV();
		case 0b101010:
			// execute_SLT();
		case 0b101011:
			// execute_SLTU();
		case 0b000011:
			// execute_SRA();
		case 0b000010:
			// execute_SRL();
		case 0b000110:
			// execute_SRLV();
		case 0b100010:
			// execute_SUB();
		case 0b100011:
			// execute_SUBU();
		case 0b001100:
			// execute_SYSCALL();							// WTF is this?
		case 0b100110:
			// execute_XOR();
		std::exit(-12);	
	}
}


std::string execute_I_type(const instructionI& Itype, uint32_t REG[32], control& ctrl){
	
	switch(Itype.opcode){
		case 0b001110:
			// execute_XORI();
		case 0b101011:
			// execute_SW();
		case 0b001011:
			// execute_SLTIU();
		case 0b001010:
			// execute_SLTI();
		case 0b101000:
			// execute_SB();
		case 0b001101:
			// execute_ORI();
		case 0b100011:
			// execute_LW();	
		case 0b001111:
			// execute_LUI();
		case 0b100000:
			// execute_LB();
		case 0b000101:
			execute_BNE(Itype, REG, ctrl);
		case 0b000001:
			if(Itype.rd == 0b10000)
				execute_BLTZAL(Itype, REG, ctrl);
			if(Itype.rd == 0b0)
				execute_BLTZ(Itype, REG, ctrl); 
			if(Itype.rd == 0b10001)
				execute_BGEZAL(Itype, REG, ctrl);
			if(Itype.rd == 0b00001)
				execute_BGEZ(Itype, REG, ctrl);
		case 0b000111:
			execute_BGTZ(Itype, REG, ctrl);
		case 0b000110:
			execute_BLEZ(Itype, REG, ctrl);
		case 0b000100:
			execute_BEQ(Itype, REG, ctrl);
		case 0b001100:
			execute_ANDI(Itype, REG, ctrl);
		case 0b001001:
			execute_ADDIU(Itype, REG, ctrl);
		case 0b001000:
			execute_ADDI(Itype, REG, ctrl);

		std::cout << "Invalid instruction \n";			
		std::exit(-12);			
	}
}


std::string execute_J_type(const instructionJ& Jtype, control& ctrl){
	switch(Jtype.opcode){
		case 0b000010:
			// execute_J();
		case 0b000011:
			// execute_JAL(Jtype, REG);
		std::exit(-12);
	}
}


//Rtype
void execute_ADD(const instructionR& Rtype, uint32_t REG[32]){
 	REG[Rtype.rd]=REG[Rtype.rs]+REG[Rtype.rt];
	overflow(REG[Rtype.rd],REG[Rtype.rs],REG[Rtype.rt]);
}


void execute_ADDU(const instructionR& Rtype, uint32_t REG[32]){
 	REG[Rtype.rd]=REG[Rtype.rs]+REG[Rtype.rt];
}

void execute_AND(const instructionR& Rtype, uint32_t REG[32]){
 	REG[Rtype.rd]=REG[Rtype.rs]&REG[Rtype.rt];
}

void execute_DIVU(const instructionR& Rtype, uint32_t REG[32]){
	LO=Rtype.rs/Rtype.rt;	
	HO=Rtype.rs%Rtype.rt;
} 

/*void execute_DIV(const instructionR& instr, uint32_t& LO, uint32_t& HI){	//signed division
	LO=instr.rs/instr.rt;	
	HO=instr.rs%instr.rt;
}*/

//Itype
void execute_ADDI(const instructionI& Itype, uint32_t REG[32], control& ctrl){ // check for overflow
 	REG[Itype.rd]=REG[Itype.rs]+Itype.IMM;
	overflow(REG[Itype.rd],REG[Itype.rs],Itype.IMM);
}

void execute_ADDIU(const instructionI& Itype, uint32_t REG[32], control& ctrl){
 	REG[Itype.rd]=REG[Itype.rs]+Itype.IMM;
}

void execute_ANDI(const instructionI& Itype, uint32_t REG[32], control& ctrl){
 	REG[Itype.rd]=REG[Itype.rs]&Itype.IMM;
}

void execute_BEQ(const instructionI& Itype, uint32_t REG[32], control& ctrl){
 	if(REG[Itype.rs]==REG[Itype.rd]){
 		ctrl.nPC=Itype.IMM;
 		ctrl.delay1=1;
 	}
 	
}

void execute_BGEZ(const instructionI& Itype, uint32_t REG[32], control& ctrl){
 	if(REG[Itype.rs]>=0){
		ctrl.nPC=Itype.IMM;
		ctrl.delay1=1;
 	}
}

void execute_BGEZAL(const instructionI& Itype, uint32_t REG[32], control& ctrl){
	if(REG[Itype.rs]>=0){
		REG[31]=ctrl.PC+8; // ????
		ctrl.nPC=Itype.IMM;
		ctrl.delay1=1;
	}
}

void execute_BGTZ(const instructionI& Itype, uint32_t REG[32], control& ctrl){
	if(REG[Itype.rs]>0){
		ctrl.nPC=Itype.IMM;
		ctrl.delay1=1;
	}
}

void execute_BLEZ(const instructionI& Itype, uint32_t REG[32], control& ctrl){
	if(REG[Itype.rs]<=0){
		ctrl.nPC=Itype.IMM;
		ctrl.delay1=1;
	}
}

void execute_BLTZ(const instructionI& Itype, uint32_t REG[32], control& ctrl){
	if(REG[Itype.rs]<0){
		ctrl.nPC=Itype.IMM;
		ctrl.delay1=1;
	}
}

void execute_BLTZAL(const instructionI& Itype, uint32_t REG[32], control& ctrl){
	if(REG[Itype.rs]<0){
		ctrl.nPC=Itype.IMM;
		ctrl.delay1=1;
	}
}

void execute_BNE(const instructionI& Itype, uint32_t REG[32], control& ctrl){
	if(REG[Itype.rs]!=REG[Itype.rd]){
		ctrl.nPC=Itype.IMM;
		ctrl.delay1=1;
	}
}


// void execute_JR(const instructionR& instr, uint32_t& nextPC){

// }





//Jtype
// void execute_J(const instructionJ& instr, uint32_t& nextPC){

// }

// void execute_JAL(const instructionJ& instr, uint32_t& nextPC){

// }

