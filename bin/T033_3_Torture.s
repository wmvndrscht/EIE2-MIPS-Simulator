# first store two numbers in memory
.data				# Begin data segment
var1:	.word 0				# first memory variable
var2:	.word 0				# second memory variable
var3:	.word 0,0			# make sure var3 holds two words
					#   consecutively
	.text				# Begin code segment
	.globl main			# first instr must be global
		
	lui $t0,0x7654			# $t0 = 0x76543210
	ori $t0,0x3210
	la $t1,var1			# $t1 = &var1 (pointer to var1)
	sw $t0,0($t1)			# var1 = $t0
	lui $t2,0x1234			# $t2 = 0x12345678
	ori $t2,0x5678
	la $t3,var2			# $t3 = &var2
	sw $t2,0($t3)			# var2 = $t3
# now retrieve the two numbers and add them
	lw $t4,0($t1)			# $t4 = var1
	lw $t5,0($t3)			# $t5 = var2
	addu $s2,$t4,$t5		# $s2 = $t4 + $t5
	lui $t7,0x8888			# $t7 = 0x88888886
	ori $t7,0x8886
	sub $2,$s2, $t7		#   if correct, set $s2 = 2
	jr $0