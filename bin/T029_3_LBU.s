lui $3, 0x2000
lui $5, 0x1FFF
ori $5, 0xFFFF
sb $4, 0($3)
lbu $4, 0($5)
jr $0
#245