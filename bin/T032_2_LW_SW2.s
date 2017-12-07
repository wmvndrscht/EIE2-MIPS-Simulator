lui $3, 0x2000
ori $3, $3, 0x4
lui $5, 0x2000
ori $5, $5, 0x8
lui $4, 10
ori $4, $4, 49
sw $4, 0xFFFC($3)
lw $2, 0XFFF8($5)
jr $0
# 49