#include <cstdint>
#include <string>
#include <iostream>
#include "rijstructures.hpp"
#include "decode_instruction.hpp"
#include "externgv.h"

const int Arithmetic_Exception = -10;
const int Memory_Exception = -11;
const int Invalid_Instruction_Exception = -12;
const int Internal_Error = -20; 
const int IO_Error = -21;

int32_t HI, LO;

// uint32_t assemble_instruction(const uint8_t ADDR_INSTR[0x1000000], const control &ctrl, const uint32_t& offset_AI){

uint32_t assemble_instruction(const control &ctrl, const uint32_t& offset_AI){
	
	uint32_t offset_PC = ctrl.PC - offset_AI;

	uint32_t instruction = (ADDR_INSTR[offset_PC] << 24 | ADDR_INSTR[offset_PC+1] 
		<< 16| ADDR_INSTR[offset_PC+2] << 8| ADDR_INSTR[offset_PC+3]);

	return instruction;
}

void initialise_control(control &ctrl, const uint32_t& offset_AI){
	ctrl.PC = offset_AI;
	ctrl.nPC = offset_AI;
	ctrl.target = 0;
	ctrl.delay1 = 0;
	ctrl.delay2 = 0;
}



// bool check_PC(control &ctrl, const uint32_t& offset_AI){

// 	if( ctrl.PC == 0){
// 		return false;
// 	}
// 	else if( ctrl.PC <  offset_AI || ctrl.PC >  0x11000000){
// 		std::exit(Memory_Exception);
// 	}
// 	else{

// 		if(ctrl.delay2 == 1){		
// 		  ctrl.PC = ctrl.nPC;
//       ctrl.nPC = 0;
//       ctrl.delay2 = 0;
//     }
//     if(ctrl.delay1 == 1){
//       ctrl.delay2 = 1;
//       ctrl.delay1 = 0;
//     }

//     return true;
// 	}

// }


// void overflow(const int32_t& result, const int32_t& val1, const int32_t& val2){

// 	if( (val1 > 0) && (val2 > 0) && (result <= 0)){
// 		exit(Arithmetic_Exception);
// 	}
// 	if((val1 < 0) && (val2 < 0) && (result >= 0)){
// 		exit(Arithmetic_Exception);
// 	}
// 	if((val1>>31) && (val2>>31) && (!(result>>31)) ){				//this should work
// 		exit(Arithmetic_Exception);
// 	}

// 	if((!(val1>>31)) && (!(val2>>31)) && (result>>31)){
// 		exit(Arithmetic_Exception);
// 	}

// }

std::string decode_instructionRIJ(const uint32_t& instruction){

	uint32_t opcode;
	opcode = instruction >> 26;

	if(opcode == 0){
		std::cerr << "R instruction detected :) " << std::endl;
		return "R";							
	}
	else if( opcode == 2  ||  opcode == 3 ){
		std::cerr << "J instruction detected :) " << std::endl;
		return "J";
	}
	else{
		std::cerr << "I instruction detected :) " << std::endl;
		return "I";
	}

}

void execute_R_type(const instructionR& Rtype, uint32_t REG[32] ){

	switch(Rtype.funct){
		case 0b100000:
			// execute_ADD(Rtype, REG);
		case 0b100001:
			execute_ADDU(Rtype, REG);
			std::cerr << "Case ADDU" << std::endl;
		case 0b100100:
			// execute_AND(Rtype, REG);
		case 0b011010:
			// execute_DIV(Rtype, REG);
		case 0b011011:
			// execute_DIVU(Rtype, REG);
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
			// execute_SYSCALL();							
		case 0b100110:
			// execute_XOR();
		exit(Invalid_Instruction_Exception);	
	}
	// std::cerr << "Outside switch" << std::endl;
}


// std::string execute_I_type(const instructionI& Itype, int32_t REG[32], control &ctrl){
	
// 	switch(Itype.opcode){
// 		case 0b001110:
// 			// execute_XORI();
// 		case 0b101011:
// 			// execute_SW();
// 		case 0b001011:
// 			// execute_SLTIU();
// 		case 0b001010:
// 			// execute_SLTI();
// 		case 0b101000:
// 			// execute_SB();
// 		case 0b001101:
// 			// execute_ORI();
// 		case 0b100011:
// 			// execute_LW();	
// 		case 0b001111:
// 			// execute_LUI();
// 		case 0b100000:
// 			// execute_LB();
// 		case 0b000101:
// 			execute_BNE(Itype, REG, ctrl);
// 		case 0b000001:
// 			if(Itype.rd == 0b10000)
// 				execute_BLTZAL(Itype, REG, ctrl);
// 			if(Itype.rd == 0b0)
// 				execute_BLTZ(Itype, REG, ctrl); 
// 			if(Itype.rd == 0b10001)
// 				execute_BGEZAL(Itype, REG, ctrl);
// 			if(Itype.rd == 0b00001)
// 				execute_BGEZ(Itype, REG, ctrl);
// 		case 0b000111:
// 			execute_BGTZ(Itype, REG, ctrl);
// 		case 0b000110:
// 			execute_BLEZ(Itype, REG, ctrl);
// 		case 0b000100:
// 			execute_BEQ(Itype, REG, ctrl);
// 		case 0b001100:
// 			execute_ANDI(Itype, REG, ctrl);
// 		case 0b001001:
// 			execute_ADDIU(Itype, REG, ctrl);
// 		case 0b001000:
// 			execute_ADDI(Itype, REG, ctrl);
			
