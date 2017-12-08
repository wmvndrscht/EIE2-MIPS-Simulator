lui $3, 0xFFFF
ori $3,$3,0xFFFF
lui $4, 0xFFFF
ori $4, $4, 0xFFFF
divu $3, $4
mfhi $6 
mflo $7
sub $2, $7, $6
jr $0
#1