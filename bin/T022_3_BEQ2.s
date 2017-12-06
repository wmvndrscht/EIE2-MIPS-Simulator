
j h1

h2:
ori $2, $2, 2
jr $0

h1:
addi $2, $2, 1
beq $2, $3, h2 

addi $2, $2, 4
ori $2, $2, 8
jr $0
# 13