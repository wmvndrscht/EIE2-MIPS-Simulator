lui $3, 0xF000 #4026531840 or - 
ori $4, $4, 0x2 #2
mult $3, $4
mflo $2
mfhi $5
and $2,$5,$2
srl $2,$2,29
jr $0
#14, check sign extension in hi		