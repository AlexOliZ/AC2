.data

.text 
.globl main 

main:
    # CONFIGURAR O PORTO RE0 COMO SAIDA E O PORTO RB0 COMO ENTRADA
    # CRIAR UM CICLO INFINITO PARA LER E ESCREVER NOS RESPETIVOS PORTOS 
    lui $t0,SFR_BASE_HI 

    li $t1,0

    lw $t2,TRISE($t0)
    andi $t2,$t2,0xFFF0
    sw $t2,TRISE($t0)

    lw $t3,TRISB($t0)
    ori $t3,$t3,0x000F
    sw $t3,TRISB($t0)

while:

    lw $t5,PORTB($t0)   
    andi $t5,$t5,0x000F

    lw $t4,LATE($t0)
    andi $t4,$t4,0xFFF0
    or $t4,$t5,$t4
    
    sw $t4,LATE($t0)    

    j while 

    li $v0,1
    jr $ra