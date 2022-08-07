####################################
## TRADUZINDO O SEGUINTE CODIGO : ##
####################################

#int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
#int i, j, k;

#int main(void) {
#	i = 1;
#	goto abc;
#	a[4] = 123;
#	a[5] = 900;
#abc:
#	a[0] = i;
#	j = a[0]
#	k = i + 3000;

#	if ( i == j ) {  
#		a[2] = k - a[9];
#	} else {
#		a[2] = a[4]
#	}
#	if (k < i && i < 600) {
#		if (k == 6 || j >= i {
#			a[9] = 400;
#		}else {
#			a[8] = 500;
#		}
#	}
#	switch(a[j * 2 + 1]) {
#	case 1:
#		a[1] = 4000;
#		break;
#	case 3:
#		switch (a[4]) {
#		case 3:
#			a[5] = 50000;
#			break;
#		case 4:
#			a[6] = 50000;
#		case 5:
#			a[7] = 70000;
#			break;
#		}
#		a[3] = 50000;
#		break;
#		}
#	case 5:
#		a[5] = 6000;
#		break;
#	}
#}			

				
#########################			
## CODIGO EM ASSEMBLY: ##
#########################
.text
main:
	# MEUS REGISTRADORES
	# $S0 = i
	# $S1 = j
	# $S2 = k
	# $S3 = temporario principal
	# $s7 = 1
	# MEUS ENDEREÇOS
	# $t0 -> i
	# $t1 -> j
	# $t2 -> k
	# $t3 -> vetA[0]
	
	la    $t0, variavel_I 	 		# $t0 <- endereco de i
	la    $t1, variavel_J    		# $t1 <- endereco de j
	la    $t2, variavel_K    		# #t2 <- endereco de k
	la    $t3, vetA		 		# $t3 <- endereco de vetA[0]
	addi  $s7, $zero, 1      		# $s7 = 1, usarei nos ifs
	
	# i = 1
        addi   $s0, $zero, 1			# $s0 <- 1, i = 1
        sw     $s0, 0($t0)   	 		# atualizamos o valor da variavel na memoria
        
        # goto abc
        j abc			 		# mudo o endereço de leitura para o rotulo abc (desvio incondicional)
        
        # a[4] = 123
 	addi  $s3, $zero, 123	 		# $s3 = 123
 	sw    $s3, 16($t3)	 		# atualizamos o valor de VetA[4] para 123
 	
 	# a[5] = 900
 	addi  $s3, $zero, 900     		# $s3 = 900
 	sw    $s3, 20($t3)        		# atualiazmos o valor de VetA[5] para 900

abc:
 	# a[0] = i
 	sw    $s0, 0($t3) 	  		# guardo valor de i no endereço de memoria $t3 (a[0])
 	
 	# j = a[0]
 	lw    $s1, 0($t3)	  		# $s1 = a[0], j = a[0] 
 	sw    $s1, 0($t1)	  		# guardando valor de j no respectivo endereço
 	
 	# k = i + 3000
 	addi  $s2, $s0, 3000      		# $s2 = i + 3000, k = i + 3000 
 	sw    $s2, 0($t2) 	  		# guardando valor de k no repectivo endereço
 	
 	# if (i == j) -> IF 1
 	beq   $s0, $s1, true_1
 	
false_1:
 	# a[2] = a[4]
 	lw    $s3, 16($t3)       		# $s3 <- a[4]
 	sw    $s3, 8($t3)	 		# guardando na memoria a[2] o valor de $s3 (a[4])
 	j end_if_1
 	
true_1:
	# a[2] = k - a[9]
	lw    $s4, 36($t3)			#s4 <- a[9]
	sub   $s3, $s2, $s4     		#s3 = k - a[9]
	sw    $s3, 8($t3)			# guardando na memoria a[2] o valor final da operação
	
end_if_1:
	# if (k < i && i < 600) -> IF 2
	slt   $s3, $s2, $s0 			# s3 = 1 se k < 1
	bne   $s7, $s3, end_if_2                # se s3 for diferente de 1, acaba o if
	slti  $s3, $s0, 600			# s3 = 1 se i < 600
	bne   $s7, $s3, end_if_2      		# se s3 for diferente de 1, acaba o if
	
true_2:
	#if (k == 6 || j >= 1) -> IF 3
	beq   $s2, 6, true_3			# se k == 6, vai para o caso verdadeiro
	slti  $s3, $s1, 1			# bota 0 no $s3 se s1 for maior ou igual a 1
	bne   $s7, $s3, true_3			# se $s3 == 0, vai para o caso verdadeiro
	
false_3:
	# a[8] = 500
	addi  $s3, $zero, 500			# $s3 = 500
	sw    $s3, 32($t3) 			# guardando o valor 500 no endereço de a[8]
	j end_if_3				# pulhando para o final do if
	
