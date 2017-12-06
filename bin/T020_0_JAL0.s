.set noreoder
.set noat
addi $2, $0, 1 
addi $2, $2, 1 
jal here
add $3, $3, $5
xori $3, $3, 4
here:
add $2, $2, $31
jr $0
# 14