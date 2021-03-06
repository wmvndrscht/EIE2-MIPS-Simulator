#ifndef _DECODE_INSTRUCTION
#define _DECODE_INSTRUCTION

#include <cstdint>
#include "rijstructures.hpp"



struct control{
	uint32_t PC;
	uint32_t nPC;
	int branch_delay;
	// uint32_t target;
	// int delay1;
	// int delay2;
	int32_t HI;
	int32_t LO;
};

uint32_t assemble_instruction(const uint8_t* ADDR_INSTR, const control &ctrl, const uint32_t& offset_AI);

bool check_PC(control& ctrl, const uint32_t& offset_AI);
void PC_advance(control& ctrl);
void initialise_control(control &ctrl, const uint32_t& offset_AI);
// void overflow(const int& result, const int& val1, const int& val2);
bool overflow(const int32_t& rs, const int32_t& rt);
bool overflow_SUB(const int32_t& rs, const int32_t& rt);
//void overflow_OLD(const int32_t& result, const int32_t& val1, const int32_t& val2);
int32_t sign_extend_8(const uint8_t& byte);
int32_t sign_extend_16(const uint32_t& half);
void check_location(uint32_t &offset_PC, std::string &place);

std::string decode_instructionRIJ(const uint32_t& instruction);
void execute_R_type(const instructionR& Rtype, int32_t REG[32], control& ctrl);
void execute_I_type(const instructionI& Itype, int32_t REG[32], control &ctrl, uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR);
void execute_J_type(const instructionJ& Jtype, int32_t REG[32], control &ctrl);

//------------------------------Rtype------------------------------- 25
void execute_ADD(const instructionR& Rtype, int32_t REG[32]);
void execute_ADDU(const instructionR& Rtype, int32_t REG[32]);
void execute_AND(const instructionR& Rtype, int32_t REG[32]);
void execute_DIV(const instructionR& Rtype, int32_t REG[32], control &ctrl);
void execute_DIVU(const instructionR& Rtype, int32_t REG[32], control& ctrl);
void execute_JR(const instructionR& Rtype, int32_t REG[32], control& ctrl);
void execute_JALR(const instructionR& Rtype, int32_t REG[32], control &ctrl);
void execute_MFHI(const instructionR& Rtype, int32_t REG[32], control& ctrl);
void execute_MFLO(const instructionR& Rtype, int32_t REG[32], control& ctrl);
void execute_MTLO(const instructionR& Rtype, int32_t REG[32], control& ctrl);
void execute_MTHI(const instructionR& Rtype, int32_t REG[32], control& ctrl);
void execute_MULTU(const instructionR& Rtype, int32_t REG[32], control &ctrl);
void execute_MULT(const instructionR& Rtype, int32_t REG[32], control &ctrl);
void execute_OR(const instructionR& Rtype, int32_t REG[32]);
void execute_SLL(const instructionR& Rtype, int32_t REG[32]);
void execute_SLLV(const instructionR& Rtype, int32_t REG[32]);
void execute_SLT(const instructionR& Rtype, int32_t REG[32]);
void execute_SLTU(const instructionR& Rtype, int32_t REG[32]);
void execute_SRA(const instructionR& Rtype, int32_t REG[32]);
void execute_SRAV(const instructionR& Rtype, int32_t REG[32]);
void execute_SRL(const instructionR& Rtype, int32_t REG[32]);
void execute_SRLV(const instructionR& Rtype, int32_t REG[32]);
void execute_SUB(const instructionR& Rtype, int32_t REG[32]);
void execute_SUBU(const instructionR& Rtype, int32_t REG[32]);
void execute_XOR(const instructionR& Rtype, int32_t REG[32]);

//------------------------------Itype------------------------------- 26

void execute_XORI(const instructionI& Itype, int32_t REG[32]);
void execute_SW(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA);
void execute_SLTIU(const instructionI& Itype, int32_t REG[32]);
void execute_SLTI(const instructionI& Itype, int32_t REG[32]);
void execute_SB(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA);
void execute_ORI(const instructionI& Itype, int32_t REG[32]);
void execute_LW(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR);
void execute_LUI(const instructionI& Itype, int32_t REG[32]);
void execute_LB(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR);
void execute_BNE(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BLTZAL(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BLTZ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BGEZAL(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BGEZ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BGTZ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BLEZ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BEQ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_ANDI(const instructionI& Itype, int32_t REG[32]);
void execute_ADDIU(const instructionI& Itype, int32_t REG[32]);
void execute_ADDI(const instructionI& Itype, int32_t REG[32]);
void execute_LWL(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR);	
void execute_LWR(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR);	
void execute_LHU(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR);	
void execute_LH(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR);	
void execute_SH(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA);
void execute_LBU(const instructionI& Itype, int32_t REG[32], uint8_t* ADDR_DATA, uint8_t* ADDR_INSTR);

//------------------------------Jtype-------------------------------
void execute_J(const instructionJ& Jtype, control &ctrl);
void execute_JAL(const instructionJ& Jtype, int32_t REG[32], control &ctrl);


#endif //_DECODE_INSTRUCTION