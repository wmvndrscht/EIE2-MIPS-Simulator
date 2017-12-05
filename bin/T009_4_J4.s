.set noreorder
.set noat

j h1
sll $0, $0, 0

h2:
ori $2, $2, 2
j h3
sll $0, $0, 0

h1:
addi $2, $2, 1
j h2
sll $0, $0, 0

h3:
addi $2, $2, 4
ori $2, $2, 8
jr $0
# 15