.data

.equ    READ_CORE_TIMER,11        
.equ    RESET_CORE_TIMER,12        
.equ    PUT_CHAR,3        
.equ    PRINT_INT,6      

.text        
.globl  main

main:
    li $t0,0
while:
    # li $v0,PRINT_INT
    li $v0,READ_CORE_TIMER
    syscall 
    blt $v0, 200000,while

    # resetCoreTimer();
    li $v0,RESET_CORE_TIMER
    syscall

    # printInt(++counter, 10 | 4 << 16); 
    addiu  $t0,$t0,1
    move $a0,$t0

    # (0 | 4 << 16)
    li $t1,10
    li $t2,4
    
    sll $t2,$t2,16
    or $a1,$t1,$t2
    li $v0,PRINT_INT
    syscall

    li $a0,'\r'
    li $v0,PUT_CHAR
    syscall
    j while
endw:
    li $v0,0
    jr $ra 

