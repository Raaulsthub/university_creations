#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"

struct cliente
{
    char* nome;
    char* cpf;
    char* telefone;
};

struct noCl
{
    Cliente cliente;
    NoCl *ant;
    NoCl *prox;
};

struct conta {
    int numero_conta;
    NoCl* cl;
    int numero_ag;
    int criacao;
    double saldo;
    double valor_limite;
};

struct noCont {
    Conta conta;
    NoCont* ant;
    NoCont* prox;
};

struct transacao {
    int codigo;
    NoCont* conta_origem;
    NoCont* conta_destino;
    int tipo;                   //1- saque, 2- deposito, 3-transferência.
    int data;
    float valor;
};

struct noTr {
    Transacao transacao;
    NoTr* ant;
    NoTr* prox;
};

void lst_cria_cliente (NoCl** inicio){    
    (*inicio) = NULL;
}

Cliente cadastro_cliente(){
    Cliente c;
    char nome[100], tel[20];
    printf("Digite o nome do cliente: ");
    getchar();
    scanf("%[^\n]", nome);
    c.nome = (char*) malloc (strlen(nome) + 1);
    strcpy(c.nome, nome);
    printf("Digite o telefone do cliente: ");
    scanf("%s", tel);
    c.telefone = (char*) malloc (strlen(tel) + 1);
    strcpy(c.telefone, tel);
    return c;
}

int insere_cliente(NoCl **inicio){
    char cpf[20];
    printf("Digite o cpf do cliente: ");
    scanf("%s", cpf);
    if(busca_cliente(*inicio, cpf) != NULL){
        return -1;
    }
    NoCl *novo = (NoCl*) malloc (sizeof(NoCl));
    novo->ant = NULL;
    novo->prox = *inicio;
    novo->cliente = cadastro_cliente();
    novo->cliente.cpf = (char*) malloc (strlen(cpf) + 1);
    strcpy(novo->cliente.cpf, cpf);
    if(*inicio != NULL)
        (*inicio)->ant = novo;
    *inicio = novo;
}

NoCl* busca_cliente(NoCl* inicio, char* cpf){
    NoCl* p = inicio;
    while(p != NULL) {
        if (strcmp(p->cliente.cpf, cpf) == 0)
            return p;
        p = p->prox;
    }
    return p;
}

int varrer_cpf(NoTr* tr, char* cpf){
    NoTr* p = tr;
    while(p != NULL) {
        if(p->transacao.conta_destino != NULL && strcmp(p->transacao.conta_destino->conta.cl->cliente.cpf, cpf) == 0){
            return -1;
        }
        else if(p->transacao.conta_origem != NULL && strcmp(p->transacao.conta_origem->conta.cl->cliente.cpf, cpf) == 0){
            return -1;
        }
        p = p->prox;
    }
}

int retira_cliente(NoCl** inicio, NoTr* tr, NoCont** cont){
    char cpf[20];
    printf("Digite o cpf do cliente: ");
    scanf("%s", cpf);
    NoCl* tirar = busca_cliente(*inicio, cpf);
    if(tirar == NULL){
        return -1;
    }
    if(varrer_cpf(tr, cpf) == -1) {
        return -2;
    }
    NoCont* p = *cont;
    while(p != NULL) {
        if(strcmp(p->conta.cl->cliente.cpf, cpf) == 0){
            printf("\nConta de numero %d teve de ser excluida por pertencer ao cliente.\n", p->conta.numero_conta);
            if(p == *cont){
                *cont = p->prox;
            }
            else{
                p->ant->prox = p->prox;
            }
            if(p->prox != NULL){
                p->prox->ant = p->ant;
            }
            free(p);
        }
        p = p->prox;
    }
    if(tirar == *inicio){
        *inicio = tirar->prox;
    }
    else{
        tirar->ant->prox = tirar->prox;
    }
    if(tirar->prox != NULL){
        tirar->prox->ant = tirar->ant;
    }
    free(tirar->cliente.nome);
    free(tirar->cliente.cpf);
    free(tirar->cliente.telefone);
    free(tirar);
    return 1;
}

void listar_clientes(NoCl** inicio){
    NoCl* p = *inicio;
    int i = 0;
    while(p != NULL){
        printf("\nCLIENTE %d\n", i);
        printf("\nNome do cliente: %s", p->cliente.nome);
        printf("\nCPF do cliente: %s", p->cliente.cpf);
        printf("\nTelefone do cliente: %s\n", p->cliente.telefone);
        p = p->prox;
        i++;
    }
}

