lui $3, 0xFFFF
ori $3,$3, 0xFFF9
lui $4, 0xFFFF
ori $4, $4, 0xFFFE
div $3, $4
mfhi $6 #mod
mflo $7 #r
add $2, $6, $7
jr $0
#2