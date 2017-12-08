ori $3,$3, 5
ori $4, $4, 2
divu $3, $4
mfhi $6 
mflo $7
add $2, $6, $7
jr $0
#3