lui $1, 0x2000
ori $1, $1, 0x4
lui $2, 0x2000
ori $2, $2, 0x8
lui $4, 10
ori $4, $4, 49
sw $4, 0xFFFC($1)
lw $2, 0XFFF8($2)
jr $0
# 49