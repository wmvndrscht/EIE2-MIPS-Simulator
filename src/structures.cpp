#include <cstdint>


uint32_t assemble(const uint8_t& ADDR_INSTR[0x1000000], const uint32_t& PC){
	uint32_t instruction = (ADDR_INSTR[PC] << 24 | ADDR_INSTR[PC+1] << 16| ADDR_INSTR[PC+2] << 8| ADDR_INSTR[PC+3]);
	return instruction;
}


struct instructionR{
	uint32_t data;
	uint32_t opcode;
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
	uint32_t rt;
	uint32_t IMM;
};


struct instructionJ{
	uint32_t data;
	uint32_t opcode;
	uint32_t address;
};

void initialiseR(const uint32_t& data, instructionR& Rtype){
	Rtype.data = data;
	Rtype.opcode = data >> 26;
	Rtype.rs = (data << 6) >> 27;
	Rtype.rt = (data << 11) >> 27;
	Rtype.rd = (data & 0xF800) >> 11;
	Rtype.shamt = (data & 0x7C0) >> 6;
	Rtype.funct = data & 0x3F;
	return;
}

void initialiseI(const uint32_t& data, instructionI& Itype){
	Itype.data = data;
	Itype.opcode = data >> 26;
	Itype.rs = (data << 6) >> 27;
	Itype.rt = (data << 11) >> 27;
	Itype.IMM = (data & 0xFFFF);
	return;
}

void initialiseJ(const uint32_t& data, instructionJ& Jtype){
	Jtype.data = data;
	Jtype.opcode = data >> 26;
	Jtype.address = data & 0x3FFFFFF;
	return; 
}