true_3:
	# a[9] = 400;
	addi  $s3, $zero, 400			# $s3 = 400
	sw    $s3, 36($t3)			# guardando o valor 400 no endereço de a[9]
	
end_if_3:	
end_if_2:
	   
	#switch(a[j * 2 + 1])
	
	
	# 1. Carregando a[j * 2 + 1]
	
	add  $s3, $s1, $s1			# j * 2
	addi $s3, $s3, 1			# j * 2 + 1
	sll  $s3, $s3, 2			# multiplico $s3 por 4 (bits)
	add  $s4, $t3, $s3   			# endereco base do vetA + j * 2 + 1
	lw   $s3, 0($s4)			# s4 <- a[j * 2 + 1]
	
	# 2. Switch
	
	# verificamos se a[j * 2 + 1] = 1
	addi  $s4, $zero, 1 			# $s4  <- 1
	beq   $s4, $s3, a_l1 		 	# se a = 1, desvie para l1 (case 1:)
        # verificamos se a[j * 2 + 1] = 3
        addi  $s4, $zero, 3 			# $s4 <- 3
        beq   $s4, $s3, a_l3  			# se a = 3, desvie para l3 (case 3:)
        # verificamos se a[j * 2 + 1] = 5
        addi  $s4, $zero, 5 			# $s4 <- 5
        beq   $s4, $s3, a_l5 			# se a = 5, desvie para l5 (case 5:)
        
        # saimos da estrutura switch
        j     fim_switch			# desvio incondicional para fim_switch
        	
 	
a_l1: 
	# case 1:
	
	# a[1] = 4000;
	addi  $s4, $zero, 4000 			# $s4 = 4000   		
	sw    $s4, 4($t3)			# guardo o valor de s4 em a[1]
	
	# saimos da estrutura switch (break)
	j fim_switch				# desvio incondicional para fim_switch
 	
a_l3: 	
	# case 3:
	
 	#switch (a[4])
 	lw    $s3, 16($t3)			# $s3 = a[4]
 	
 	# verificamos se a = 3
	addi  $s4, $zero, 3 			# $s4  <- 3
	beq   $s4, $s3, b_23 		 	# se a = 3, desvie para 23 (case 3:)
        # verificamos se a = 4
        addi  $s4, $zero, 4 			# $s4 <- 4
        beq   $s4, $s3, b_24  			# se a = 4, desvie para 24 (case 4:)
        # verificamos se a = 5
        addi  $s4, $zero, 5 			# $s4 <- 5
        beq   $s4, $s3, b_25 			# se a = 5, desvie para 25 (case 5:) 
        
        # saimos da estrutura switch (break)
        j     fim_switch_2			# desvio incondicional para fim_switch_2
        

b_23:
	# case 3->3:
	
	# a[5] = 50000; 
	addi  $s3, $zero, 50000			# $s3 = 50000
	sw    $s3, 20($t3)			# guardo o valor de s3 na memoria correspondente a a[5]
	
	# saimos da estrutura switch (break)
	j    fim_switch_2			# desvio incondicional para fim_switch_2

b_24:
	# case 3->4
	
	# a[6] = 50000;
	addi  $s3, $zero, 50000			# $s3 = 50000
	sw    $s3, 24($t3)			# guardo o valor de s3 na memoria correspondente a a[6]
	

b_25:
	# case 3->5
	
	# a[7] = 70000;
	addi  $s3, $zero, 70000			# $s3 = 70000
	sw    $s3, 28($t3)			# guardo o valor de s3 na memoria correspondente a a[7]
	
	# saimos da estrutura switch (break)
	j    fim_switch_2			# desvio incondicional para fim_switch_2
	

fim_switch_2:

	#a[3] = 50000;
	addi  $s3, $zero, 50000			# $s3 = 50000
	sw    $s3, 12($t3)			# guardo o valor de s3 na memoria correspondente a a[3]
	
	# saimos da estrutura switch (break)
	j    fim_switch			# desvio incondicional para fim_switch
	
a_l5:
	# case 5
	
	#a[5] = 6000;
	addi  $s4, $zero, 6000 			# $s4 = 6000   		
	sw    $s4, 20($t3)			# guardo o valor de s4 em a[5]
	
	# saimos da estrutura switch (break)
	j fim_switch				# desvio incondicional para fim_switch


fim_switch: 
	# return 0;         			// termina o programa retornando 0
        addi  $v0, $zero, 17 			# servico 17 do sistema - exit2
        addi  $a0, $zero, 0 			# o valor de retorno do programa Ã© zero
        syscall             			# chamamos o servico 17 do sistema com o valor 0




.data
variavel_I: .word 0				#variavel i
variavel_J: .word 0				#variavel j
variavel_K: .word 0				#variavel k
vetA: 	    .word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9  # Vetor de interiros com valores iniciais 1, 2, 3 ... 9
