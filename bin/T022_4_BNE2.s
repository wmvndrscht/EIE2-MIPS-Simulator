j h1

h2:
xori $2, $2, 0x11
jr $0

h1:
addi $2, $2, -1
bne $2, $0, h2 

addi $2, $2, 4
ori $2, $2, 8
jr $0
# 0xee