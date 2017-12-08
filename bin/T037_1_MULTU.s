lui $3, 0xF000
ori $3, $3, 0x4
ori $4, $4, 0x8
multu $3, $4
mfhi $2
mflo $5
or $2,$2,$5
jr $0
#39, checking both hi and lo

