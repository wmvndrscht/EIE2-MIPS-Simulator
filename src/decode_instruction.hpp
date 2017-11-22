#ifndef _DECODE_INSTRUCTION
#define _DECODE_INSTRUCTION

#include <cstdint>
#include "rijstructures.hpp"



struct control{
	uint32_t PC;
	uint32_t nPC;
	uint32_t target;
	int delay1;
	int delay2;
};

uint32_t assemble_instruction(const uint8_t ADDR_INSTR[0x1000000], const control &ctrl, const uint32_t& offset_AI);
bool check_PC(control &ctrl, const uint32_t& offset_AI);
void initialise_control(control &ctrl, const uint32_t& offset_AI);
void overflow(const int& result, const int& val1, const int& val2);

std::string decode_instructionRIJ(const uint32_t& instruction);
std::string execute_R_type(const instructionR& Rtype, int32_t REG[32]);
std::string execute_I_type(const instructionI& Itype, int32_t REG[32], control &ctrl);
std::string execute_J_type(const instructionJ& Jtype, control &ctrl);


void execute_DIVU(const instructionR& Rtype, int32_t REG[32]);
void execute_ADD(const instructionR& Rtype, int32_t REG[32]);
void execute_ADDU(const instructionR& Rtype, int32_t REG[32]);
void execute_AND(const instructionR& Rtype, int32_t REG[32]);

void execute_ADDI(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_ADDIU(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_ANDI(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BEQ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BGEZ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BGEZAL(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BGTZ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BLEZ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BLTZ(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BLTZAL(const instructionI& Itype, int32_t REG[32], control &ctrl);
void execute_BNE(const instructionI& Itype, int32_t REG[32], control &ctrl);


#endif //_DECODE_INSTRUCTION