here:
ori $1, $1, 0xffff
xori $2, $2, 16
sllv $1, $1, $2
sra $2, $1, 31
bgez $2, here
lui $3, 0x8000
add $2, $3, $2
jr $0
# 246