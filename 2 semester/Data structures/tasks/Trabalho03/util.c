#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "util.h"

// MENUS 

void cabecalho () {
    system("cls");
    printf("\t*************************************\n\t*            BANCO  UFSM            *\n\t*************************************\n");
}

int menu_p() {
    int op;
    cabecalho ();
    printf("\n 1 - RELATORIOS");
    printf("\n 2 - OPERACOES");
    printf("\n 3 - SAIR\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op != 1 && op != 2 && op != 3){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

int menu_relatorios(){
    int op;
    cabecalho ();
    printf("\n--> RELATORIOS\n");
    printf("\n 1 - Lista com o nome dos clientes e suas agencias");
    printf("\n 2 - Lista com o nome dos clientes que estao no negativo");
    printf("\n 3 - Lista com todos os saques efetuados em certo mes");
    printf("\n 4 - Lista com o saldo das contas que nao estao no negativo");
    printf("\n 5 - Lista com todas as contas de certo cliente");
    printf("\n 6 - Voltar\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

int menu_op(){
    int op;
    cabecalho ();
    printf("\n--> OPERACOES\n");
    printf("\n 1 - Operacoes com clientes");
    printf("\n 2 - Operacoes com contas");
    printf("\n 3 - Operacoes com transacoes");
    printf("\n 4 - Voltar\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op != 1 && op != 2 && op != 3 && op != 4){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

int menu_opCliente(){
    int op;
    cabecalho ();
    printf("\n--> OPERACOES COM CLIENTES\n");
    printf("\n 1 - Cadastrar cliente");
    printf("\n 2 - Excluir cliente");
    printf("\n 3 - Listar clientes");
    printf("\n 4 - Voltar\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op != 1 && op != 2 && op != 3 && op != 4){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

int menu_opConta(){
    int op;
    cabecalho ();
    printf("\n--> OPERACOES COM CONTAS\n");
    printf("\n 1 - Cadastrar conta");
    printf("\n 2 - Excluir conta");
    printf("\n 3 - Listar contas");
    printf("\n 4 - Voltar\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op != 1 && op != 2 && op != 3 && op != 4){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

int menu_opTransacao(){
    int op;
    cabecalho ();
    printf("\n--> OPERACOES COM TRANSACOES\n");
    printf("\n 1 - Cadastrar transacao");
    printf("\n 2 - Listar transacoes");
    printf("\n 3 - Voltar\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op != 1 && op != 2 && op != 3) {
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

int menu_opCadastroTR(){
    int op;
    cabecalho ();
    printf("\n--> CADASTRAR TRANSACAO\n");
    printf("\n 1 - Saque");
    printf("\n 2 - Deposito");
    printf("\n 3 - Transferencia");
    printf("\n 4 - Voltar\n");
    printf("\n--> Digite a opcao desejada: ");
    scanf("%d", &op);
    while(op != 1 && op != 2 && op != 3 && op != 4){
        printf("\n-> Operacao invalida!! Digite novamente: ");
        scanf("%d", &op);
    }
    return op;
}

//PROGRAMA

void init(NoCl** clientes, NoCont** contas, NoTr** transacoes){
    int op, op2, op3, op4;
    do{
        int continuar, num_cont, num_cont2, retiracliente, retiraconta;
        char cpf[20];
        op = menu_p();
        switch(op){
            case 1:
                op2 = menu_relatorios();
                switch(op2){
                    case 1:
                        r1 (clientes, contas);
                        printf("\n\n-> Digite um numero para continuar: ");
                        scanf("%d", &continuar);
                        break;
                    case 2:
                        r2 (contas);
                        printf("\n\n-> Digite um numero para continuar: ");
                        scanf("%d", &continuar);
                        break;
                    case 3:
                        r3 (transacoes);
                        printf("\n\n-> Digite um numero para continuar: ");
                        scanf("%d", &continuar);
                        break;
                    case 4:
                        r4 (contas);
                        printf("\n\n-> Digite um numero para continuar: ");
                        scanf("%d", &continuar);
                        break;
                    case 5:
                        r5 (contas);
                        printf("\n\n-> Digite um numero para continuar: ");
                        scanf("%d", &continuar);
                        break;
                    case 6:
                        break;
                }
                break;
            case 2:
                op2 = menu_op();
                switch(op2){
                    case 1:
                        op3 = menu_opCliente();
                        switch(op3){
                            case 1:
                                if(insere_cliente(clientes) == -1){
                                    printf("Cliente ja existente!\n");
                                }
                                else {
                                    printf("Cliente adicionado com sucesso!\n");
                                }
                                break;
                            case 2:
                                retiracliente = retira_cliente(clientes, *transacoes, contas);
                                if(retiracliente == -1){
                                    printf("\nCliente nao encontrado!\n");
                                }
                                else if(retiracliente == -2) {
                                    printf("Nao foi possivel excluir cliente, pois esta envolvido em uma transacao!\n");
                                }
                                else{
                                    printf("\nCliente removido com sucesso!\n");
                                }
                                printf("\n-> Digite um numero para continuar: ");
                                scanf("%d", &continuar);
                                break;
                            case 3:
                                listar_clientes(clientes);
                                printf("\n\n-> Digite um numero para continuar: ");
                                scanf("%d", &continuar);
                                break;
                            case 4:
                                break;
                        }
                        break;
                    case 2:
                        op3 = menu_opConta();
                        switch(op3){
                            case 1:
                                printf("Digite o CPF do cliente que deseja criar uma conta: ");
                                scanf("%s", cpf);
                                if(busca_cliente(*clientes, cpf) == NULL){
                                    printf("\nNao foi possivel criar a conta, cliente nao encontrado!\n");
                                }
                                else{
                                    if(insere_conta (contas, *clientes, cpf) == -1) {
                                        printf("\nConta com numero ja existente!\n");
                                    }
                                    else {
                                        printf("\nConta criada com sucesso!\n");
                                    }
                                }
                                printf("\n-> Digite um numero para continuar: ");
                                scanf("%d", &continuar);
                                break;
                            case 2:
                                retiraconta = retira_conta(contas, *transacoes);
                                if (retiraconta == -1) {
                                    printf("\nConta nao encontrada!\n");
                                }
                                else if (retiraconta == -2) {
                                    printf("\nConta nao pode ser excluida, pois esta envolvida em uma transacao!\n");
                                }
                                else{
                                    printf("\nConta removida com sucesso!\n");
                                }
                                printf("\n-> Digite um numero para continuar: ");
                                scanf("%d", &continuar);
                                break;
                            case 3:
                                listar_contas(contas);
                                printf("\n\n-> Digite um numero para continuar: ");
                                scanf("%d", &continuar);
                                break;
                            case 4:
                                break;
                        }
                        break;
                    case 3:
                        op3 = menu_opTransacao();
                        switch(op3){
                            case 1:
                                op4 = menu_opCadastroTR();
                                switch (op4) {
                                    case 1:
                                        printf("Digite o numero da conta que voce deseja realizar o saque: ");
                                        scanf("%d", &num_cont);
                                        if(busca_conta(*contas, num_cont) == NULL){
                                            printf("\nNao foi possivel realizar o saque, conta nao encontrada!\n");
                                        }
                                        else{
                                            insere_tr (transacoes, contas, num_cont, op4, 0);
                                        }
                                        printf("\n-> Digite um numero para continuar: ");
                                        scanf("%d", &continuar);
                                        break;
                                    case 2:
                                        printf("Digite o numero da conta que voce deseja realizar o deposito: ");
                                        scanf("%d", &num_cont);
                                        if(busca_conta(*contas, num_cont) == NULL){
                                            printf("\nNao foi possivel realizar o deposito, conta nao encontrada!\n");
                                        }
                                        else{
                                            insere_tr (transacoes, contas, num_cont, op4, 0);
                                        }
                                        printf("\n-> Digite um numero para continuar: ");
                                        scanf("%d", &continuar);
                                        break;
                                    case 3:
                                        printf("Digite o numero da conta origem: ");
                                        scanf("%d", &num_cont);
                                        printf("Digite o numero da conta destino: ");
                                        scanf("%d", &num_cont2);
                                        if(busca_conta(*contas, num_cont) == NULL || busca_conta(*contas, num_cont2) == NULL){
                                            printf("\nNao foi possivel realizar a transferencia, pelo menos uma das contas nao foi encontrada!\n");
                                        }
                                        else{
                                            insere_tr (transacoes, contas, num_cont, op4, num_cont2);
                                        }
                                        printf("\n-> Digite um numero para continuar: ");
                                        scanf("%d", &continuar);
                                        break;
                                    case 4:
                                        break;
                                }
                                break;
                            case 2:
                                listar_transacoes(*transacoes);
                                printf("\nDigite qualquer numero para continuar: ");
                                scanf("%d", &continuar);
                                break;
                        }
                        break;
                }
                break;
            case 3:
                break;
        }
    }while(op != 3);
}
