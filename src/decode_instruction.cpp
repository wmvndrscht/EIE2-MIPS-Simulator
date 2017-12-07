#include <cstdint>
#include <string>
#include <iostream>
#include "rijstructures.hpp"
#include "decode_instruction.hpp"
#include <cmath>

//----for reference
// const int Arithmetic_Exception = -10;
// const int Memory_Exception = -11;
// const int Invalid_Instruction_Exception = -12;  <- look more at errors
// const int Internal_Error = -20; 
// const int IO_Error = -21;


uint32_t assemble_instruction(const uint8_t* ADDR_INSTR, const control &ctrl, const uint32_t& offset_AI){
	
	uint32_t offset_PC = ctrl.PC - offset_AI;

	uint32_t instruction = (ADDR_INSTR[offset_PC] << 24 | ADDR_INSTR[offset_PC+1] 
		<< 16| ADDR_INSTR[offset_PC+2] << 8| ADDR_INSTR[offset_PC+3]);

	return instruction;
}

void initialise_control(control &ctrl, const uint32_t& offset_AI){
	ctrl.PC = offset_AI;
	ctrl.nPC = offset_AI;
	ctrl.branch_delay = 0;
	ctrl.HI = 0;
	ctrl.LO = 0;
}

void PC_advance(control& ctrl){

  if( ctrl.branch_delay == 0 ){  //if no branch_delay, carry on iterating
    ctrl.PC = ctrl.PC + 4;
  }
  else if(ctrl.branch_delay == 1){  //if branch_delay just occured do the branch stored in nPC, no longer branch delay
    ctrl.PC = ctrl.nPC;
    ctrl.branch_delay = 0;
  }
  else{   //if branch delay set to 2, carry on as normal but - branch delay by 1
    ctrl.PC = ctrl.PC + 4;
    ctrl.branch_delay = 1;
  }


  if( ctrl.PC < 0x10000000 && ctrl.PC > 0){
  	std::exit(-11);
  }

  if( 0x11000000 <= ctrl.PC && ctrl.PC < 0x20000000){
  	std::exit(-11);
  }

  if( ctrl.PC >= 0x24000000){
  	std::exit(-11);
  }

  if( (ctrl.PC & 0x3) != 0x0 ){
  	std::exit(-11);  //memory exception as not multiple of 4
  }

}


std::string decode_instructionRIJ(const uint32_t& instruction){

	uint32_t opcode;
	opcode = instruction >> 26;

	if(opcode == 0){
		std::cerr << "Decode R " << std::endl;
		return "R";							
	}
	else if( opcode == 2  ||  opcode == 3 ){
		std::cerr << "Decode J " << std::endl;
		return "J";
	}
	else{
		std::cerr << "Decode I " << std::endl;
		return "I";
	}

}

