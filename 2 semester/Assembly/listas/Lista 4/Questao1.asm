#################################
##PROGRAMA EM C A SER TRADUZIDO##
#################################

#include <stdio.h>

#const int dimensao = 10;

#int soma_sequencia;

#void gera_sequencia_fibonacci (int *f, int dim)
#{
#	int *ptr;
#	f[0] = 0;
#	f[1] = 1;
#	
#	for (ptr = &f[2]; ptr < &f[dim]; ptr++)
#	{
#		*ptr = *(ptr - 1) + *(ptr - 2);
#	}
#}
#
#int *calcula_soma_elementos (int f[], int dim)
#{
#	int i;
#	soma_sequencia = 0;
#	
#	for (i = 0; i < dim; i++) 
#	{
#		soma_sequencia = soma_sequencia + f[i];
#	}
#	return &soma_sequencia;
#	
#}

#void imprime_soma(int *ptr)
#{
#	printf("A soma dos elementos de fib e %d\n", *ptr);
#}

#int main (void) 
#{
#	int fib[dimensao];
#	int *ponteiro_soma_sequencia;
#	
#	gera_sequencia_fibonacci(fib, dimensao);
#	ponteiro_soma_sequencia = calcula_soma_elementos (fib, dimensao);
#	imprime_soma (ponteiro_soma_sequencia);
#	return 0;
#}

.text
	 
.globl main

##################
#MAIN
##################

# Mapa da Pilha
#
# ----------	
# *ponteiro soma sequencia		$sp + 40
# fib					$sp + 0		
# ----------
#             
#int main (void)                           
main:
#--------|
#PROLOGO |
#--------|
	
        addi  $sp, $sp, -44				# reserva na pilha um espaço ptr e vetor
        sw    $ra, 0($sp)  				# armazena na pilha o endereço de retorno
        lw    $t0, dimensao				# guarda em $t0 o valor da dimensao do vetor fib
	sll   $t0, $t0, 2				# multiplica $t0 por 4, pois fib eh um vetor de inteiros
	sub   $sp, $sp, $t0				# reserva na pilha espaco para o vetor fib


        
#-----------------------|
# CORPO DO PROCEDIMENTO |
#-----------------------| 
	#int fib[dimensao];
	la    $t0, 4($sp)				# carrego o endereco do vetor em $t0
	#int *ponteiro_soma_sequencia;
	la    $t1, 44($sp)				# carrego o endereco do ponteiro em $t1
	
	#gera_sequencia_fibonacci(fib, dimensao);
        move  $a0, $t0 					# carrego valor parametro (endereco do vetor) em $a0
        lw    $a1, dimensao				# carrego valor parametro (dimensao) em $a1 
	jal   gera_sequencia_fibonacci			# desvio incondicional para o procedimento
	
	#ponteiro_soma_sequencia = calcula_soma_elementos (fib, dimensao);
	move  $a0, $t0 					# carrego valor parametro (endereco do vetor) em $a0
	lw    $a1, dimensao				# carrego valor parametro (dimensao) em $a1 
	jal   calcula_soma_elementos			# desvio incondicional para o procedimento
	sw    $v0, 0($t1)				# guardo $v0 no endereco guardado pelo poneteiro
	
	#imprime_soma (ponteiro_soma_sequencia);
	move  $a0, $v0					# carrego valor parametro (ponteiro_soma_sequencia) em $a0
	jal   imprime_soma				# desvio incondicional para o procedimento
#-------------------|
# FINAL DA FUNCAO   |
#-------------------|       
        li    $v0, 17      			        # servico 17: termina o programa
        syscall             		     	        # fazemos a chamada ao serviço 17.
##################
# GERA_SEQUENCIA_FIBONACCI
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
# ra		$sp
# ----------
# 

