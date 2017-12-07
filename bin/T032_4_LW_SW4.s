lui $3, 0x9546
ori $3, $3, 0x4578
lui $4, 0x2000
ori $4, $4, 0x4
lui $5, 0x2000
ori $5, $5, 0x8
sw $3, 0xFFF8($4)
lh $6, 0xFFF8($4)
lhu $7, 0xFFFA($4)
sll $6, $6, 16
add $6, $6, $7
sub $6, $6, $3
blez $6, good
jr $0

good:
xori $2, $2, 17
jr $0
# 17