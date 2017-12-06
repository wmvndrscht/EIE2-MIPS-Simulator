lui $3, 0x2000
ori $3, $3, 0x4
lui $5, 0x2000
ori $5, $5, 0x8
ori $4, $4, 96
sb $4, 0xFFFC($3)
lb $2, 0XFFF8($5)
jr $0
# 96