j h1

h2:
addi $2, $2, 0x9
jr $0

h1:
addi $2, $2, -1
bgez $2, h2 

addi $2, $2, 4
xori $2, $2, 8
jr $0
#11