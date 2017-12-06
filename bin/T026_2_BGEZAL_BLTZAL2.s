addi $4, $4, -1
slt $4, 0
ori $5, $5, 31
sllv $1, $4, $5
srlv $1, $1, $5

BLTZAL $1, go2
BGEZAL $1, go1
BLTZAL $1, go2

go1:
ori $2, $0, 16 
jalr $0

go2:
xori $2, $0, 14
jr $0
#16