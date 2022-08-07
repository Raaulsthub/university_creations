####################################
## TRADUZINDO O SEGUINTE CODIGO : ##
####################################

#int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
#int i, j, k;
#int acc = 0;

#int main(void) {
#	i = 1;
#	j = 2;
#	k = 4;
#	for (i = 1; i < 10; i++) {
#		a[i] = a[i - 1] + 19;
#	}
#	for (i = 0; i < 10; i++) {
#		for (j = i;  j < 10; j++) {
#			acc = acc + a[j];
#		}
#	}
#	a[6] = acc;
#	while (a[k] < acc) { 
#		a[k] = a[k] + 10;
#	}
#	do {
#		a[7] = a[k] + 1;
#	} while (a[7] < a[8]);
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
	# $s5 = acc
	# $s7 = 1
	# MEUS ENDEREÇOS
	# $t0 -> i
	# $t1 -> j
	# $t2 -> k
	# $t3 -> vetA[0]
	# $t5 -> acc
	
	la    $t0, variavel_I 	 			# $t0 <- endereco de i
	la    $t1, variavel_J    			# $t1 <- endereco de j
	la    $t2, variavel_K    			# #t2 <- endereco de k
	la    $t3, vetA		 			# $t3 <- endereco de vetA[0]
	la    $t5, acc					# $t4 <- endereco de acc
	addi  $s7, $zero, 1      			# $s7 = 1, usarei nos ifs
	
	#acc = 0
	add    $s5 , $zero, $zero			# $s4 <- 0, acc = 0
	sw     $s5, 0($t5)				# atualizamos o valor da variavel na memoria
	
	# i = 1
        addi   $s0, $zero, 1				# $s0 <- 1, i = 1
        sw     $s0, 0($t0)   	 			# atualizamos o valor da variavel na memoria
        
        # j = 2
        addi   $s1, $zero, 2				# $s1 <- 1, j = 1
        sw     $s1, 0($t1)   	 			# atualizamos o valor da variavel na memoria

	# k = 4
        addi   $s2, $zero, 4				# $s0 <- 4, k = 1
        sw     $s2, 0($t2)   	 			# atualizamos o valor da variavel na memoria

#	for (i = 1; i < 10; i++) {
#		a[i] = a[i - 1] + 19;
#	}
inicio_for:        
        #for (i = 1; i < 10; i++)
inicializacao_laco_for: 
	addi   $s0, $zero, 1				# $s0 <- 1, i = 1
	sw     $s0, 0($t0)   	 			# atualizamos o valor da variavel na memoria
        j     verifica_condicao_for			# salto incondicional para a verificacao do laco for    
        
codigo_for_condicao_verdadeira:
        #a[i] = a[i - 1] + 19;
        # 1. a[i - 1] + 19
        sll    $s4, $s0, 2				# multiplico i por 4 bits e guardo em $s4
        subi   $s4, $s4, 4				# subtraio 1 posição (i - 1)	
        add    $s4, $s4, $t3				# $s4 = vetA + (i - 1), tem o endereço efetivo de a[i - 1]
        lw     $s3, 0($s4)				# $s3 = a[i - 1]
        addi   $s3, $s3, 19				# $s3 = a[i - 1] - 19
        # 2. a[i] = a[i - 1] + 19;
        addi   $s4, $s4, 4				# $s4 guarda endereço de a[i]
        sw     $s3, 0($s4)				# guardo $s3 no endereço de memoria guardado em s4
        
        # laco for - incremento
        # i++
        addi  $s0, $s0, 1   				# incrementamos o valor de i
        sw    $s0, 0($t0)   				# atualiza o valor de i na memoria
        
          
verifica_condicao_for:
	# verifica se a condicao do laco for eh verdadeira  
	# i < 10
        slti   $s4, $s0, 10 				# $t4 <- 1 se i < 10
        bne    $s4, $zero, codigo_for_condicao_verdadeira  # desvio para condicao verdadeira se i < 10 ($s4 = 1)
        
#-----------------------------------------------------------------------------------------------------------------------------------------------------#       
#-----------------------------------------------------------------------------------------------------------------------------------------------------#

#	for (i = 0; i < 10; i++) {
#		for (j = i;  j < 10; j++) {
#			acc = acc + a[j];
#		}
#	}

inicio_for_2:        
        #for (i = 0; i < 10; i++)
inicializacao_laco_for_2: 
	add    $s0, $zero, $zero			# $s0 <- 1, i = 0
	sw     $s0, 0($t0)   	 			# atualizamos o valor da variavel na memoria
        j     verifica_condicao_for_2			# salto incondicional para a verificacao do laco for    	 
        
codigo_for_condicao_verdadeira_2:
inicio_for_3:        
        #for (j = i; j < 10; j++)
inicializacao_laco_for_3: 
	add    $s1, $s0, $zero				# j = i
        sw     $s1, 0($t1)    				# atualizamos o valor da variavel na memoria
        j     verifica_condicao_for_3			# salto incondicional para a verificacao do laco for  
        
