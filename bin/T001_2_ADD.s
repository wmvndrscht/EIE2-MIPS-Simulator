#lui $3, 0x4000
lui $3, 0xFFFF
lui $4, 0x1
srl $4, $4, 0x10                                                                                                                          
add $2, $3, $4                                                             
jr $0                                                                      
#expected 1