lui $3, 0xFFFF
ori $3, $3, 0xFFFF
lui $4, 0xFFFF
ori $4, $4, 0xFFFF
multu $3, $4
mflo $2
jr $0
#1, check lo