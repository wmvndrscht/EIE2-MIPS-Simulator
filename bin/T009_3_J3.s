.set noreorder
.set noat
addi $3, $3, 1
j hello_there
addu $2, $2, $3
addu $2, $2, $3
addu $2, $2, $3
addu $2, $2, $3
hello_there:
addu $2, $3, $3
jr $0
#2