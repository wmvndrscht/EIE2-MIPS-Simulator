lui $3, 0xFFFF
ori $3,$3, 0xFFF9 #$3 = -7
ori $4, $4, 2  #$4 = 2
div $3, $4
mfhi $6 #mod
mflo $7 #r
and $2,$6,$7
add $2, $6, $7
andi $2, $2, 0xF
jr $0
#12