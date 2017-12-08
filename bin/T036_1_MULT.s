lui $3, 0xFFFF
ori $3, $3, 0xFFFE #-2
lui $4, 0xFFFF 
ori $4, $4, 0xFFF0 #-16
mult $3, $4
mflo $2
mfhi $5
add $2, $2, $5
jr $0
#32, check signed -2*-16 = 32
