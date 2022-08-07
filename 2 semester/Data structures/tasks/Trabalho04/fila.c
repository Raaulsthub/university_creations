#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct person
{
    char *ser;
    int pass;
};

typedef struct no
{
    Person *p;
    struct no *prox;
} No;

struct fila
{
    No *ini;
    No *fim;
};

Fila *fila_cria(void)
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int fila_vazia(Fila *f)
{
    return (f->ini == NULL);
}

Person *create_person()
{
    char ser[20];
    Person *p = (Person *)malloc(sizeof(Person));
    printf("\n Digite o servico que deseja realizar: ");
    getchar();
    scanf("%[^\n]", ser);
    p->ser = (char *)malloc(sizeof(char) * (strlen(ser) + 1));
    strcpy(p->ser, ser);
    printf("\n Digite sua senha: ");
    scanf("%d", &(p->pass));
    return p;
}

void fila_insere(Fila *f, Person *p)
{
    No *n = (No *)malloc(sizeof(No));
    n->p = p;
    n->prox = NULL;
    if (f->fim != NULL)
        f->fim->prox = n;
    else
        f->ini = n;
    f->fim = n;
}

Person *fila_retira(Fila *f)
{
    if (fila_vazia(f))
    {
        return NULL;
    }
    No *t = f->ini;
    Person *returnV = t->p;
    f->ini = t->prox;
    if (f->ini == NULL) /* verifica se fila ficou vazia */
        f->fim = NULL;
    free(t);
    return returnV;
}

void fila_libera(Fila *f)
{
    No *q = f->ini;
    while (q != NULL)
    {
        No *t = q->prox;
        free(q->p->ser);
        free(q->p);
        free(q);
        q = t;
    }
    free(f);
}

void pessoa_libera(Person *p)
{
    free(p->ser);
    free(p);
}

static int fila_tamanho(Fila *f)
{
    No *no = f->ini;
    int cont = 0;
    while (no != NULL)
    {
        no = no->prox;
        cont++;
    }
    return cont;
}

void pessoa_imprime(Person *p)
{
    printf("\n SENHA: %d", p->pass);
    printf("\n SERVICO: %s", p->ser);
}

void fila_imprime(Fila *f)
{
    int tam = fila_tamanho(f);
    int cont = 0;
    while (cont != tam)
    {   
        printf("\n\nPESSOA %d:\n", cont + 1);
        Person* p = fila_retira(f);
        pessoa_imprime (p);
        fila_insere(f, p);
        cont++;
    }
}