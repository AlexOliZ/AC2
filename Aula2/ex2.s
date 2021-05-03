.data 

.equ RESET_CORE_TIMER,12
.equ READ_CORE_TIMER,11
.equ    PUT_CHAR,3 
.equ PRINT_INT,6    

.text 
.globl main 

main:
    subu $sp,$sp,8
    sw $ra,0($sp)
    sw $s0,4($sp)
    li $s0,0
while_m:
    bge $s0,20,end_m
    
    li $a0,1000
    jal delay 
    
    # printInt(++counter, 10 | 4 << 16); 
    addiu $s0,$s0,1
    move $a0,$s0
    li $a1,10

    li $v0,PRINT_INT
    syscall

    li $a0,'\r'
    li $v0,PUT_CHAR
    syscall
    
    j while_m
end_m:
    
    lw $ra,0($sp)
    lw $s0,4($sp)
    addiu $sp,$sp,8
    jr $ra 


delay:
for:
    ble $a0,0,end
    sub $a0,$a0,1
    li $v0,RESET_CORE_TIMER
    syscall
while:
    li $v0,READ_CORE_TIMER
    syscall 
    bge $v0,20000,endw
    j while
endw:
    j for
end:
    li $v0,0
    jr $ra 


