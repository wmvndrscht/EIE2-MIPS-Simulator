j h1

h2:
addi $2, $2, 0x11
jr $0

h1:
addi $2, $2, -1
blez $2, h2 

addi $2, $2, 4
ori $2, $2, 8
jr $0
#16