codigo_for_condicao_verdadeira_3:
        #acc = acc + a[j];
        sll    $s3, $s1, 2 				# multiplico j por 4 bits e guardo em $s3
	add    $s4, $t3, $s3				# calculo endereço efetivo de a[j] e guardo em $s4
	lw     $s3, 0($s4)				# carrego valor de a[j] para $s3
        add    $s5, $s5, $s3				# acc = acc + a[j]
        sw     $s5, 0($t5)
        
        # laco for 3 - incremento
        # j++
        addi  $s1, $s1, 1   				# incrementamos o valor de j
        sw    $s1, 0($t1)   				# atualiza o valor de j na memoria
        
          
verifica_condicao_for_3: 
	# verifica se a condicao do laco for eh verdadeira  
	# j < 10
        slti   $s4, $s1, 10 				# $t4 <- 1 se j < 10
        bne    $s4, $zero, codigo_for_condicao_verdadeira_3  # desvio para condicao verdadeira se i < 10 ($s4 = 1)        
        
	# laco for 2 - incremento
        # i++
        addi  $s0, $s0, 1   				# incrementamos o valor de i
        sw    $s0, 0($t0)   				# atualiza o valor de i na memoria
          
verifica_condicao_for_2:
	# verifica se a condicao do laco for eh verdadeira 
	# i < 10
        slti   $s4, $s0, 10 				# $t4 <- 1 se i < 10
        bne    $s4, $zero, codigo_for_condicao_verdadeira_2  # desvio para condicao verdadeira se i < 10 ($s4 = 1)
        
  	#a[6] = acc
  	sw     $s5, 24($t3) 				#guardo o valor de acc em a[6]
#-----------------------------------------------------------------------------------------------------------------------------------------------------#       
#-----------------------------------------------------------------------------------------------------------------------------------------------------#        
                    
#	while (a[k] < acc) { 
#		a[k] = a[k] + 10;
#	}
                
inicio_while:        
       j    testa_condicao 			       # verificamos se a condicao do laco eh verdadeira
instrucoes_laco_while:          		       # instrucoes caso a condicao seja verdadeira
       # a[k] = a[k] + 10;
       sll   $s4, $s2, 2 	  	 	       # multiplico k por 4 bits e guardo em $s4
       add   $s4, $s4, $t3			       # somo $s4 com a base do vetor a para descobrir o endereco de a[k] e guardo esse em $s4	
       lw    $s3, 0($s4)			       # carrego valor de a[k] em $s3
       addi  $s3, $s3, 10			       # $s3 <- a[k] + 10
       sw    $s3, 0($s4)			       # guardo o resultado final na memoria em a[k]
       	
testa_condicao:                  		       # testamos se a condicao do laco while eh verdadeira
      # while (a[k] < acc)
      sll    $s4, $s2, 2			       # multiplico k por 4 bits e guardo em $s4
      add    $s4, $s4, $t3			       # somo $s4 com a base do vetor a para descobrir o endereco de a[k] e guardo esse em $s4	
      lw     $s3, 0($s4)			       # carrego valor de a[k] para $s3
      slt    $s4, $s3, $s5			       # se a[k] for menor que acc, $s4 recebe 1, caso contrario, recebe 0
      beq    $s4, 1, instrucoes_laco_while	       # se $s4 for 1, realizamos as instrucoes do laco while novamente	
fim_while:

#-----------------------------------------------------------------------------------------------------------------------------------------------------#       
#-----------------------------------------------------------------------------------------------------------------------------------------------------#   

#	do {
#		a[7] = a[k] + 1;
#	} while (a[7] < a[8]);        

laco_do_while:                 

            sll    $s4, $s2, 2			       # multiplico k por 4 bits e guardo em $s4
     	    add    $s4, $s4, $t3		       # somo $s4 com a base do vetor a para descobrir o endereco de a[k] e guardo esse em $s4	
      	    lw     $s3, 0($s4)			       # carrego valor de a[k] para $s3
      	    addi   $s4, $s3, 1			       # $s4 <- a[k] + 1	
      	    sw     $s4, 28($t3)	  		       # guardo valor de s4 em a[7]
            
verifica_condicao_do_while:  
	    # while (a[7] < a[8])          
            lw     $s3, 28($t3)
            lw     $s4, 32($t3)
            slt    $s6, $s3, $s4
            beq	   $s6, 1, laco_do_while
fim_do_while:            
#-----------------------------------------------------------------------------------------------------------------------------------------------------#       
#-----------------------------------------------------------------------------------------------------------------------------------------------------#   
	   # return 0;         			     // termina o programa retornando 0
           addi  $v0, $zero, 17 		     # servico 17 do sistema - exit2
           addi  $a0, $zero, 0 			     # o valor de retorno do programa Ã© zero
           syscall             			     # chamamos o servico 17 do sistema com o valor 0
.data
variavel_I: .word 0				# variavel i
variavel_J: .word 0				# variavel j
variavel_K: .word 0				# variavel k
acc:	    .word 0				# variavel acc
vetA: 	    .word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9  # vetor de interiros com valores iniciais 1, 2, 3 ... 9
