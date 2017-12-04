lui $3, 0xFA  
lui $4, 0x5
srl $4, $4, 0x10
srl $3, $3, 0x10                                                        
add $2, $3, $4                                                             
jr $0                                                                      
#expected 0xff