lui $3, 0xfcae
ori $3, $3, 0x00dd
lui $4, 0xddfc
ori $4, $4, 0xae00
lui $5, 0x2200
ori $5, $5, 0x4
sw $3, 0($5)
sw $4, 4($5)
#lhu $6, ($5)
lwl $6, 5($5)
#lhu $7, 6($5)
#sll $7, $7, 16
lwr $7, 2($5)
beq $6, $7, good
jr $0

good:
xori $2, $2, 17
jr $0