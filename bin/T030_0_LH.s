lui $3, 0x2000 

ori $4, $4, 0x4
ori $5, $5, 0x4

sb $4, 0($3)
sb $5, 1($3)

lh $1, 0($3)
srl $6, $1, 8
and $2, $1, $5
srl $2, $2, 2
jr $0
# 1, ensures both bytes are loaded in