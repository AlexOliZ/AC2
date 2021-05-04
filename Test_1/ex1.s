# inkey = 0 ligar led0 RE0
# inkey = 1 ligar led1 RE1
# inkey = 2 ligar led2 RE2
# inkey = 3 ligar led3 RE3
# else -> ligar led4 RE4 2 segundos (2000ms)

.data 
.equ inkey,1
.equ    READ_CORE_TIMER,11        
.equ    RESET_CORE_TIMER,12   
.text 
.globl main


main:
    addiu $sp,$sp,-16
    sw $ra,0($sp)
    sw $s0,4($sp)
    sw $s1,8($sp)
    sw $s2,12($sp)
    lui $s0,SFR_BASE_HI

    lw $s1,TRISE($s0)
    andi $s1,$s1,0xFFE0
    sw $s1,TRISE($s0)

while:
    li $v0,inkey
    syscall
    move $s2,$v0
    andi $s2,$s2,0x0F

case_0:
    bne $s2,0,case_1
    lw $t0,LATE($s0)
    li $t0,0x01
    sw $t0,LATE($s0)
    j end_case
case_1:
    bne $s2,1,case_2
    lw $t0,LATE($s0)
    li $t0,0x02
    sw $t0,LATE($s0)
    j end_case
case_2:
    bne $s2,2,case_3
    lw $t0,LATE($s0)
    li $t0,0x04
    sw $t0,LATE($s0)
    j end_case
case_3:
    bne $s2,3,default
    lw $t0,LATE($s0)
    li $t0,0x08
    sw $t0,LATE($s0)
    j end_case
default:
    lw $t0,LATE($s0)
    li $t0,0x10
    sw $t0,LATE($s0)
    li $a0,2000
    jal delay
end_case:
    j while
end:    
    lw $ra,0($sp)
    lw $s0,4($sp)
    lw $s1,8($sp)
    lw $s2,12($sp)
    addiu $sp,$sp,16
    jr $ra 

delay:

for:
    ble $a0,0,end_f
    li $v0,RESET_CORE_TIMER
    syscall
while_d:    
    li $v0,READ_CORE_TIMER
    syscall
    blt $v0,20000,while_d
    addiu $a0,$a0,-1
    j for
end_f:
    li $v0,0
    jr $ra
