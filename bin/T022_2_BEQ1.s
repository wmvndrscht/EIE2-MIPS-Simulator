
j h1

h2:
ori $2, $2, 2
jr $0

h1:
addi $2, $2, 1
slt $3, $0, $2
beq $2, $3, h2 

addi $2, $2, 4
ori $2, $2, 7
jr $0
# 3