lui $3, 0xFFFF
ori $3, $3, 0xFFFF
lui $4, 0xFFFF
ori $4, $4, 0xFFFF
multu $3, $4
mfhi $2
andi $2, $2, 0xF
jr $0
#0xE, check hi