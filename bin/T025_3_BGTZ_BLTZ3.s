slti $4, -1
bltz $4, go2
bgtz $4, go1
bltz $4, go2
xori $2, $2, 10 
jr $0

go1:
ori $2, $2, 9
jr $0

go2:
addi $2, $2, 8
jr $0
#9