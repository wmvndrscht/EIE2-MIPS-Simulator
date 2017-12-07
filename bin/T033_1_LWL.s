lui $3, 0x9546
ori $3, $3, 0x8578
lui $4, 0x2000
ori $4, $4, 0x4
lui $5, 0x2000
ori $5, $5, 0x8
sw $3, 0($4)
lwl $6, 2($4)
lhu $7, ($4)
#sll $7, $7, 16
add $6, $6, $7
#0411fffsub $6, $6, $3
beq $6, $3, good
jr $0

good:
xori $2, $2, 16
jr $0