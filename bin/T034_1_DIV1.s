ori $3,$3, 5
ori $4, $4, 2
div $3, $4
mfhi $6 
mflo $7
add $2, $6, $7
jr $0
#3 simple div, 5/2 -> 2r1