void execute_R_type(const instructionR& Rtype, int32_t REG[32], control& ctrl){

	switch(Rtype.funct){
		case 0b100000:
			if(Rtype.shamt==0){
				std::cerr << "ADD" << std::endl;
				execute_ADD(Rtype, REG); //2
				break;}
		case 0b100001:
			if(Rtype.shamt == 0){
				std::cerr << "ADDU" << std::endl;				
				execute_ADDU(Rtype, REG); //1
				break;}
		case 0b100100:
			if(Rtype.shamt == 0){
				std::cerr << "AND" << std::endl;
				execute_AND(Rtype, REG); //1
				break;}
		case 0b011010:
			if(Rtype.shamt == 0 && Rtype.rd == 0){
				std::cerr << "DIV" << std::endl;
				execute_DIV(Rtype, REG, ctrl); //4
				break;}
		case 0b011011:
			if(Rtype.shamt == 0 && Rtype.rd == 0){
				std::cerr << "DIVU" << std::endl;
				execute_DIVU(Rtype, REG, ctrl); //4
				break;}
		case 0b001000:
			if(Rtype.rt == 0 && Rtype.rd == 0 && Rtype.shamt == 0){
				std::cerr << "JR" << std::endl;
				execute_JR(Rtype, REG, ctrl); //1
				break;}
		case 0b001001:
			if(Rtype.rt == 0 && Rtype.shamt == 0){
			std::cerr << "JALR" << std::endl;
			execute_JALR(Rtype, REG, ctrl);
			break;}
		case 0b010000:
			if(Rtype.rs == 0 && Rtype.rt == 0 && Rtype.shamt == 0){
				execute_MFHI(Rtype, REG, ctrl); //3
				std::cerr << "MFHI" << std::endl;
				break;}
		case 0b010010:
			if(Rtype.rs == 0 && Rtype.rt == 0 && Rtype.shamt == 0){
				execute_MFLO(Rtype, REG, ctrl); //3
				std::cerr << "MFLO" << std::endl;
				break;}
		case 0b010001:
			if(Rtype.rd == 0 && Rtype.rt == 0 && Rtype.shamt == 0){
			execute_MTHI(Rtype, REG, ctrl);
			std::cerr << "MTHI" << std::endl;
			break;
			}
		case 0b010011:
			if(Rtype.rd == 0 && Rtype.rt == 0 && Rtype.shamt == 0){
			execute_MTLO(Rtype, REG, ctrl);
			std::cerr << "MTLO" << std::endl;
			break;
			}
		case 0b011000:
			if(Rtype.rd == 0 && Rtype.shamt == 0){
				execute_MULT(Rtype, REG, ctrl);  //4
				std::cerr << "MULT" << std::endl;
				break;}
		case 0b011001:
			if(Rtype.rd == 0 && Rtype.shamt == 0){
				execute_MULTU(Rtype, REG, ctrl);  //4
				std::cerr << "MULTU" << std::endl;
				break;}
		case 0b100101:
			if(Rtype.shamt == 0){
				execute_OR(Rtype, REG);	//1	
				std::cerr << "OR" << std::endl;
				break;}
		case 0b000000:
			if(Rtype.rs == 0){	
			execute_SLL(Rtype, REG); //2 
			std::cerr << "SLL" << std::endl;
			break;}
		case 0b000100:
			if(Rtype.shamt == 0){	
			execute_SLLV(Rtype, REG); //3
			std::cerr << "SLLV" << std::endl;
			break;}
		case 0b101010:
			if(Rtype.shamt == 0){
				execute_SLT(Rtype, REG);  //2
				std::cerr << "SLT" << std::endl;
				break;}
		case 0b101011:
			if(Rtype.shamt == 0){
				execute_SLTU(Rtype, REG); //1
				std::cerr << "SLTU" << std::endl;
				break;}
		case 0b000011:
			if(Rtype.rs == 0){
			execute_SRA(Rtype, REG); //2
			std::cerr << "SRA" << std::endl;
			break;}
		case 0b000111:
			if(Rtype.shamt == 0){
			execute_SRAV(Rtype, REG);
			std::cerr << "SRAV" << std::endl;
			break;}
		case 0b000010:
			if(Rtype.rs == 0){
			execute_SRL(Rtype, REG);  //2
			std::cerr << "SRL" << std::endl;
			break;}
		case 0b000110:
			if(Rtype.shamt == 0){
				execute_SRLV(Rtype, REG); //3
				std::cerr << "SRLV" << std::endl;
				break;}
		case 0b100010:
			if(Rtype.shamt == 0){
				execute_SUB(Rtype, REG); //2
				std::cerr << "SUB" << std::endl;
				break;}
		case 0b100011:
			if(Rtype.shamt == 0){
				std::cerr << "SUBU" << std::endl;
				execute_SUBU(Rtype, REG); //1	
				break;}				
		case 0b100110:
			if(Rtype.shamt == 0){
			execute_XOR(Rtype, REG);  //1
			std::cerr << "XOR" << std::endl;
			break;}
		default:
			std::exit(-12); //invalid instrution type
		std::cerr << "LALA" << std::endl;
	}
	std::cerr << "Outside switch" << std::endl;
}

void execute_ADD(const instructionR& Rtype, int32_t REG[32]){ //edge cases 0xFFFFFFFF + 0xFFFFFFFF, overflow??
	if( overflow(REG[Rtype.rs], REG[Rtype.rt]) ){
		std::cerr << "ADD not executed due to overflow" << std::endl;
		std::exit(-10);//Arithmetic_Exception
	}
	else{
		REG[Rtype.rd] = REG[Rtype.rs] + REG[Rtype.rt];
		std::cerr << "ADD executed" << std::endl;
	}
}

void execute_ADDU(const instructionR& Rtype, int32_t REG[32]){ //edge cases 0xFFFFFFFF + 0xFFFFFFFF, wrap around?
 	REG[Rtype.rd] = (uint32_t)REG[Rtype.rs] + (uint32_t)REG[Rtype.rt]; //any reason why there weren't uint32_t here?
}

void execute_AND(const instructionR& Rtype, int32_t REG[32]){  //simple, tested
	REG[Rtype.rd] = REG[Rtype.rs] & REG[Rtype.rt];
}

void execute_OR(const instructionR& Rtype, int32_t REG[32]){  //simple, tested
	REG[Rtype.rd] = REG[Rtype.rs] | REG[Rtype.rt];
}

void execute_XOR(const instructionR& Rtype, int32_t REG[32]){  //simple, tested
	REG[Rtype.rd] = (uint32_t)REG[Rtype.rs] ^ (uint32_t)REG[Rtype.rt];
}

void execute_SUBU(const instructionR& Rtype, int32_t REG[32]){  //sub overflow, 1 -2 etc, tested
	REG[Rtype.rd] = (uint32_t)REG[Rtype.rs] - (uint32_t)REG[Rtype.rt];  //any reason why weren't uin32_t before??
}

void execute_JR(const instructionR& Rtype, int32_t REG[32], control& ctrl){ //correct Rtype bits, valid does delay etc..?, tested
	ctrl.nPC = REG[Rtype.rs];
	ctrl.branch_delay = 2;
}

