lui $3, 0x1
srl $3, $3, 0x10
lui $4, 0xf
srl $4, $4, 0x10
addu $2, $3, $4
jr $0
#expected 0x10