void lst_cria_conta (NoCont** inicio) {    
    (*inicio) = NULL;
}

Conta cadastro_conta (NoCl *inicio, char* cpf) {
    Conta c;
    c.cl = busca_cliente(inicio, cpf);
    printf("Digite o numero da agencia: ");
    scanf("%d", &c.numero_ag);
    printf("Digite a data de criacao da conta (DDMMAAAA): ");
    scanf("%d", &c.criacao);
    printf("Digite o saldo inicial da conta: ");
    scanf("%lf", &c.saldo);
    printf("Digite o valor limite da conta: ");
    scanf("%lf", &c.valor_limite);
    while (c.valor_limite < c.saldo) {
        printf("Uma conta não pode ter saldo maior que valor limite! Terao de ser digitados novamente o saldo e o limite.\n");
        printf("Digite o saldo novamente: ");
        scanf("%lf", &c.saldo);
        printf("Digite o limite da conta: ");
        scanf("%lf", &c.valor_limite);
    }
    return c;
}

NoCont* busca_conta (NoCont* inicio, int num) {
    NoCont* p = inicio;
    while(p != NULL) {
        if (p->conta.numero_conta == num)
            return p;
        p = p->prox;
    }
    return p;
}

int insere_conta (NoCont **inicio, NoCl *client, char* cpf) {
    int num;
    printf("Digite o numero da conta: ");
    scanf("%d", &num);
    if(busca_conta(*inicio, num) != NULL) {
        return -1;
    }
    NoCont *novo = (NoCont*) malloc (sizeof(NoCont));
    novo->ant = NULL;
    novo->prox = *inicio;
    novo->conta = cadastro_conta(client, cpf);
    novo->conta.numero_conta = num;
    if(*inicio != NULL)
        (*inicio)->ant = novo;
    *inicio = novo;
}

int varrer_numConta(NoTr* tr, int num) {
    NoTr* p = tr;
    while (p != NULL) {
        if(p->transacao.conta_destino != NULL && p->transacao.conta_destino->conta.numero_conta == num) {
            return -1;
        }
        else if(p->transacao.conta_origem != NULL && p->transacao.conta_origem->conta.numero_conta == num) {
            return -1;
        }
        p = p -> prox;
    }
}

int retira_conta (NoCont** inicio, NoTr* tr) {
    int num;
    printf("Digite o numero da conta: ");
    scanf("%d", &num);
    NoCont* tirar = busca_conta(*inicio, num);
    if(tirar == NULL){
        return -1;
    }
    if (varrer_numConta(tr, num) == -1) {
        return -2;
    }
    if(tirar == *inicio){
        *inicio = tirar->prox;
    }
    else{
        tirar->ant->prox = tirar->prox;
    }
    if(tirar->prox != NULL){
        tirar->prox->ant = tirar->ant;
    }
    free(tirar);
    return 1;
}

void listar_contas (NoCont** inicio) {
    NoCont* p = *inicio;
    int i = 0;
    while(p != NULL) {
        printf("\nCONTA %d\n", i);
        printf("\nNumero da conta: %d", p->conta.numero_conta);
        printf("\nNumero da agencia: %d", p->conta.numero_ag);
        printf("\nNome do cliente dono da conta: %s", p->conta.cl->cliente.nome);
        printf("\nCPF do cliente dono da conta: %s", p->conta.cl->cliente.cpf);
        printf("\nData de criacao da conta: %d", p->conta.criacao);
        printf("\nSaldo atual da conta: R$ %.2f", p->conta.saldo);
        printf("\nValor limite da conta: R$ %.2f\n", p->conta.valor_limite);
        p = p->prox;
        i++;
    }
}

void r1 (NoCl** client, NoCont** conta) {
    NoCl* c = *client;
    NoCont* p;
    int i = 0;
    while(c != NULL) {
        int cont = 0;
        p = *conta;
        printf("\nCLIENTE %d\n", i);
        printf("\nNome do cliente: %s", c->cliente.nome);
        while(p != NULL) {
            if (strcmp (p->conta.cl->cliente.nome, c->cliente.nome) == 0) {
                printf("\n-> Possui conta na agencia: %d\n", p->conta.numero_ag);
                cont++;
            }
            p = p->prox;
        }
        if (cont == 0)
            printf("\n-> Nao possui conta em nenhuma agencia\n");
        c = c->prox;
        i++;
    }
}