void execute_SLTU(const instructionR& Rtype, int32_t REG[32]){  //simple 1 or 0 with correct register, tested
	REG[Rtype.rd] = (uint32_t)REG[Rtype.rs] < (uint32_t)REG[Rtype.rt];
}

void execute_SUB(const instructionR& Rtype, int32_t REG[32]){ //tested
	if( overflow_SUB(REG[Rtype.rs], REG[Rtype.rt]) ){
		std::exit(-10);//Arithmetic_Exception
	}
	else{
		REG[Rtype.rd] = REG[Rtype.rs]-REG[Rtype.rt];
	}
}

void execute_SLT(const instructionR& Rtype, int32_t REG[32]){  //tested, says arithmetic comparison does not cause Integer Overflow??, tested
	REG[Rtype.rd] = REG[Rtype.rs] < REG[Rtype.rt];
}

void execute_SRA(const instructionR& Rtype, int32_t REG[32]){ //tested
	REG[Rtype.rd] = REG[Rtype.rt] >> Rtype.shamt;	
}

void execute_SRAV(const instructionR& Rtype, int32_t REG[32]){ //tested, signed values for sign extension and correct variable shift
	REG[Rtype.rd] = REG[Rtype.rt] >> (REG[Rtype.rs] & 0x1F);
}

void execute_SRL(const instructionR& Rtype, int32_t REG[32]){
	REG[Rtype.rd] = (uint32_t)REG[Rtype.rt] >> (uint32_t)Rtype.shamt; //tested, make sure 0's inserted
	// REG[Rtype.rd] = REG[Rtype.rd] & (pow(2, 32 - Rtype.shamt) -1) ;
}
//----------------------------------------------------------------17:00
void execute_SLL(const instructionR& Rtype, int32_t REG[32]){  //tested, simple
	REG[Rtype.rd] = (uint32_t)REG[Rtype.rt] << (uint32_t)Rtype.shamt;
}

void execute_SLLV(const instructionR& Rtype, int32_t REG[32]){  //tested. simple
	REG[Rtype.rd] = REG[Rtype.rt] << (REG[Rtype.rs]&0x1F); // the value in REG can be huge, we should only use the lowest 5 bits
}

void execute_SRLV(const instructionR& Rtype, int32_t REG[32]){  //tested, simple
	REG[Rtype.rd] = (uint32_t)REG[Rtype.rt] >> (uint32_t)(REG[Rtype.rs]&0x1F); // same thing here
}

void execute_MFHI(const instructionR& Rtype, int32_t REG[32], control& ctrl){ //weird to test..., just need to move to high and back
	REG[Rtype.rd] = ctrl.HI;  //this seems too simple hmmmm
}

void execute_MFLO(const instructionR& Rtype, int32_t REG[32], control& ctrl){
	REG[Rtype.rd] = ctrl.LO;  //this seems too simple hmmmm
}

void execute_MTHI(const instructionR& Rtype, int32_t REG[32], control& ctrl){
	ctrl.HI = REG[Rtype.rs];
}

void execute_MTLO(const instructionR& Rtype, int32_t REG[32], control& ctrl){
	ctrl.LO = REG[Rtype.rs];
}

void execute_DIVU(const instructionR& Rtype, int32_t REG[32], control& ctrl){  //test big vals
	if(Rtype.rt != 0 ){
		ctrl.LO = uint32_t(((uint32_t)REG[Rtype.rs])/((uint32_t)REG[Rtype.rt]));	
		ctrl.HI = uint32_t(((uint32_t)REG[Rtype.rs])%((uint32_t)REG[Rtype.rt]));
	}
	else{
		return; //do nothing if divide by 0
	}
} 

void execute_DIV(const instructionR& Rtype, int32_t REG[32], control &ctrl){	//signed division
	if(Rtype.rt != 0 ){
		ctrl.LO = (int32_t)REG[Rtype.rs]/(int32_t)REG[Rtype.rt];	//what does arithmetic result is undefined really mean??
		ctrl.HI = (int32_t)REG[Rtype.rs]%(int32_t)REG[Rtype.rt];
	}
	else{
		return; //do nothing if divide by 0
	}
}

void execute_MULTU(const instructionR& Rtype, int32_t REG[32], control &ctrl){
	uint64_t temp = uint64_t(uint64_t(REG[Rtype.rs]) * uint64_t(REG[Rtype.rt]));
	ctrl.LO = (uint32_t) (temp & 0xFFFFFFFF);
	ctrl.HI = (uint32_t) ((temp >> 32) & 0xFFFFFFFF);
}

void execute_MULT(const instructionR& Rtype, int32_t REG[32], control &ctrl){
	uint64_t temp = (int64_t)REG[Rtype.rs] * (int64_t)REG[Rtype.rt];
	ctrl.LO = (int32_t)(temp & 0xFFFFFFFF);  //WHAT IS THE SIGN EXTEND THING
	ctrl.HI = (int32_t) ((temp >> 32)& 0xFFFFFFFF);
}

