# inkey = 0 ligar led0 RE0
# inkey = 1 ligar led1 RE1
# inkey = 2 ligar led2 RE2
# inkey = 3 ligar led3 RE3
# else -> ligar led4 RE4 2 segundos (2000ms)

.data 
.equ inkey,1
.text 
.globl main




main:
    addiu $sp,$sp,-16
    sw $ra,0($sp)
    sw $s0,4($sp)
    sw $s1,8($sp)
    sw $s2,12($sp)
while:


    

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
