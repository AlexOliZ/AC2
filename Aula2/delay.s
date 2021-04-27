.data

.equ    READ_CORE_TIMER,11        
.equ    RESET_CORE_TIMER,12   
.equ    PUT_CHAR,3        
.equ    PRINT_INT,6 
.equ K, 20000     

.text        
.globl  main

main:
    subu $sp, $sp, 8	               
    sw $ra, 0($sp)                    
    sw $s0, 4($sp)      

    li $t1,10
    li $t2,4
    
while:
    # li $v0,PRINT_INT
    li $a0,1
    jal delay

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
    sll $t2,$t2,16
    or $a1,$t1,$t2
    li $v0,PRINT_INT
    syscall

    li $a0,'\r'
    li $v0,PUT_CHAR
    syscall
    j while

endw:

    lw $ra, 0($sp)		              
    lw $s0, 4($sp)                    
    addiu $sp, $sp, 8 
    jr $ra

delay:
    move $t0,$a0
for:
    ble $t0,0,endf
    li $v0,RESET_CORE_TIMER 
    syscall
w:
    li $v0,READ_CORE_TIMER 
    syscall
    blt $v0,K,w
    subu $t0,$t0,1
    j for 
endf:
    jr $ra 