void execute_JALR(const instructionR& Rtype, int32_t REG[32], control &ctrl){
	ctrl.nPC = REG[Rtype.rs];
	REG[Rtype.rd] = ctrl.PC + 8;
	ctrl.branch_delay = 2;
}

//----------------------------------Itype----------------------------------------------------------

void execute_I_type(const instructionI& Itype, int32_t REG[32], control &ctrl, uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR){
	std::cerr << "Reaches I type" << std::endl;
	switch(Itype.opcode){
		case 0b001110:
			execute_XORI(Itype, REG);
			std::cerr << "XORI" << std::endl;
			break;
		case 0b101011:
			execute_SW(Itype, REG, ADDR_DATA);
			std::cerr << "SW" << std::endl;
			break;
		case 0b001011:
			execute_SLTIU(Itype, REG);
			std::cerr << "SLTIU" << std::endl;
			break;
		case 0b001010:
			execute_SLTI(Itype, REG);
			std::cerr << "SLTI" << std::endl;
			break;
		case 0b101000:
			std::cerr << "SB" << std::endl;
			execute_SB(Itype, REG, ADDR_DATA);
			break;
		case 0b001101:
			execute_ORI(Itype, REG);
			std::cerr << "ORI" << std::endl;
			break;
		case 0b100011:
			execute_LW(Itype, REG, ADDR_DATA, ADDR_INSTR);
			std::cerr << "LW" << std::endl;
			break;
		case 0b001111:
			execute_LUI(Itype, REG);
			std::cerr << "LUI" << std::endl;
			break;
		case 0b100000:
			std::cerr << "LB" << std::endl;
			execute_LB(Itype, REG, ADDR_DATA, ADDR_INSTR);
			break;
		case 0b000101:
			execute_BNE(Itype, REG, ctrl);
			std::cerr << "BNE" << std::endl;
			break;
		case 0b000001:
			if(Itype.rd == 0b10000){
				execute_BLTZAL(Itype, REG, ctrl);
				std::cerr << "BLTZAL" << std::endl;
				break;}
			if(Itype.rd == 0b0){
				execute_BLTZ(Itype, REG, ctrl);
				std::cerr << "BLTZ" << std::endl;
				break;}
			if(Itype.rd == 0b10001){
				execute_BGEZAL(Itype, REG, ctrl);
				std::cerr << "BGEZAL" << std::endl;
				break;}
			if(Itype.rd == 0b00001){
				execute_BGEZ(Itype, REG, ctrl);
				std::cerr << "BGEZ" << std::endl;			
				break;}
		case 0b000111:
			if(Itype.rd == 0){
				execute_BGTZ(Itype, REG, ctrl);
				std::cerr << "BGTZ" << std::endl;
				break;}
		case 0b000110:
			if(Itype.rd == 0){
				execute_BLEZ(Itype, REG, ctrl);
				std::cerr << "BLEZ" << std::endl;
				break;}
		case 0b000100:
			execute_BEQ(Itype, REG, ctrl);
			std::cerr << "BEQ" << std::endl;
			break;
		case 0b001100:
			execute_ANDI(Itype, REG);
			std::cerr << "ANDI" << std::endl;
			break;
		case 0b001001:
			execute_ADDIU(Itype, REG);
			std::cerr << "ADDIU" << std::endl;
			break;
		case 0b001000:
			execute_ADDI(Itype, REG);
			std::cerr << "ADDI" << std::endl;
			break;
		case 0b100010:
			std::cerr << "LWL" << std::endl;
			execute_LWL(Itype, REG, ADDR_DATA, ADDR_INSTR);
			std::cerr << "LWL" << std::endl;
			break;
		case 0b100110:
			std::cerr << "LWR" << std::endl;
			execute_LWR(Itype, REG, ADDR_DATA, ADDR_INSTR);
			std::cerr << "LWR" << std::endl;
			break;
		case 0b100101:
			execute_LHU(Itype, REG, ADDR_DATA, ADDR_INSTR);
			std::cerr << "LHU" << std::endl;
			break;
		case 0b100001:
			execute_LH(Itype, REG, ADDR_DATA, ADDR_INSTR);
			std::cerr << "LH" << std::endl;
			break;
		case 0b101001:
			execute_SH(Itype, REG, ADDR_DATA);
			std::cerr << "SH" << std::endl;
			break;
		case 0b100100:
			execute_LBU(Itype, REG, ADDR_DATA, ADDR_INSTR);
			std::cerr << "LBU" << std::endl;
			break;
		default:
			std::exit(-12); //invalid instrution type
	//std::exit(Invalid_Instruction_Exception);			
	}
}

//-------------------------------------------Itype-----------------------------------------------------