void r2 (NoCont** inicio) {
    NoCont* p = *inicio;
    int i = 0;
    while(p != NULL) {
        if (p->conta.saldo < 0.0) {
            printf("\nCliente negativo %d\n", i);
            printf("\nNome do cliente: %s", p->conta.cl->cliente.nome);
            printf("\nSaldo atual da conta: R$ %.2f\n", p->conta.saldo);
            i++;
        }
        p = p->prox;
    }
}

void r3 (NoTr** inicio) {
    NoTr* t = *inicio;
    int i = 0, data;
    printf("\nDigite o mes e o ano que deseja consultar os saques (MMAAAA): ");
    scanf("%d", &data);
    while(t != NULL) {
        if ((t->transacao.data % 1000000) == data && t->transacao.tipo == 1) {
            printf("\nSaque %d\n", i);
            printf("\nConta: %d", t->transacao.conta_origem->conta.numero_conta);
            printf("\nData (DD/MM/AAAA): %d", t->transacao.data);
            printf("\nValor: R$ %.2f\n", t->transacao.valor);
            i++;
        }
        t = t->prox;
    }
    if (i == 0)
        printf("\nSem saques no periodo informado\n");
}

void r4 (NoCont** inicio) {
    NoCont* p = *inicio;
    int i = 0;
    while(p != NULL) {
        if (p->conta.saldo >= 0.0) {
            printf("\nConta fora do negativo %d\n", i);
            printf("\nNumero da conta: %d", p->conta.numero_conta);
            printf("\nNome do cliente: %s", p->conta.cl->cliente.nome);
            printf("\nSaldo atual da conta: R$ %.2f\n", p->conta.saldo);
            i++;
        }
        p = p->prox;
    }
}

void r5 (NoCont** inicio) {
    NoCont* c = *inicio;
    int i = 0;
    char nome[20];
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", nome);
    while(c != NULL) {
        if (strcmp(nome, c->conta.cl->cliente.nome) == 0) {
            printf("\nConta %d\n", i);
            printf("\nNumero da conta: %d", c->conta.numero_conta);
            printf("\nAgencia: %d", c->conta.numero_ag);
            printf("\nSaldo em conta: R$ %.2f\n", c->conta.saldo);
            i++;
        }
        c = c->prox;
    }
    if (i == 0)
        printf("\nCliente sem contas ou nao encontrado\n");
}

void cria_tr (NoTr** inicio) {    
    (*inicio) = NULL;
}

Transacao cadastro_saque (NoCont** inicio, int num, int tipo) {
    Transacao t;
    t.tipo = tipo;
    t.conta_origem = busca_conta (*inicio, num);
    t.conta_destino = NULL;
    printf("Digite o codigo da transacao: ");
    scanf("%d", &t.codigo);
    printf("Digite a data da transacao (DDMMAAAA): ");
    scanf("%d", &t.data);
    printf("Digite o valor que deseja sacar: ");
    scanf("%f", &t.valor);
    if((*inicio)->conta.saldo - t.valor < 0.0 - ((*inicio)->conta.valor_limite)) {
        printf("\nNao foi possivel realizar a saque, conta origem nao possui saldo suficiente!\n");
        t.tipo = -1;
    }
    else {
        (*inicio)->conta.saldo -= t.valor;
    } 
    return t;
}

Transacao cadastro_deposito (NoCont** inicio, int num, int tipo) {
    Transacao t;
    t.tipo = tipo;
    t.conta_origem = NULL;
    t.conta_destino = busca_conta (*inicio, num);
    printf("Digite o codigo da transacao: ");
    scanf("%d", &t.codigo);
    printf("Digite a data da transacao (DDMMAAAA): ");
    scanf("%d", &t.data);
    printf("Digite o valor que deseja depositar: ");
    scanf("%f", &t.valor);
    if ((*inicio)->conta.saldo + t.valor <= (*inicio)->conta.valor_limite) {
        (*inicio)->conta.saldo += t.valor; 
    } else {
        printf("\nNao foi possivel realizar o deposito, saldo em conta iria ultrapassar o limite!\n");
        t.tipo = -1;
    }   
    return t;
}

