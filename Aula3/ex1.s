# o registo TRISx serve para converter as portas para entrada(1) ou saida(0) 
# o registo PORTx serve para ler o valor de um porto configurado como entrada
# o registo LATx serve para escrever o valor de um porto configurado como saida
#

# Configurar o bit 0 do porto E (RE0) como entrada,
# o bit 0 do registo TRISE deve ser colocado a 1 (i.e.TRISE0=1);

# Configurar o bit 1do porto E (RE1) como saída, o bit 
# 1 do registo TRISE deve ser colocado a 0 (TRISE1=0).



.data

.text 
.globl main 

main:
    # CONFIGURAR O PORTO RE0 COMO SAIDA E O PORTO RB0 COMO ENTRADA
    # CRIAR UM CICLO INFINITO PARA LER E ESCREVER NOS RESPETIVOS PORTOS 
    lui $t0,SFR_BASE_HI 

    lw $t2,TRISE($t0)
    andi $t2,$t2,0xFFF0
    sw $t2,TRISE($t0)

    lw $t3,TRISB($t0)
    ori $t3,$t3,0x000F
    sw $t3,TRISB($t0)

while:

    lw $t5,PORTB($t0)   
    andi $t5,$t5,0x000F

    #xori $t5,$t5,0xFFFF    # ex2
    xori $t5,$t5,0x0009     # ex3

    lw $t4,LATE($t0)
    andi $t4,$t4,0xFFF0
    or $t4,$t5,$t4
    
    sw $t4,LATE($t0)    

    j while 

    li $v0,1
    jr $ra