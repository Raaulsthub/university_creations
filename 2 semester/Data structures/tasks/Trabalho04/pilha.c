#include "pilha.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct doc {
    char* name;
    char* cpf;
    int cod;
};

typedef struct no
{
    Doc* d;
    struct no *prox;
} No;

struct pilha
{
    No* prim;
};

Doc *create_doc ()
{
    int cod;
    char name[30], cpf[12];
    Doc *d = (Doc *)malloc(sizeof(Doc));
    printf("\n Digite o nome do cliente atendido: ");
    getchar();
    scanf("%[^\n]", name);
    d->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(d->name, name);
    printf("\n Digite o cpf do cliente atendido: ");
    getchar();
    scanf("%[^\n]", cpf);
    d->cpf = (char *)malloc(sizeof(char) * (strlen(cpf) + 1));
    strcpy(d->cpf, cpf);
    printf("\n Codigo identificador para o possivel documento: ");
    scanf("%d", &cod);
    d->cod = cod;
    return d;
}

void doc_imprime(Doc *d)
{
    printf("\n NOME: %s", d->name);
    printf("\n CPF: %s", d->cpf);
    printf("\n CODIGO: %d", d->cod);
}

void pilha_imprime(Pilha *p)
{   
    int cont = 0;
    Pilha* p2 = pilha_cria();
    Doc* d;
    while (!pilha_vazia(p))
    {
        d = pilha_pop(p);
        printf("\n\nDOCUMENTO: %d:\n", cont + 1);
        doc_imprime(d);
        pilha_push(p2, d);
        cont++;
    }
    while (!pilha_vazia(p2)) {
        pilha_push(p, pilha_pop(p2));
    }
    free(p2);
}

Pilha* pilha_cria()
{
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->prim = NULL;
    return p;
}

void pilha_libera(Pilha* p)
{
    No* q = p->prim;
    while (q != NULL)
    {
        No* t = q->prox;
        free(q->d->cpf);
        free(q->d->name);
        free(q->d);
        free(q);
        q = t;
    }
    free(p);
}

void doc_libera (Doc* d)
{
    free(d->cpf);
    free(d->name);
    free(d);
}

int pilha_vazia(Pilha* p)
{
    return (p->prim == NULL);
}

void pilha_push(Pilha* p, Doc* d)
{
    No* n = (No*)malloc(sizeof(No));
    n->d = d;
    n->prox = p->prim;
    p->prim = n;
}

Doc* pilha_pop(Pilha* p)
{
    No* t;
    float v;
    if (pilha_vazia(p))
    {
        printf("Pilha vazia.\n");
        return NULL;
    }
    t = p->prim;
    Doc* d = p->prim->d;
    p->prim = t->prox;
    free(t);
    return d;
}