Transacao cadastro_transferencia(NoCont** inicio, int num, int num2, int tipo) {
    Transacao t;
    t.tipo = tipo;
    t.conta_origem = busca_conta(*inicio, num);
    t.conta_destino = busca_conta(*inicio, num2);
    printf("Digite o codigo da transacao: ");
    scanf("%d", &t.codigo);
    printf("Digite a data da transacao (DDMMAAAA): ");
    scanf("%d", &t.data);
    printf("Digite o valor que deseja transferir: ");
    scanf("%f", &t.valor);
    if (t.conta_destino->conta.saldo + t.valor > t.conta_destino->conta.valor_limite) {
        printf("\nNao foi possivel realizar a transferencia, conta destino ultrapassaria seu saldo limite!\n");
        t.tipo = -1;
    }
    else if(t.conta_origem->conta.saldo - t.valor < 0.0 - t.conta_origem->conta.valor_limite) {
        printf("\nNao foi possivel realizar a transferencia, conta origem nao possui saldo suficiente!\n");
        t.tipo = -1;
    }
    else {
        t.conta_origem->conta.saldo -= t.valor;
        t.conta_destino->conta.saldo += t.valor;
    }
    return t;
}

void insere_tr (NoTr** inicio, NoCont** cont, int num, int tipo, int num2) {          
    NoTr* novo = (NoTr*) malloc (sizeof (NoTr));
    novo->prox = *inicio;
    novo->ant = NULL;
    switch (tipo) {
        case 1:
            novo->transacao = cadastro_saque (cont, num, tipo);
            break;
        case 2:
            novo->transacao = cadastro_deposito (cont, num, tipo);
            break;
        case 3:
            novo->transacao = cadastro_transferencia (cont, num, num2, tipo);
            break;
    }
    if (novo->transacao.tipo == -1) {
        free(novo);
        return;
    } else {
        printf("\nOperacao efetuada com sucesso!\n");
    }
    
    if (*inicio != NULL)
        (*inicio)->ant = novo;
    *inicio = novo;
}


NoTr* busca_tr (NoTr* inicio, int cod) {
    NoTr* p = inicio;
    while(p != NULL) {
        if (p->transacao.codigo == cod)
            return p;
        p = p->prox;
    }
    return NULL;	
}

void retira_tr (NoTr** inicio, int cod) {          
    NoTr* p = busca_tr(*inicio, cod);
    if (p == NULL)
        return ;                             
    if (*inicio == p)		
        *inicio = p->prox;
    else
        p->ant->prox = p->prox;
    if (p->prox != NULL)
        p->prox->ant = p->ant;
    free(p);
}

void listar_transacoes(NoTr* inicio) {
    NoTr* p = inicio;
    int i = 1;
    while(p != NULL) {
        printf("\n\nTRANSACAO %d", i);
        printf("\nCodigo: %d", p->transacao.codigo);
        if(p->transacao.conta_origem != NULL)
            printf("\nConta origem: %d", p->transacao.conta_origem->conta.numero_conta);
        if(p->transacao.conta_destino != NULL)            
            printf("\nConta destino: %d", p->transacao.conta_destino->conta.numero_conta);
        switch(p->transacao.tipo) {
            case 1:
                printf("\nTipo: Saque");
                break;
            case 2:
                printf("\nTipo: Deposito");
                break;
            case 3:
                printf("\nTipo: Transferencia");
                break;
        }
        printf("\nData (DD/MM/AAAA): %d", p->transacao.data);
        printf("\nValor: %.2f", p->transacao.valor);
        p = p->prox;
        i++;
    } 
}

void final_free_cl(NoCl* cl) {
    NoCl* p;
    while(cl != NULL) {
        p = cl->prox;
        free(cl->cliente.cpf);
        free(cl->cliente.nome);
        free(cl->cliente.telefone);
        free(cl);
        cl = p;
    }
}

void final_free_cont(NoCont* c) {
    NoCont* p;
    while(c != NULL){
        p = c->prox;
        free(c);
        c = p;
    }
}

void final_free_tr(NoTr* tr) {
    NoTr* p;
    while(tr != NULL) {
        p = tr->prox;
        free(tr);
        tr = p;
    }
}
