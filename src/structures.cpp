#include <cstdint>

struct instructionR{
	uint32_t data;
	uint32_t opcode;
	uint32_t rs;
	uint32_t rt;
	uint32_t rd;
	uint32_t shamt;
	uint32_t funct;

}

struct instructionI{
	uint32_t data;
	uint32_t opcode;
	uint32_t rs;
	uint32_t rt;
	uint32_t IMM;
}


struct instructionJ{
	uint32_t data;
	uint32_t opcode;
	uint32_t address;
}