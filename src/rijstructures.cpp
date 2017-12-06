#include <cstdint>
#include "rijstructures.hpp"

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
	Itype.rd = (data << 11) >> 27;
	Itype.IMM = (data & 0xFFFF);
	if(Itype.IMM & 0x8000){
		Itype.IMMs = (0xFFFF0000 | Itype.IMM);
	}
	else{
		Itype.IMMs =Itype.IMM;
	}
	return;
}

void initialiseJ(const uint32_t& data, instructionJ& Jtype){
	Jtype.data = data;
	Jtype.opcode = data >> 26;
	Jtype.address = data & 0x3FFFFFF;
	return; 
}

