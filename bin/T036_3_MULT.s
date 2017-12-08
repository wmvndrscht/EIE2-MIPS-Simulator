lui $3, 0xFFFF
ori $3, $3, 0xFFFF
lui $4, 0xFFFF
ori $4, $4, 0xFFFF
mult $3, $4
mfhi $2
mflo $3
or $2, $2, $3
jr $0
#1, check largest -1*-1