xori $3, $3, 59
ori $4, $4, 10
divu $3, $4
nop
mflo $2
mfhi $1
add $2, $2, $1
jalr $0
#14