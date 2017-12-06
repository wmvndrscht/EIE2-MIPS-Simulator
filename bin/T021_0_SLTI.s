ori $3, $3, 34
sub $3, $0, $3
slt $4, $0, $3
slti $5, $3, -1
sltu $6, $3, $3
sltiu $7, $3, -1
sll $5, $5, 1
sll $6, $6, 2
sll $7, $7, 3
add $2, $4, $5
addu $2, $6, $2
addu $2, $2, $7
jr $0
# 10