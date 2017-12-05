
j h1

h2:
ori $2, $2, 2
j h3

h1:
addi $2, $2, 1
j h2

h3:
addi $2, $2, 4
ori $2, $2, 8
jr $0
# 15