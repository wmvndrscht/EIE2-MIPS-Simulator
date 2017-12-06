
j h1

ori $2, $2, 2
jr $0

h1:
addi $2, $2, 1
slt $3, $0, $2
bne $2, $3, -24 

addi $2, $2, 4
ori $2, $2, 8
jr $0
# 3