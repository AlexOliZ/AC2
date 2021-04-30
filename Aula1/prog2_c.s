
    .equ inkey,1
    .equ GET_CHAR,2
    .equ PUT_CHAR,3
    .data
str1: .asciiz "Key Pressed\n"
    .text
    .globl main

main:
    
do:
    li $v0,inkey
    syscall
w:  beq $v0,0,w
    syscall
    j w
endw:

if:
    beq $v0,'\n',while
    
    la $a0,str1
    li $v0,PUT_CHAR
    syscall

    bne $v0,'\n',do
while:

    li $v0,0
    jr $ra 