// 		exit(Invalid_Instruction_Exception);			
// 	}
// }


// std::string execute_J_type(const instructionJ& Jtype, control &ctrl){
// 	switch(Jtype.opcode){
// 		case 0b000010:
// 			// execute_J();
// 		case 0b000011:
// 			// execute_JAL(Jtype, REG);
// 		exit(Invalid_Instruction_Exception);
// 	}
// }


//Rtype
// void execute_ADD(const instructionR& Rtype, int32_t REG[32]){ //
//  	REG[Rtype.rd]=REG[Rtype.rs]+REG[Rtype.rt];
// 	overflow(REG[Rtype.rd],REG[Rtype.rs],REG[Rtype.rt]);
// }

void execute_ADDU(const instructionR& Rtype, uint32_t REG[32]){
	std::cerr << "execute_ADDU !! \n BEFORE we have \n";
	std::cerr << "REG[" << Rtype.rd << "] = " << REG[Rtype.rd] << std::endl;
	std::cerr << "REG[" << Rtype.rs << "] = " << REG[Rtype.rs] << std::endl;
	std::cerr << "REG[" << Rtype.rt << "] = " << REG[Rtype.rt] << std::endl;
 	REG[Rtype.rd]=REG[Rtype.rs]+REG[Rtype.rt];
 	std::cerr << "After we have, unsigned REG[" << Rtype.rd << "] = " << REG[Rtype.rd] << std::endl;
 	std::cerr << "After we have, signed REG[" << Rtype.rd << "] = " << (int32_t)REG[Rtype.rd] << std::endl;
}

// void execute_AND(const instructionR& Rtype, int32_t REG[32]){
//  	REG[Rtype.rd]=REG[Rtype.rs]&REG[Rtype.rt];
// }

// void execute_DIVU(const instructionR& Rtype, int32_t REG[32]){
// 	LO=REG[Rtype.rs]/REG[Rtype.rt];	
// 	HI=REG[Rtype.rs]%REG[Rtype.rt];
// } 

/*void execute_DIV(const instructionR& Rtype, int32_t REG[32], control &ctrl){	//signed division
	LO=instr.rs/instr.rt;	
	HO=instr.rs%instr.rt;
}*/

//Itype
// void execute_ADDI(const instructionI& Itype, int32_t REG[32], control &ctrl){ // check for overflow
//  	REG[Itype.rd]=REG[Itype.rs]+Itype.IMM;
// 	overflow(REG[Itype.rd],REG[Itype.rs],Itype.IMM);
// }

// void execute_ADDIU(const instructionI& Itype, int32_t REG[32], control &ctrl){
//  	REG[Itype.rd]=REG[Itype.rs]+Itype.IMM;
// }

// void execute_ANDI(const instructionI& Itype, int32_t REG[32], control &ctrl){
//  	REG[Itype.rd]=REG[Itype.rs]&Itype.IMM;
// }

// void execute_BEQ(const instructionI& Itype, int32_t REG[32], control &ctrl){
//  	if(REG[Itype.rs]==REG[Itype.rd]){
//  		ctrl.nPC=Itype.IMM;
//  		ctrl.delay1=1;
//  	}
 	
// }

// void execute_BGEZ(const instructionI& Itype, int32_t REG[32], control &ctrl){
//  	if(REG[Itype.rs]>=0){
// 		ctrl.nPC=Itype.IMM;
// 		ctrl.delay1=1;
//  	}
// }

// void execute_BGEZAL(const instructionI& Itype, int32_t REG[32], control &ctrl){
// 	if(REG[Itype.rs]>=0){
// 		REG[31]=ctrl.PC+8; // ????
// 		ctrl.nPC=Itype.IMM;
// 		ctrl.delay1=1;
// 	}
// }

// void execute_BGTZ(const instructionI& Itype, int32_t REG[32], control &ctrl){
// 	if(REG[Itype.rs]>0){
// 		ctrl.nPC=Itype.IMM;
// 		ctrl.delay1=1;
// 	}
// }

// void execute_BLEZ(const instructionI& Itype, int32_t REG[32], control &ctrl){
// 	if(REG[Itype.rs]<=0){
// 		ctrl.nPC=Itype.IMM;
// 		ctrl.delay1=1;
// 	}
// }

// void execute_BLTZ(const instructionI& Itype, int32_t REG[32], control &ctrl){
// 	if(REG[Itype.rs]<0){
// 		ctrl.nPC=Itype.IMM;
// 		ctrl.delay1=1;
// 	}
// }

// void execute_BLTZAL(const instructionI& Itype, int32_t REG[32], control &ctrl){
// 	if(REG[Itype.rs]<0){
// 		ctrl.nPC=Itype.IMM;
// 		ctrl.delay1=1;
// 	}
// }

// void execute_BNE(const instructionI& Itype, int32_t REG[32], control &ctrl){
// 	if(REG[Itype.rs]!=REG[Itype.rd]){
// 		ctrl.nPC=Itype.IMM;
// 		ctrl.delay1=1;
// 	}
// }


// // void execute_JR(const instructionR& instr, int32_t& nextPC){

// // }





// //Jtype
// // void execute_J(){

// // }

// // void execute_JAL(){

// // }