#void gera_sequencia_fibonacci (int *f, int dim)
gera_sequencia_fibonacci:  
#--------|
#PROLOGO |
#--------|
 	addi 	$sp, $sp, -24				# reserva na pilha espa�o
 	sw   	$s0, 4($sp)				# guardo valor de $s0
 	sw   	$s1, 8($sp)				# guardo valor de $s1
 	sw   	$s2, 12($sp)				# guardo valor de $s2
 	sw	$s3, 16($sp)				# guardo valor de $s3
 	sw	$s4, 20($sp)				# guardo valor de $s4
 	sw   	$ra, 0($sp)				# guardo na memoria o endereco de retorno
#-----------------------|
# CORPO DO PROCEDIMENTO |
#-----------------------|
	#int *ptr;
	move  	$s0, $zero				#$s0 guarda ptr
	#f[0] = 0;
	add	$s2, $zero, $zero			# $s2 = 0
	sw      $s2, 0($a0)				# f[0] = 0
	#f[1] = 1;
	addi	$s2, $zero, 1				# $s2 = 1
	sw	$s2, 4($a0)				# f[1] = 1
	
#	for (ptr = &f[2]; ptr < &f[dim]; ptr++)
#	{
#		*ptr = *(ptr - 1) + *(ptr - 2);
#	}
#}
inicializacao_laco_for_1:            
        la    $s0, 8($a0)     						# $s0 (ptr) armazena o endereco de fib[2]
        sw    $s0, 4($sp)  						# guardo valor do ptr na memoria
        sll   $a1, $a1, 2						# em $a1 multiplico o tamanho do vetor por 4 bits (eh um vetor de inteiros)
        add   $a0, $a0, $a1						# a0 recebe o endereco de fib[dimensao]
        j     verifica_condicao_for_1 					# salto incondicional para a verificacao do laco for
               
codigo_for_condicao_verdadeira_1:
        #*ptr = *(ptr - 1) + *(ptr - 2);
        lw     $s3, -4($s0)
        lw     $s4, -8($s0)
        add    $s3, $s3, $s4
        sw     $s3, 0($s0)     
        # ptr++
        addi   $s0, $s0, 4						# aumento o ponteiro em uma posicao (4 bits)
verifica_condicao_for_1:
        # ptr < &f[dim]
        slt    $s2, $s0, $a0						# seta $s2 para 1 se o endereco do ponteiro for menor que o endereco do ultimo espaco do vetor fib
        bne    $s2, $zero, codigo_for_condicao_verdadeira_1 		# se $s2 for diferente de 0, pula para o codigo da condicao verdadeira

codigo_for_condicao_falsa_1:            
fim_for:
	
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
        addi $sp, $sp, 24   				# restauramos a pilha
        jr   $ra            				# retorna ao procedimento chamador
        
##################
# CALCULA_SOMA_ELEMENTOS
##################
# Mapa da Pilha
#
# ----------
# $s4		$sp + 24
# $s3		$sp + 20
# $s2		$sp + 16
# $s1		$sp + 12
# $s0		$sp + 8	
# i		$sp + 4
# ra		$sp
# ----------
# 

#int *calcula_soma_elementos (int f[], int dim)
calcula_soma_elementos:  
#--------|
#PROLOGO |
#--------|
 	addi 	$sp, $sp, -24				# reserva na pilha espa�o
 	sw   	$s0, 4($sp)				# guardo valor de $s0
 	sw   	$s1, 8($sp)				# guardo valor de $s1
 	sw   	$s2, 12($sp)				# guardo valor de $s2
 	sw	$s3, 16($sp)				# guardo valor de $s3
 	sw	$s4, 20($sp)				# guardo valor de $s4
 	sw   	$ra, 0($sp)				# guardo na memoria o endereco de retorno
#-----------------------|
# CORPO DO PROCEDIMENTO |
#-----------------------|
	#int i;
	move  	$s0, $zero				#$s0 guarda i
	sw      $s0, 4($sp)				# guardo o valor de i na memoria
	#soma_sequencia = 0;
	la      $s1, soma_sequencia			#$s1 guarda o endereco de soma sequencia
	sw      $zero, 0($s1)				#guardo o valor zero na variavel global
	
