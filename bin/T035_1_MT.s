lui $3, 0x1234
ori $3, $3, 0x5678
lui $4, 0x9abc
xori $4, 0xdef0

mthi $3
mtlo $4
mfhi $5
mflo $6

beq $3, $5, b1
jr $0

b1:
beq $4, $6, b2
jr $0

b2:
addi $2, $2, 10
jr $0
#10
