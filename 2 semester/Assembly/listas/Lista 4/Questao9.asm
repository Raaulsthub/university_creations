#Escreva o algoritmo de Both para a multiplicação, como um procedimento. Escreva
#em assembly para o MIPS. A multiplicação será para números inteiros, com 8 bits,
#em complemento de 2. Usando o simulador MARS, teste o procedimento (escreva
#um programa com o procedimento), fazendo a multiplicação X · Y , com X = 15 e Y
#= ?6.


.text
	 
.globl main

##################
#MAIN
##################

# Mapa da Pilha
#
# ----------	
# y					$sp + 8
# x					$sp + 4
# $ra					$sp + 0		
# ----------
#             
#int main (void)                           
main:
#--------|
#PROLOGO |
#--------|
	
        addi  $sp, $sp, -12				# reserva na pilha um espaco para x, y e $ra
        sw    $ra, 0($sp)  				# armazena na pilha o endereÃ§o de retorno
        
#-----------------------|
# CORPO DO PROCEDIMENTO |
#-----------------------| 
	addi   $t0, $zero, 15				# $t0 armazena valor de x = 15
	sw     $t0, 4($sp)				# armazeno x na memoria
	subi   $t1, $zero, 6				# $t0 armazena valor de y = -6
	sw     $t1, 8($sp)				# armazeno y na memoria
	
	move   $a0, $t0					# guardo valor de x no parametro 1
	move   $a1, $t1					# guardo valor de y no parametro 2
	
	jal    multiplica_both				# desvio incondicional para a função
	
	move $a0, $v0  					# carrego valor produto em $a0
	li  $v0, 1           				# chamo a função de sistema para impressão de inteiro
    	syscall
#-------------------|
# FINAL DA FUNCAO   |
#-------------------|       
        li    $v0, 17      			        # servico 17: termina o programa
        syscall             		     	        # fazemos a chamada ao serviÃ§o 17.
##################
# MULTIPLICA_BOTH
##################
# Mapa da Pilha
#
# ----------
# $s4		$sp + 24
# $s3		$sp + 20
# $s2		$sp + 16
# $s1		$sp + 12
# $s0		$sp + 8	
# *ptr		$sp + 4
# ra		$sp + 0
# ----------
# 

multiplica_both:  
#--------|
#PROLOGO |
#--------|
 	addi 	$sp, $sp, -32				# reserva na pilha espaço
 	sw   	$s0, 4($sp)				# guardo valor de $s0
 	sw   	$s1, 8($sp)				# guardo valor de $s1
 	sw   	$s2, 12($sp)				# guardo valor de $s2
 	sw	$s3, 16($sp)				# guardo valor de $s3
 	sw	$s4, 20($sp)				# guardo valor de $s4
 	sw	$s5, 24($sp)				# guardo valor de $s5
 	sw	$s6, 28($sp)				# guardo valor de $s6
 	sw   	$ra, 0($sp)				# guardo na memoria o endereco de retorno
#-----------------------|
# CORPO DO PROCEDIMENTO |
#-----------------------|
	
	and   $s1, $a1, 0x00FF				#s1 guarda valor produto, com 8 zeros a esquerda e o valor do multiplicador a direita
	and   $s0, $a0, 0x00FF				#s0 guarda o valor do multiplicando
	sll   $s0, $s0, 8				#passo o valor do multiplicando para os msbs da variavel
	add   $s4, $zero, $zero				#s4 guarda BA (bit auxiliar)
	
#	for (i = 0; i < 8; i++)
inicializacao_laco_for_1:            
        add   $s2, $zero, $zero						# $s2 eh o iterador e comeca com o valor zero
        j     verifica_condicao_for_1 					# salto incondicional para a verificacao do laco for
               
codigo_for_condicao_verdadeira_1:
        # COMPARA O ULTIMO BIT DO PRODUTO E BA
        and   $s5, $s1, 0x0001						# $s5 guarda ultimo bit do produto
        
        beq   $s5, $s4, iguais						# se ultimo bit eh igual a B.A, pulo para o rotulo iguais
        slt   $s6, $s5, $s4						# verifico se o bit do produto eh 0 e ba eh 1
        beq   $s6, $zero, subtrair					# se $s6 eh igual a 0, quer dizer que o bit do produto eh 1 e o ba eh 0, entao pulo para subtrair
        j     somar							# se o lsb do produto eh 0 e o ba eh 1 pulo para o rotulo somar
        
iguais:
	j final
subtrair:
        sub   $s1, $s1, $s0    						#subtraio os msbs do produto com o multiplicando
        j final								#desvio incondicional pra final
somar:	
	add   $s1, $s1, $s0        					#somo os msbs do produto com o multiplicando
	j final								#desvio incondicional pra final
final:		
	move  $s4, $s5							# ba ganha o ultimo bit do produto
	sra   $s1, $s1, 1						# shift aritimetico para a direita no produto	
              
        # i++
        addi   $s2, $s2, 1						# incremento i em 1
verifica_condicao_for_1:
        # i < 9
        slti   $s3, $s2, 8						# seta $s2 para 1 se i < 8
        bne    $s3, $zero, codigo_for_condicao_verdadeira_1 		# se $s2 for diferente de 0, pula para o codigo da condicao verdadeira

codigo_for_condicao_falsa_1:            
fim_for:
	move $v0, $s1
#-------------------|
# FINAL DA FUNCAO   |
#-------------------| 
# return
	move $a0, $zero					# zero parametro 1
	move $a1, $zero					# zero parametro 2  				
        lw   $ra, 0($sp)				# leio vetor de retorno
        lw   $s0, 4($sp)				# leio valor original de $s0
        lw   $s1, 8($sp)				# leio valor original de $s1
        lw   $s2, 12($sp)				# leio valor original de $s2
        lw   $s3, 16($sp)				# leio valor original de $s3
        lw   $s4, 20($sp)				# leio valor original de $s4
        lw   $s5, 24($sp)				# leio valor original de $s5
        lw   $s6, 28($sp)				# leio valor original de $s6
        addi $sp, $sp, 32   				# restauramos a pilha
        jr   $ra            				# retorna ao procedimento chamador
