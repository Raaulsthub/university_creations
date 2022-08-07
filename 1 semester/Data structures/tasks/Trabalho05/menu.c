#include "menu.h"
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>

static void cabecalho () {
    system("cls");
    printf("\t*************************************\n\t*      SISTEMA DE CURSOS  UFSM      *\n\t*************************************\n");
}

static int menu_layout () {
    int op;
    cabecalho ();
    printf("\n 1 - OPERACOES COM CURSOS");
    printf("\n 2 - OPERACOES COM ALUNOS");
    printf("\n 3 - SAIR\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op < 1 || op > 3){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

static int menu_cursos() {
    int op;
    cabecalho();
    printf("\n 1 - INSERIR CURSO;");
    printf("\n 2 - EXCLUIR CURSO");
    printf("\n 3 - IMPRIMIR TODOS OS CURSOS");
    printf("\n 4 - VOLTAR\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op < 1 || op > 4){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

static int menu_alunos() {
    int op;
    cabecalho();
    printf("\n 1 - INSERCAO DE ALUNO");
    printf("\n 2 - EXCLUSAO DE ALUNO");
    printf("\n 3 - IMPRESSAO DE ALUNOS DE UM CURSO");
    printf("\n 4 - IMPRESSAO DE TODOS OS ALUNOS");
    printf("\n 5 - VOLTAR\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op < 1 || op > 5){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

void init () {
    int op, op1;
    char continuar;
    Arvore* ufsm = arv_cria();
    do {
        op = menu_layout();
        switch(op) {
            case 1:
                op1 = menu_cursos();
                switch(op1) {
                    case 1:
                        cabecalho();
                        printf("OPCAO 1 -> INSERIR CURSO\n");
                        arv_insere_curso(ufsm);
                        printf("\nDigite um caractere para continuar: ");
                        scanf(" %c", &continuar);
                        break;
                    case 2:
                        cabecalho();
                        printf("OPCAO 2 -> EXCLUIR CURSO\n");
                        arv_exclui_curso(ufsm);
                        printf("\nDigite um caractere para continuar: ");
                        scanf(" %c", &continuar);
                        break;
                    case 3:
                        cabecalho();
                        printf("OPCAO 3 -> IMPRIMIR TODOS OS CURSOS\n");
                        imprime_asc(arv_get_raiz(ufsm));
                        printf("\nDigite um caractere para continuar: ");
                        scanf(" %c", &continuar);
                        break;
                    case 4:
                        break;
                }
                break;
            case 2:
                op1 = menu_alunos();
                switch(op1){
                    case 1:
                        cabecalho();
                        printf("OPCAO 1 -> INSERCAO DE ALUNO\n");
                        lst_insere_ordenado(ufsm);
                        printf("\nDigite um caractere para continuar: ");
                        scanf(" %c", &continuar);
                        break;
                    case 2:
                        cabecalho();
                        printf("OPCAO 2 -> EXCLUSAO DE ALUNO\n");
                        lst_retira(ufsm);
                        printf("\nDigite um caractere para continuar: ");
                        scanf(" %c", &continuar);
                        break;
                    case 3:
                        cabecalho();
                        printf("OPCAO 3 -> IMPRESSAO DE ALUNOS DE UM CURSO\n");
                        lst_imprime(ufsm);
                        printf("\nDigite um caractere para continuar: ");
                        scanf(" %c", &continuar);
                        break;
                    case 4:
                        cabecalho();
                        printf("OPCAO 3 -> IMPRESSAO DE TODOS OS ALUNOS\n");
                        arv_imprime_vinc(arv_get_raiz(ufsm));
                        printf("\nDigite um caractere para continuar: ");
                        scanf(" %c", &continuar);
                        break;
                    case 5:
                        break;
                }
                break;
            case 3:
                arv_libera_arvore (ufsm);
                break;
        }
    }while (op != 3);
}