void execute_ADDI(const instructionI& Itype, int32_t REG[32]){ // check for overflow, correct imm etc
	if( overflow(REG[Itype.rs], Itype.IMMs) ){
		exit(-10); //arithmetic overflow exception
	}
	REG[Itype.rd] = REG[Itype.rs] + Itype.IMMs;
}

void execute_ADDIU(const instructionI& Itype, int32_t REG[32]){  //is it wrap around or not? does not trap overflow!!!!!
 	REG[Itype.rd] = REG[Itype.rs] + Itype.IMM;
}

void execute_ANDI(const instructionI& Itype, int32_t REG[32]){  //simple, make sure immediate is zero-extended
 	REG[Itype.rd] = REG[Itype.rs] & (uint32_t)Itype.IMM;
}

void execute_BEQ(const instructionI& Itype, int32_t REG[32], control &ctrl){  //18-bit signed, hmmmm ???
 	if(REG[Itype.rs] == REG[Itype.rd]){
 		ctrl.nPC = (int32_t)ctrl.PC + (Itype.IMMs << 2) + 4;  //adding the relative offset right?
 		ctrl.branch_delay = 2;
 	}
 	return;
}

void execute_BGEZ(const instructionI& Itype, int32_t REG[32], control &ctrl){
 	if(REG[Itype.rs] >= 0){
 		ctrl.nPC = (int32_t)ctrl.PC + (Itype.IMMs << 2) + 4;  //adding the relative offset right?
 		ctrl.branch_delay = 2;
 	}
}

void execute_BGEZAL(const instructionI& Itype, int32_t REG[32], control &ctrl){  //passed++++
	if(REG[Itype.rs] >= 0){
		ctrl.nPC = (int32_t)ctrl.PC + (Itype.IMMs << 2) + 4;
		ctrl.branch_delay = 2;
	}
	REG[31] = ctrl.PC + 8; // ????
}

void execute_BGTZ(const instructionI& Itype, int32_t REG[32], control &ctrl){
	if(REG[Itype.rs] > 0){
		ctrl.nPC = (int32_t)ctrl.PC + (Itype.IMMs << 2) + 4;
		ctrl.branch_delay = 2;
	}
}

void execute_BLEZ(const instructionI& Itype, int32_t REG[32], control &ctrl){
	if(REG[Itype.rs] <= 0){
		ctrl.nPC = (int32_t)ctrl.PC + (Itype.IMMs << 2) + 4;
		ctrl.branch_delay = 2;
	}
}

void execute_BLTZ(const instructionI& Itype, int32_t REG[32], control &ctrl){
	if(REG[Itype.rs] < 0){
		ctrl.nPC = (int32_t)ctrl.PC + (Itype.IMMs << 2) + 4;
		ctrl.branch_delay = 2;
	}
}
//---------------------------
void execute_BLTZAL(const instructionI& Itype, int32_t REG[32], control &ctrl){
	if(REG[Itype.rs] < 0){
		ctrl.nPC = (int32_t)ctrl.PC + (Itype.IMMs << 2) + 4;
		ctrl.branch_delay = 2;
	}
	REG[31] = ctrl.PC + 8;
}

void execute_BNE(const instructionI& Itype, int32_t REG[32], control &ctrl){
	if(REG[Itype.rs] != REG[Itype.rd]){
		ctrl.nPC = (int32_t)ctrl.PC + (Itype.IMMs << 2) + 4;
		ctrl.branch_delay = 2;
	}
}

void execute_LB(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR){
	std::string place;
	uint32_t offset_PC = REG[Itype.rs] + Itype.IMMs;
	check_location(offset_PC, place);
	if(place == "ADDR_DATA"){
		REG[Itype.rd] = sign_extend_8(ADDR_DATA[offset_PC]);
	}
	else if(place == "ADDR_INSTR"){
		REG[Itype.rd] = sign_extend_8(ADDR_INSTR[offset_PC]);
	}
	else if( place == "GETC"){
		int32_t c;
		c = std::getchar();
		REG[Itype.rd] = c;
	}
	else{
		exit(-11);
	}
}

void check_location(uint32_t &offset_PC, std::string &place){
	std::cerr << "Check location offset_PC = " << offset_PC << std::endl;
	if( (0x10000000 <= offset_PC) && (offset_PC < 0x11000000) ){
		offset_PC = offset_PC - 0x10000000;
		place = "ADDR_INSTR";
		std::cerr << "place = ADDR_INSTR" << std::endl;
	}
	else if( (0x20000000 <= offset_PC) && (offset_PC < 0x24000000) ){
		offset_PC = offset_PC - 0x20000000;
		place = "ADDR_DATA";
		std::cerr << "place = ADDR_DATA" << std::endl;
	}
	else if( (0x30000000 <= offset_PC) && (offset_PC < 0x30000004)){
		std::cerr << "GETC" << std::endl;
		place = "GETC";
		std::cerr << "place = GETC" << std::endl;
	}
	else if( (0x30000004 <= offset_PC) && (offset_PC < 0x30000008)){
		std::cerr << "PUTC" << std::endl;
		place = "PUTC";
	}
	else{
		std::exit(-11);
	}
}

