lui $3, 0x8000                                                             
lui $4, 0x1                                                                
srl $4, $4, 0x10                                                           
addu $2, $3, $4                                                             
jr $0                                                                      
#expected 0xff   