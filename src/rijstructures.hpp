#ifndef _RIJSTRUCTURES
#define _RIJSTRUCTURES

#include <cstdint>

struct instructionR{
	uint32_t data;		
	uint32_t opcode;	// why not uint8_t ?
	uint32_t rs;
	uint32_t rt;
	uint32_t rd;
	uint32_t shamt;
	uint32_t funct;
};

struct instructionI{
	uint32_t data;
	uint32_t opcode;	
	uint32_t rs;
	uint32_t rd;
	uint32_t IMM;		// uint16_t ?
	int32_t IMMs;
};

struct instructionJ{
	uint32_t data;
	uint32_t opcode;
	uint32_t address;
};

void initialiseR(const uint32_t& data, instructionR& Rtype);
void initialiseI(const uint32_t& data, instructionI& Itype);
void initialiseJ(const uint32_t& data, instructionJ& Jtype);

#endif //RIJ_STRUCTURES
