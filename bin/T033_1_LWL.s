lui $3, 0x9546
ori $3, $3, 0x1122
lui $4, 0x3344
ori $4, 0x5473
lui $5, 0x2000
ori $5, $5, 0x8
#lui $6, 0x7896
#ori $6, $6, 0xabcd
#lui $7, 0xfefe
#ori $7, $7, 0xdddd
sw $3, 0($5)
sw $4, 4($5)
lwl $6, 2($5)
lwr $7, 5($5)
#sll $7, $7, 16
add $6, $6, $7
#0411fffsub $6, $6, $3
lui $8, 0x1122
ori $8, $8, 0x3344
beq $6, $8, good
jr $0

good:
xori $2, $2, 16
jr $0