#	for (i = 0; i < dim; i++) 
#	{
#		soma_sequencia = soma_sequencia + f[i];
#	}
#	return &soma_sequencia;
inicializacao_laco_for_2:            

        j     verifica_condicao_for_2 					# salto incondicional para a verificacao do laco for
               
codigo_for_condicao_verdadeira_2:
        #soma_sequencia = soma_sequencia + f[i];
        sll    $s3, $s0, 2 						# i * 4 bits guardado em $s3
        add    $s4, $s3, $a0						# $s4 guarda endereco de f[i]
        lw     $s3, 0($s4)						# $s3 guarda o valor de f[i]
        lw     $s2, 0($s1)						# guardo o valor de soma_sequencia em $s2
        add    $s2, $s2,  $s3						# $s2 -> soma_sequencia = soma_sequencia + f[i];
        sw     $s2, 0($s1)						# guardo o valor na memoria de soma_sequencia
        # i++
        addi   $s0, $s0, 1						# aumento a variavel i
verifica_condicao_for_2:
        #i < dim
        slt    $s2, $s0, $a1						# seta $s2 para 1 se o endereco do ponteiro for menor que dim
        bne    $s2, $zero, codigo_for_condicao_verdadeira_2 		# se $s2 for diferente de 0, pula para o codigo da condicao verdadeira

codigo_for_condicao_falsa_2:            
fim_for_2:
	
#-------------------|
# FINAL DA FUNCAO   |
#-------------------| 
# return
	move $v0, $s1					# guardo na variavel de retorno um ponteiro para a variavel soma_sequencia
	move $a0, $zero					# zero parametro 1
	move $a1, $zero					# zero parametro 2  				
        lw   $ra, 0($sp)				# leio vetor de retorno
        lw   $s0, 4($sp)				# leio valor original de $s0
        lw   $s1, 8($sp)				# leio valor original de $s1
        lw   $s2, 12($sp)				# leio valor original de $s2
        lw   $s3, 16($sp)				# leio valor original de $s3
        lw   $s4, 20($sp)				# leio valor original de $s4
        addi $sp, $sp, 24   				# restauramos a pilha
        jr   $ra            				# retorna ao procedimento chamador
       
imprime_soma:

        # prologo
	sub $sp, $sp, 8		# ajusta a pilha para guradar dois itens
	sw  $ra, 4($sp)		# guarda na pilha o endereço de retorno
	sw  $a0, 0($sp)		# guarda na pilha o argumento $a0 
	
	#corpo
	la  $a0, evento1		#carrego string a ser printada para argumento do syscall			
	li  $v0, 4			# serviço para imprimir uma string
	syscall				# executa uma chamada ao sistema
	lw  $a0, 0($sp)			# carrego novamente o valor do ponteiro
	
	 
	lw  $a0, 0($a0)			#carrego string a ser printada para argumento do syscall			
	li  $v0, 1			# serviço para imprimir um inteiro
	syscall				# executa uma chamada ao sistema
	lw  $a0, 0($sp)			# carrego novamente o valor do ponteiro
	
	li  $a0, '\n'			#carrego string a ser printada para argumento do syscall			
	li  $v0, 11			# serviço para imprimir uma string
	syscall				# executa uma chamada ao sistema
	lw  $a0, 0($sp)			# carrego novamente o valor do 
	
	# epilogo	
	lw 	$ra, 4($sp)		# restaura o endereço de retorno
	lw 	$a0, 0($sp)		# restaura o argumento $a0 do procedimento
	add     $sp, $sp, 8		# elimina dois itens (palavras) da pilha
	jr 	$ra			# retorna a funçao chamadora      
        

.data
dimensao:  	.word 10
soma_sequencia: .word 0 
evento1: 	.asciiz "A soma dos elementos de fib e \0"
