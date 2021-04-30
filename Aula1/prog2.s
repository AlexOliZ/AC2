#int main(void) {
#   char c;
#   do{
#   c = getChar();
#   if( c != '\n' )
#       putChar( c );
#   } while( c != '\n' );
#   return 0;
#}
    .equ GET_CHAR,2
    .equ PUT_CHAR,3
    .data
str1: .asciiz "Key Pressed\n"
    .text
    .globl main

main:
    #li $t1,'\n'
    
do:
    li $v0,GET_CHAR
    syscall
if:
    beq $v0,'\n',while
    
    la $a0,str1
    li $v0,PUT_CHAR
    syscall

    bne $v0,'\n',do
while:

    li $v0,0
    jr $ra 
