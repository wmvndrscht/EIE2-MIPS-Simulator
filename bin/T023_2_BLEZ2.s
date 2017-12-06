j h1

h2:
xori $2, $2, 0x11
jr $0

h1:
addiu $2, $2, 1
blez $2, h2 

addi $2, $2, 8
andi $2, $2, 9
jr $0
#9 