void execute_LUI(const instructionI& Itype, int32_t REG[32]){
	REG[Itype.rd] = Itype.IMM << 16;
}

void execute_LW(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR){
	uint32_t offset_PC = 	REG[Itype.rs] + Itype.IMMs;
	std::string place;
	if( offset_PC%4 != 0){
		std::exit(-11); //address error exception
	}
	check_location(offset_PC, place);
	if(place == "ADDR_DATA"){
		REG[Itype.rd] = (ADDR_DATA[offset_PC] << 24 | ADDR_DATA[offset_PC+1] 
			<< 16| ADDR_DATA[offset_PC+2] << 8 | ADDR_DATA[offset_PC+3]);
	}
	else if(place == "ADDR_INSTR"){
		REG[Itype.rd] = (ADDR_INSTR[offset_PC] << 24 | ADDR_INSTR[offset_PC+1] 
			<< 16| ADDR_INSTR[offset_PC+2] << 8 | ADDR_INSTR[offset_PC+3]);
	}
	else if( place == "GETC"){
		int32_t c;
		c = std::getchar();
		REG[Itype.rd] = c;
	}
	else{
		exit(-11);
	}
}

void execute_ORI(const instructionI& Itype, int32_t REG[32]){
	REG[Itype.rd] = (uint32_t)REG[Itype.rs] | Itype.IMM;
}

void execute_SB(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA){
	uint32_t offset_PC = REG[Itype.rs] + Itype.IMMs;
	std::string place;
	check_location(offset_PC, place);
	if( place == "ADDR_DATA"){
		ADDR_DATA[offset_PC] = (uint8_t)(REG[Itype.rd] & 0xFF);
	}
	else if(place == "ADDR_INSTR"){
		std::cerr << "Cannot write to instruction area " << std::endl;
		exit(-11);} //ADDR_INSTR one cannot write to
	else if( place == "PUTC"){
		std::putchar( (uint8_t)(REG[Itype.rd] & 0xFF) );
	}
	else{
		std::exit(-11);
	}
}

void execute_SLTI(const instructionI& Itype, int32_t REG[32]){
 	REG[Itype.rd] = REG[Itype.rs] < Itype.IMMs; // sign extension needed
}

void execute_SLTIU(const instructionI& Itype, int32_t REG[32]){
 	REG[Itype.rd] = (uint32_t)REG[Itype.rs] < (uint32_t)Itype.IMMs;
}

void execute_SW(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA){
	uint32_t offset_PC = REG[Itype.rs] + Itype.IMMs;
	if(offset_PC%4 != 0){
		std::exit(-11); //address error exception
	}
	std::string place;
	check_location(offset_PC, place);
	if(place == "ADDR_DATA"){
	 	ADDR_DATA[offset_PC] = uint8_t ((uint32_t(REG[Itype.rd]) >> 24)&0xFF);			// this might cause problems
		ADDR_DATA[offset_PC+1] = uint8_t ((uint32_t(REG[Itype.rd]) >> 16)&0xFF);
		ADDR_DATA[offset_PC+2] = uint8_t ((uint32_t(REG[Itype.rd]) >> 8)&0xFF); 
		ADDR_DATA[offset_PC+3] = uint8_t (uint32_t(REG[Itype.rd])&0xFF);  //how does this go???1!!!!!
	}
	else if( place == "ADDR_INSTR"){
		exit(-11);
	}
	else if( place == "PUTC"){
		std::putchar( uint8_t (uint32_t(REG[Itype.rd])&0xFF));
	}
	else{
		std::exit(-11);
	}
}

void execute_XORI(const instructionI& Itype, int32_t REG[32]){
 	REG[Itype.rd] = REG[Itype.rs] ^ Itype.IMM;
}

void execute_LBU(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR){
	uint32_t offset_PC = REG[Itype.rs] + Itype.IMMs;
	std::string place;
	check_location(offset_PC, place);
	if(place == "ADDR_DATA"){
		REG[Itype.rd] = (int32_t) ADDR_DATA[ offset_PC ];  //may need to check address is in range
	}
	else if(place == "ADDR_INSTR"){
		REG[Itype.rd] = (int32_t) ADDR_INSTR[ offset_PC ]; 
	}
	else if( place == "GETC"){
		int32_t c;
		c = std::getchar();
		REG[Itype.rd] = c;
	}
	else{
		exit(-11);
	}
}

void execute_LH(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR){
	uint32_t offset_PC = REG[Itype.rs] + Itype.IMMs;
	if(offset_PC%2 != 0){
		std::exit(-11); //address error exception
	}
	std::string place;
	check_location(offset_PC, place);
	if(place == "ADDR_DATA"){
		REG[Itype.rd] = (ADDR_DATA[offset_PC] << 8 | ADDR_DATA[offset_PC+1]);
		REG[Itype.rd] = sign_extend_16(REG[Itype.rd]);
	}
	else if(place == "ADDR_INSTR"){
		REG[Itype.rd] = (ADDR_INSTR[offset_PC] << 8 | ADDR_INSTR[offset_PC+1]);
		REG[Itype.rd] = sign_extend_16(REG[Itype.rd]);
	}
	else if( place == "GETC"){
		int32_t c;
		c = std::getchar();
		REG[Itype.rd] = c;
	}
	else{
		exit(-11);
	}
}

