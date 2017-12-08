lui $3, 0xffff 
ori $3,$3, 0xfffb #-5
ori $4, $4, 2 
div $3, $4
mfhi $6 #1...shouldn't be -1
mflo $7 #-2
add $2, $6, $7 #-1+(-2)
#srl $2, $2, 28
jr $0
#253