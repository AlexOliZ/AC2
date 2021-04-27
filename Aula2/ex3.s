.data

.equ    cnt1,20000000
.equ    cnt5,4000000
.equ    cnt10,2000000
.equ    READ_CORE_TIMER,11        
.equ    RESET_CORE_TIMER,12   
.equ    PUT_CHAR,3        
.equ    PRINT_INT,6      
.equ K, 20000     

.text        
.globl  main

# var que conta de 0 a 10 para o cnt1
# e dá print quando var == 10
# var que conta de 0 a 1 para o cnt5
# e dá print quando var == 1
# e freq do delay == 10hz


main:
    subu $sp, $sp, 8	               
    sw $ra, 0($sp)                    
    sw $s0, 4($sp)                    
    li $t0,0    # val print de 10hz
    li $t1,0    # val if de 1hz
    li $t2,0    # val if de 5hz
    li $t3,10   # aux print
    li $t4,4    # aux print
    li $t5,0    # val print de 1hz
    li $t6,0    # val print de 5hz

while:

    # li $v0,PRINT_INT
    li $a0,1
    jal delay

    li $v0,READ_CORE_TIMER
    syscall 
    blt $v0, 200000,while

    # print 10hz
    # ...
    
    # printInt(++counter, 10 | 4 << 16); 
    addiu  $t0,$t0,1
    move $a0,$t0
    
    sll $t4,$t4,16
    or $a1,$t3,$t4
    li $v0,PRINT_INT
    syscall

    li $a0,'\r'
    li $v0,PUT_CHAR
    syscall

if5:
    bne $t2,1,e5
    # print 5hz
    # ...

    # printInt(++counter, 10 | 4 << 16); 
    addiu  $t6,$t6,1
    move $a0,$t0

    # (0 | 4 << 16)
    sll $t4,$t4,16
    or $a1,$t3,$t4
    li $v0,PRINT_INT
    syscall

    li $a0,'\r'
    li $v0,PUT_CHAR
    syscall
    li $t2,0
    j end5
e5:
    addiu $t2,$t2,1
end5:

if1:
    bne $t1,10,e1
    # print 1hz
    # ...

    addiu  $t5,$t5,1
    move $a0,$t0

    # (0 | 4 << 16)
    sll $t4,$t4,16
    or $a1,$t3,$t4
    li $v0,PRINT_INT
    syscall

    li $a0,'\r'
    li $v0,PUT_CHAR
    syscall
    li $t1,0
    j end1
e1:
    addiu $t1,$t1,1
end1:
    
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