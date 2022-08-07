#Escreva uma função F, em assembly para o MIPS. Esta função que tem um argumento x. O argumento e o valor de retorno da função são tipos inteiros de 32
#bits. Esta função deve setar os bits 21, 15 e 7–3, zerar os bits 25 a 22 e inverter os
#bits 28, 27, 13–10. Teste a função: escreva um procedimento main que chama o
#procedimento F com o valor x = 0xA5A5A5A5. Qual o valor de retorno da função
#F?

.text
	 
.globl main

##################
#MAIN
##################

# Mapa da Pilha
#
# ----------	
# ra		$sp + 4
# x		$sp
# ----------
# 
        
main:
#--------|
#PROLOGO |
#--------|

        addi  $sp, $sp, -8  				# reserva na pilha um espaÃ§o para x e endereco de retorno
        sw    $ra, 4($sp)  				# armazena na pilha o endereÃ§o de retorno
        
#-----------------------|
# CORPO DO PROCEDIMENTO |
#-----------------------| 
        li    $a0, 0xA5A5A5A5 				# carrego valor parametro em $a0
	jal   procedimento				#desvio incondicional para o procedimento
	sw    $v0, 0($sp)				#salvo valor na memoria
	la    $t1, var1					#carrego endereco de variavel global para $t0
	sw    $v0, 0($t1)				#carrego valor na var1 global
	
#-------------------|
# FINAL DA FUNCAO   |
#-------------------|       
        li    $v0, 17      			      # serviÃ§o 17: termina o programa
        syscall             		     	      # fazemos a chamada ao serviÃ§o 17.
    

##################
#PROCEDIMENTO
##################

# Mapa da Pilha
#
# ----------	
# ra		$sp + 4
# x		$sp
# ----------
# 
 
procedimento:  
#--------|
#PROLOGO |
#--------|
 	subi $sp, $sp, -8				# reserva na pilha um espaÃ§o para x e endereco de retorno
 	sw   $ra, 4($sp)				# guardo na memoria o endereco de retorno
#-----------------------|
# CORPO DO PROCEDIMENTO |
#-----------------------|

#SETAR BITS
	li   $t0, 0x002080F8				# Carrego mascara para setar os bits 21, 15 e 7–3
	or   $a0, $a0, $t0				# Operacao or bitwise entre mascara e parametro x
	
#ZERAR BITS
	li   $t0, 0xFC3FFFFF				# Carrego mascara 2 para zerar os bits de 22 a 25
	and  $a0, $a0, $t0				# Operacao and bitwise entre mascara 2 e parametro x
	
#INVERTER
	li   $t0, 0x18003C00				# Carrego mascara 3 para inverter bits 10 - 13, 28, 27
	xor  $a0, $a0, $t0				# Operacao nor entre mascara 3 e parametro x
	
	
	move $v0, $a0
#-------------------|
# FINAL DA FUNCAO   |
#-------------------| 
# return  				
        lw   $ra, 4($sp)				# leio vetor de retorno
        addi $sp, $sp, 28   				# restauramos a pilha
        jr   $ra            				# retorna ao procedimento chamador
        

.data

var1:  .word 0
########################################################################
# RESULTADO FINAL : BC2599FD
########################################################################