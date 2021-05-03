# parte 2
.data 
.equ    READ_CORE_TIMER,11        
.equ    RESET_CORE_TIMER,12        
.text 
.globl main

main:
    addiu $sp,$sp,-4
    sw $ra,0($sp)
w:
    jal johnson_counter
    j w 

    lw $ra,0($sp)
    addiu $sp,$sp,4
    jr $ra

johnson_counter:
    addiu $sp,$sp,-16
    sw $ra,0($sp)
    sw $s0,4($sp)
    sw $s1,8($sp)
    sw $s2,12($sp)

    li $s2,0
    lui $s0,SFR_BASE_HI 
    
    lw $s1,TRISE($s0)
    andi $s1,$s1,0xFFF0
    sw $s1,TRISE($s0)

w2:

    not  $t1, $s3
    andi $t1, $t1, 0x0008      # keeps NOT(bit 3)
    srl  $t1, $t1, 3           # bit 3 becomes bit 0

    sll  $s3, $s3, 1
	or   $s3, $s3, $t1

    lw $t1, LATE($s0)          #   $t1 <- LATE
    andi $t1, $t1, 0xFFF0      #   $t1 <- $t1 & 0xFFF0
    or   $t1, $t1, $s3         #   $t1 <- $t1 | counter
    sw $t1, LATE($s0)          #   LATE <- $t1

    li $a0, 500
    jal delay
    j w2
    
    lw $ra,0($sp)
    lw $ra,4($sp)
    lw $ra,8($sp)
    lw $ra,12($sp)
    addiu $sp,$sp,16


simple_counter:
    addiu $sp,$sp,-16
    sw $ra,0($sp)
    sw $s0,4($sp)
    sw $s1,8($sp)
    sw $s2,12($sp)

    li $s2,0
    lui $s0,SFR_BASE_HI 
    
    lw $s1,TRISE($s0)
    andi $s1,$s1,0xFFF0
    sw $s1,TRISE($s0)
    
    #lw $t1,TRISB($t0)
    #ori $t1,$t1,0x000F
    #sw $t1,TRISB($t0)
w1:

    lw $t0,LATE($s0)
    andi $t0,0xFFF0
    andi $t0,0x000F
    or $t0,$t0,$s2
    sw $t0,LATE($s0)

    # delay 2hz -> 0.5s
    li $a0,500
    jal delay
    addiu $s2,$s2,1
    j w1

    lw $ra,0($sp)
    lw $ra,4($sp)
    lw $ra,8($sp)
    lw $ra,12($sp)
    addiu $sp,$sp,16
    jr $ra 


switch:
    lui $t0,SFR_BASE_HI 
    
    lw $t1,TRISE($t0)
    andi $t1,$t1,0xFFF0
    sw $t1,TRISE($t0)
    
    lw $t1,TRISB($t0)
    ori $t1,$t1,0x000F
    sw $t1,TRISB($t0)

while:
    # input
    lw $t1,PORTB($t0)
    # output
    lw $t2,LATE($t0)
    # extrair bits 0 a 3
    andi $t1,$t1,0x000F
    andi $t2,$t2,0xFFF0
    or $t1,$t1,$t2

    sw $t1,LATE($t0)

    j while 
    jr $ra

delay:

for: ble $a0,0,endf 
    li $v0,RESET_CORE_TIMER
    syscall 
while_d:
    li $v0,READ_CORE_TIMER
    syscall
    blt $v0,20000,while_d

    sub $a0,$a0,1
    j for 
endf:
    jr $ra 