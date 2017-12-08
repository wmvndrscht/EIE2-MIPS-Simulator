ori $3,$3, 7  #$3 = 7
lui $4, 0xFFFF
ori $4, $4, 0xFFFE  #4 = -2
div $3, $4
mfhi $6 #mod = -3
mflo $7 #r = 1
add $2, $6, $7
andi $2, $2, 0xF
jr $0
#14