void execute_LHU(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR){
	uint32_t offset_PC = REG[Itype.rs] + Itype.IMMs;
	if(offset_PC%2 != 0){
		std::exit(-11); //address error exception
	}
	std::string place;
	check_location(offset_PC, place);
	if(place == "ADDR_DATA"){
		REG[Itype.rd] = (0x0000 << 16)| (ADDR_DATA[offset_PC] << 8 | ADDR_DATA[offset_PC+1]);
	}
	else if(place == "ADDR_INSTR"){
		REG[Itype.rd] = (0x0000 << 16)| (ADDR_INSTR[offset_PC] << 8 | ADDR_INSTR[offset_PC+1]);
	}
	else if( place == "GETC"){
		int32_t c;
		c = std::getchar();
		REG[Itype.rd] = c;
	}
	else{
		exit(-11);
	}
}
void execute_SH(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA){
	uint32_t offset_PC = Itype.IMMs + (uint32_t)Itype.rs;
	if(offset_PC%2 != 0){
		std::exit(-11); //address error exception
	}
	std::string place;
	check_location(offset_PC, place);

	if(place == "ADDR_DATA"){
 		ADDR_DATA[offset_PC] = (uint8_t)((REG[Itype.rd] & 0xFF00) >> 8);
 		ADDR_DATA[offset_PC+1] = (uint8_t)(REG[Itype.rd] & 0xFF);
	}
	else if( place == "ADDR_INSTR"){
		exit(-11);
	}
	else if( place == "PUTC"){
		std::putchar( (uint8_t)(REG[Itype.rd] & 0xFF));
	}
	else{
		std::exit(-11);
	}
}

void execute_LWL(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR){
	uint32_t offset_PC = ((Itype.IMMs + Itype.rs)&0xFFFFFFFC);

	std::string place;
	check_location(offset_PC, place);
	uint32_t data;
	if(place == "ADDR_DATA"){
		std::cerr << "Place: " << place << "\n";
		data = (ADDR_DATA[offset_PC] << 24 | ADDR_DATA[offset_PC+1] << 16|	ADDR_DATA[offset_PC+2] << 8| ADDR_DATA[offset_PC+3]);
	}
	if(place == "ADDR_INSTR"){
		std::cerr << "Place: " << place << "\n";
		data = (ADDR_INSTR[offset_PC] << 24 | ADDR_INSTR[offset_PC+1] << 16|	ADDR_INSTR[offset_PC+2] << 8| ADDR_INSTR[offset_PC+3]);
	}

	if( place == "ADDR_DATA" || place == "ADDR_INSTR"){
		uint32_t EffAddr = Itype.IMMs + Itype.rs;
	 	uint32_t lsbs = 0x3 & EffAddr;
		uint32_t mask;
		uint32_t mask2=0;
		if( lsbs == 0x0){
			mask = 0xFFFFFFFF;
			mask2 = 0x0;
		}
		else if( lsbs == 0x1){
			mask = 0x00FFFFFF;
			mask2 = 0x000000FF;
		}
		else if( lsbs == 0x2){
			mask = 0x0000FFFF;
			mask2 = mask;
		}
		else{
			mask = 0x000000FF;
			mask2 = 0x00FFFFFF;
		}
		data = (data & mask) ;
		data = data << (8*lsbs);
		REG[Itype.rd] = mask2 & REG[Itype.rd];
		REG[Itype.rd] = data | REG[Itype.rd];
	}
	else if( place == "GETC"){
		int32_t c;
		c = std::getchar();
		REG[Itype.rd] = c;
	}
	else{
		exit(-11);
	}
}


