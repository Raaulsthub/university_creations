#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "fila.h"
#include "pilha.h"

#define SIM 1

static void cabecalho () {
    system("cls");
    printf("\t*************************************\n\t*            BANCO  UFSM            *\n\t*************************************\n");
}

static int menu_layout () {
    int op;
    cabecalho ();
    printf("\n 1 - CHEGADA DE PESSOA");
    printf("\n 2 - ATENDIMENTO A PESSOA");
    printf("\n 3 - PROCESSAMENTO DE DOCUMENTO");
    printf("\n 4 - IMPRESSAO DAS FILAS E DA PILHA");
    printf("\n 5 - SAIR\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op != 1 && op != 2 && op != 3 && op != 4 && op != 5){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

static int op1 ()
{
    int op;
    printf("\n A pessoa precisa de acesso prioritario? ");
    printf("\n   1 - SIM");
    printf("\n   2 - NAO");
    printf("\n--> ");
    scanf("%d", &op);
    while(op != 1 && op != 2){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

static int op2 ()
{
    int op;
    printf("\n Deseja gerar documento? ");
    printf("\n   1 - SIM");
    printf("\n   2 - NAO");
    printf("\n--> ");
    scanf("%d", &op);
    while(op != 1 && op != 2){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

void menu (Fila** lstPri, Fila** lst, Pilha** pilha) {
    int op;
    char var;
    Person *p;
    Doc *d;
    do{
        op = menu_layout ();
        switch (op) {
        case 1:
            cabecalho ();
            p = create_person();
            if (op1() == SIM)
                fila_insere(*lstPri, p);
            else
                fila_insere(*lst, p);
            break;
        case 2:
            cabecalho ();
            if (!fila_vazia (*lstPri)) {
                p = fila_retira (*lstPri);
                pessoa_imprime (p);
                pessoa_libera (p);
            } else if (!fila_vazia (*lst)) {
                p = fila_retira (*lst);
                pessoa_imprime (p);
                pessoa_libera (p);
            } else {
                printf("\n-> Operacao invalida!!! Filas Vazias!!! ");
                printf("\n Digite um caractere para continuar: ");
                scanf(" %c", &var);
                break;
            }
            d = create_doc();
            if (op2() != SIM) {
                doc_libera (d);
            }
            else {
                pilha_push (*pilha, d);
            } 
            break;
        case 3:
            cabecalho ();
            if (pilha_vazia (*pilha))
            {
                printf("\n-> Operacao invalida!!! Pilha Vazia!!! ");
            } else {
                d = pilha_pop (*pilha);
                doc_imprime (d);
                doc_libera (d);
            }
            printf("\n Digite um caractere para continuar: ");
            scanf(" %c", &var);
            break;
        case 4:
            cabecalho ();
            printf("\nFila Prioritaria:\n");
            if (fila_vazia (*lstPri))
                printf("\nFila Vazia!\n");
            else 
                fila_imprime (*lstPri);
            printf("\n-------------------------\nFila nao prioritaria:\n");
            if (fila_vazia (*lst))
                printf("\nFila Vazia!\n");
            else 
                fila_imprime (*lst);
            printf("\n-------------------------\nPilha de documentos:\n");
            if (pilha_vazia (*pilha))
                printf("\nPilha Vazia!\n");
            else 
                pilha_imprime (*pilha);
            printf("\n Digite um caractere para continuar: ");
            scanf(" %c", &var);
            break;
        case 5:
            break;
        }
    } while(op != 5);
}