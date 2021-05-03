.data
.text
.globl main 

main:
    lui $t0,SFR_BASE_HI
    # configurar o porto TRISE0 como saida
    lw $t1,TRISE($t0)
    andi $t1,$t1,0xFFFE
    sw $t1,TRISE($t0)
    # configurar o porto TRISB0 como entrada 
    lw $t1,TRISB($t0)
    ori $t1,$t1,0x0001
    sw $t1,TRISB($t0)

while:
    # ler informação
    lw $t1,PORTB($t0)
    lw $t2,LATE($t0)
    # extrarir bit0
    andi $t1,$t1,0x0001
    andi $t2,$t2,0xFFFE
    # passar informação para o 
    or $t1,$t1,$t2
    # guardar no porto de saida
    sw $t1,LATE($t0)

    j while 
    jr $ra 