void execute_LWR(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR){
	uint32_t offset_PC = ((Itype.IMMs + Itype.rs)&0xFFFFFFFC);
	std::string place;
	check_location(offset_PC, place);
	uint32_t data;
	if(place == "ADDR_DATA"){
		std::cerr << "Place: " << place << "\n";
		data = (ADDR_DATA[offset_PC] << 24 | ADDR_DATA[offset_PC+1] << 16|	ADDR_DATA[offset_PC+2] << 8| ADDR_DATA[offset_PC+3]);
	}
	if(place == "ADDR_INSTR"){
		std::cerr << "Place: " << place << "\n";
		data = (ADDR_INSTR[offset_PC] << 24 | ADDR_INSTR[offset_PC+1] << 16|	ADDR_INSTR[offset_PC+2] << 8| ADDR_INSTR[offset_PC+3]);
	}

	if( place == "ADDR_DATA" || place == "ADDR_INSTR"){
		uint32_t EffAddr = Itype.IMMs + Itype.rs;
		uint32_t lsbs = 0x3 & EffAddr;
		uint32_t mask;
		uint32_t mask2;
		if( lsbs == 0x0){
			mask = 0xFF000000;
			mask2 = 0xFFFFFF00;
		}
		else if( lsbs == 0x1){
			mask = 0xFFFF0000;
			mask2 = mask;
		}
		else if( lsbs == 0x2){
			mask = 0xFFFFFF00;
			mask2 = 0xFF000000;
		}
		else{
			//mask = 0x000000FF; 
			mask = 0xFFFFFFFF;
			mask2 = 0x0;
		}
		data = data & mask;
		data = data >> (32-(8*(lsbs+1)));

		REG[Itype.rd] = (mask2) & REG[Itype.rd];
		REG[Itype.rd] = REG[Itype.rd] | data;
	}
	else if( place == "GETC"){
		int32_t c;
		c = std::getchar();
		REG[Itype.rd] = c;
	}
	else{
		exit(-11);
	}
}


//-----------------------------------------------Jtype----------------------------------------------

void execute_J_type(const instructionJ& Jtype, int32_t REG[32], control &ctrl){
	switch(Jtype.opcode){
		case 0b000010:
			execute_J(Jtype,ctrl);
			std::cerr << "J" << std::endl;
			break;
		case 0b000011:
			execute_JAL(Jtype, REG, ctrl);
			std::cerr << "JAL" << std::endl;
			break;
		default:
			std::exit(-12); //invalid instruction type
		//std::exit(Invalid_Instruction_Exception);
	}
}


void execute_J(const instructionJ& Jtype, control &ctrl){
	ctrl.branch_delay = 2;
	ctrl.nPC = ( (ctrl.PC+4) & 0xF0000000) | (Jtype.address << 2);
}


void execute_JAL(const instructionJ& Jtype, int32_t REG[32], control &ctrl){
	ctrl.branch_delay = 2;
	REG[31] = ctrl.PC + 8;
	ctrl.nPC = ( (ctrl.PC+4) & 0xF0000000) | (Jtype.address << 2);
	return;
}



/*void overflow_OLD(const int32_t& result, const int32_t& val1, const int32_t& val2){

	if( (val1 > 0) && (val2 > 0) && (result <= 0)){
		return true;
	}
	if((val1 < 0) && (val2 < 0) && (result >= 0)){
		return true;
	}
	if((val1>>31) && (val2>>31) && (!(result>>31)) ){				//this should work
		return true;
	}

	if((!(val1>>31)) && (!(val2>>31)) && (result>>31)){
		return true;
	}
	return false;
}*/

bool overflow_SUB(const int32_t& rs, const int32_t& rt){
	int32_t temp_rs = rs;
	int32_t temp_rt = rt;
	int32_t check = (int32_t)temp_rs - (int32_t)temp_rt;
	temp_rt = temp_rt & 0x80000000;
	temp_rs = temp_rs & 0x80000000;
	check = check & 0x80000000; 
	std::cerr << temp_rs << " " << temp_rt << " " << check << "\n";
	if((rs >= 0) && (rt < 0) && (check < 0)){
		return true;
	}
	if((rs < 0) && (rt >= 0) && (check >= 0)){
		return true;
	}
	std::cerr << temp_rs << " " << temp_rt << " " << check << "\n";
	/* temp_rs = rt;
	 temp_rt = rs;
	check = (int32_t)temp_rs - (int32_t)temp_rt;
	temp_rt = temp_rt & 0x80000000;
	temp_rs = temp_rs & 0x80000000;
	check = check & 0x80000000; 
	if(temp_rs && !(temp_rt) && !(check)){
		return true;
	}
	if(!(temp_rt) && temp_rs && check){
		return true;
	}*/
	
	return false;
}
bool overflow(const int32_t& rs, const int32_t& rt){
	uint32_t temp_rs = (uint32_t)rs;
	uint32_t temp_rt = (uint32_t)rt;
	uint32_t check = (uint32_t)temp_rs + (uint32_t)temp_rt;
	temp_rt = temp_rt >> 31;
	temp_rs = temp_rs >> 31;
	check = check >> 31; 
	if(temp_rs && temp_rt && !(check))
		return true;
	if(!(temp_rt) && !(temp_rs) && check)
		return true;
	return false;
	/*
	if(check > 0xFFFFFFFF){ this detects all neg+neg as overflow
		return true;
	}
	else{
		return false;
	}*/
}


int32_t sign_extend_8(const uint8_t& byte){
	int32_t temp = (int32_t)byte;
	if(byte >> 7){
		temp = temp | 0xFFFFFF00;
	}
	return temp;
}

int32_t sign_extend_16(const uint32_t& half){
	int32_t temp = (int32_t)half;
	if(half >> 15){
		temp = temp | 0xFFFF0000;
	}
	return temp;
}