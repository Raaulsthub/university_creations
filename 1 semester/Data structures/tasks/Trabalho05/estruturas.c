#include "menu.h"
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct curso
{
    int codigo;
    char *nome;
    char *centro;
    No_lst *lst;
};

struct no_arv
{
    Curso *c;
    No_arv *esq;
    No_arv *dir;
    No_arv *pai;
};

struct arvore
{
    No_arv *raiz;
};

struct no
{
    Al *aluno;
    struct no *prox;
};

struct aluno
{
    int mat;
    char *nome;
    char *anoIng;
};
/*composi��o de uma arvore*/

static void arv_libera_no(No_arv* no);

static void arv_insere_no2(No_arv * no, No_arv* c);
static void arv_insere (No_arv* pai, No_arv* filho, int dir);

static void arv_remove_no3(No_arv * filho);
static int arv_remove_no2(No_arv * no, int v);

static No_arv * encontra_maior(No_arv * no);
static No_arv * encontra_menor(No_arv * no);

static No_lst *lst_localiza_ultimo_menor(No_lst *inicio, int v);
static No_lst *lst_localiza_ultimo_menor_rec(No_lst *ant, No_lst *inicio, int v);
static No_lst *lst_localiza_ultimo(No_lst *inicio);
static No_lst *lst_localiza_ultimo_rec(No_lst *ant, No_lst *inicio);
static void insere_lista(No_lst **inicio, int v, No_lst *ant);
static void lst_retira_rec(No_lst **no, int v);
static void lst_imprime_rec(No_lst *no);

/* fun��o de cria��o */
Arvore * arv_cria ()
{
    Arvore * arv = (Arvore *) malloc(sizeof(Arvore));
    arv->raiz = NULL;
    return arv;
}



/* fun��o de cria��o */
No_arv * arv_cria_no (int v)
{
    No_arv * no = (No_arv *) malloc(sizeof(No_arv));
    no->c = (Curso*) malloc (sizeof(Curso));
    no->c->codigo = v;
    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;
    return no;
}


/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
int arv_vazia (Arvore * arvore)
{
   return (arvore->raiz == NULL);
}

/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
int arv_no_vazio (No_arv * no)
{
   //supondo que no n�o seja nulo
   return (no->esq==NULL && no->dir == NULL);
}

/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */
No_arv * arv_busca_raiz (Arvore * arvore)
{
   return (arvore->raiz);
}


No_arv* arv_busca_filho(No_arv * no, int dir){
    if (dir)
        return no->dir;
    else return no->esq;
}

Curso* arv_busca_valor(No_arv * no){
    return no->c;
}


void arv_libera_arvore(Arvore * arv){

    arv_libera_no(arv->raiz);
    free(arv);
}

static void arv_libera_no(No_arv * no){
    if (no==NULL)
        return;
    arv_libera_no(no->esq);
    arv_libera_no(no->dir);
    free(no->c->centro);
    free(no->c->nome);
    lst_libera (&(no->c->lst));
    free(no->c);
    free(no);
}


void arv_insere_no(Arvore * arv, No_arv* c){
    if (arv->raiz==NULL){
        No_arv * filho = c;
        arv->raiz = filho;
        return;
    }
    arv_insere_no2(arv->raiz, c);
}

static void arv_insere_no2(No_arv * no, No_arv* c){
    if (no==NULL) return;

    if (c->c->codigo == no->c->codigo) {
        printf("\nCurso ja existe no banco de dados!");
        return;
    }

    if (c->c->codigo < no->c->codigo)
    {
        if (no->esq==NULL){
            No_arv * filho = c;
            arv_insere(no, filho, 0);
            return;
        }

        arv_insere_no2(no->esq, c);
    }
    else {
        if (no->dir==NULL){
            No_arv * filho = c;
            arv_insere(no, filho, 1);
            return;
        }

        arv_insere_no2(no->dir, c);
    }

}


int arv_remove_no(Arvore * arv, int v){
    if (arv->raiz==NULL) return 0;
    return arv_remove_no2(arv->raiz, v);
}


static int arv_remove_no2(No_arv * no, int v){
    if (no==NULL) return 0;

    if (no->c->codigo==v)
    {
        arv_remove_no3(no);
        return 1;
    }

    if (v < no->c->codigo)
        return arv_remove_no2(no->esq, v);
    else return arv_remove_no2(no->dir, v);

}

static void arv_remove_no3(No_arv * filho){

    if (filho->esq==NULL && filho->dir == NULL)
    {
        if (filho->pai->esq==filho)
            filho->pai->esq = NULL;
        else filho->pai->dir = NULL;
        free(filho);
        return;
    }
    if (filho->esq!=NULL) {

        No_arv * maior = encontra_maior(filho->esq);
        filho->c->codigo = maior->c->codigo;
        filho->c->nome = maior->c->nome;
        filho->c->centro = maior->c->centro;
        filho->c->lst = maior->c->lst;        
        arv_remove_no3(maior);
        return;
    }
    else{

        No_arv * menor = encontra_menor(filho->dir);
        filho->c->codigo = menor->c->codigo;
        filho->c->nome = menor->c->nome;
        filho->c->centro = menor->c->centro;
        filho->c->lst = menor->c->lst; 

        arv_remove_no3(menor);
        return;
    }

}

No_arv * arv_busca_no(No_arv * no, int v){
    if (no==NULL)
        return NULL;

    if (no->c->codigo==v)
        return no;
    if (v<no->c->codigo)
        return arv_busca_no(no->esq, v);

    return arv_busca_no(no->dir, v);

}

static No_arv * encontra_maior(No_arv * no)
{
    if (no->dir==NULL) return no;
    return encontra_maior(no->dir);
}

static No_arv * encontra_menor(No_arv * no)
{
    if (no->esq==NULL) return no;
    return encontra_menor(no->esq);
}



/* inser��o de um no filho abaixo de um no pai */
static void arv_insere (No_arv* pai, No_arv* filho, int dir)
{
   if (dir)
       pai->dir = filho;
   else
      pai->esq = filho;

   filho->pai = pai;

}


void arv_insere_curso(Arvore *arv)
{
    int cod;
    printf("\nDigite o codigo do curso: ");
    scanf("%d", &cod);
    No_arv *curso = arv_cria_no(cod);
    char nome[30];
    printf("\nDigite o nome do curso: ");
    scanf(" %[^\n]", nome);
    curso->c->nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(curso->c->nome, nome);
    char centro[30];
    printf("\nDigite o centro ao qual o curso pertence: ");
    scanf(" %[^\n]", centro);
    curso->c->centro = (char *)malloc(sizeof(char) * (strlen(centro) + 1));
    strcpy(curso->c->centro, centro);
    lst_cria(&(curso->c->lst));
    if (arv_busca_no (arv->raiz, cod)) {
        printf("\nCurso ja existe no banco de dados!");
        free(curso->c->centro);
        free(curso->c->nome);
        lst_libera (&(curso->c->lst));
        free(curso->c);
        free(curso);
    } else {
        arv_insere_no(arv, curso);
    }
}

void arv_imprime_no(No_arv *no)
{
    printf("CURSO DE CODIGO %d\n", no->c->codigo);
    printf("NOME: %s\n", no->c->nome);
    printf("CENTRO: %s\n\n\n", no->c->centro);
}

void imprime_asc(No_arv *no)
{
    if (no == NULL)
        return;

    imprime_asc(no->esq);
    arv_imprime_no(no);
    imprime_asc(no->dir);
}

No_arv *arv_get_raiz(Arvore *arv)
{
    return arv->raiz;
}

void arv_exclui_curso(Arvore *arv)
{
    int cod;
    printf("Digite o codigo do curso: ");
    scanf("%d", &cod);
    if (arv->raiz->esq == NULL && arv->raiz->dir == NULL) {
        printf("\n!!!Operacao invalida! Voce esta tentando excluir o unico curso, mas a universidade nao pode ficar sem cursos!!!\n");
        printf("\n!Adicione ao menos mais um curso para poder excluir este!\n");
        return;
    }
    No_arv* c = arv_busca_no(arv->raiz, cod);
    if (c == NULL) {
        printf("Curso nao encontrado!");
        return;
    }
    arv_remove_no(arv, cod);
}

void lst_cria(No_lst **inicio)
{
    *inicio = NULL;
}

void lst_libera(No_lst **inicio)
{
    No_lst *no = *inicio;
    while (no != NULL)
    {
        No_lst *t = no;
        no = no->prox;
        free(t->aluno->anoIng);
        free(t->aluno->nome);
        free(t->aluno);
        free(t);
    }
    *inicio = NULL;
}

void lst_insere_ordenado(Arvore *arv)
{
    int cod, v;
    printf("\nDigite o codigo do curso: ");
    scanf("%d", &cod);
    No_arv *noArv = arv_busca_no(arv->raiz, cod);
    if (noArv == NULL) {
        printf("\nFalha ao inserir aluno! Curso digitado nao existe!\n");
    } else {
        printf("\nDigite o numero de matricula: ");
        scanf("%d", &v);
        if (lst_busca_rec(noArv->c->lst, v) != NULL) {
            printf("\nFalha ao inserir aluno! Numero de matricula ja existe neste curso!\n");
        } else {
            No_lst *ant = lst_localiza_ultimo_menor_rec(NULL, (noArv->c->lst), v);
            insere_lista(&(noArv->c->lst), v, ant);
            printf("\nAluno adicionado com Sucesso!\n");
        }
    }
}

static void insere_lista(No_lst **inicio, int v, No_lst *ant)
{
    No_lst *novo = (No_lst *)malloc(sizeof(No_lst));
    novo->aluno = (Al *)malloc(sizeof(Al));
    novo->aluno->mat = v;
    char nome[30];
    printf("\nDigite o nome do aluno: ");
    scanf(" %[^\n]", nome);
    novo->aluno->nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(novo->aluno->nome, nome);
    char ano[30];
    printf("\nDigite o ano de ingresso ao curso: ");
    scanf(" %[^\n]", ano);
    novo->aluno->anoIng = (char *)malloc(sizeof(char) * (strlen(ano) + 1));
    strcpy(novo->aluno->anoIng, ano);
    if (ant == NULL)
    {
        novo->prox = *inicio;
        *inicio = novo;
    }
    else
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }
}

static No_lst *lst_localiza_ultimo_menor_rec(No_lst *ant, No_lst *inicio, int v)
{

    if (inicio != NULL)
    {
        if (inicio->aluno->mat < v)
            return lst_localiza_ultimo_menor_rec(inicio, inicio->prox, v);
        else
            return ant;
    }
    return ant;
}

No_lst *lst_busca_rec(No_lst *inicio, int v)
{
    if (inicio != NULL)
    {
        if (inicio->aluno->mat == v)
            return inicio;
        return lst_busca_rec(inicio->prox, v);
    }
    return NULL;
}

static void lst_imprime_rec(No_lst *no)
{
    if (no != NULL)
    {
        printf("MATRICULA DO ALUNO: %d\n", no->aluno->mat);
        printf("NOME: %s\n", no->aluno->nome);
        printf("ANO DE INGRESSO: %s\n\n\n", no->aluno->anoIng);

        lst_imprime_rec(no->prox);
    }
}

void lst_imprime(Arvore* arv) {
    int cod;
    printf("\nDigite o codigo do curso: ");
    scanf("%d", &cod);
    No_arv *noArv = arv_busca_no(arv->raiz, cod);
    if (noArv == NULL) {
        printf("\nFalha ao imprimir! Curso digitado nao existe!\n");
    } else {
        No_lst *no = noArv->c->lst;
        printf("\nALUNOS DO CURSO: %s\n\n", noArv->c->nome);
        lst_imprime_rec (no);
    }
}

static void lst_retira_rec(No_lst **no, int v)
{
    if ((*no) != NULL)
    {
        if ((*no)->aluno->mat == v)
        {
            No_lst *t = *no;
            *no = (*no)->prox;
            free(t->aluno->anoIng);
            free(t->aluno->nome);
            free(t->aluno);
            free(t);
        }
        else
        {
            lst_retira_rec(&(*no)->prox, v);
        }
    }
}

void lst_retira(Arvore *arv)
{
    int cod, v;
    printf("\nDigite o codigo do curso: ");
    scanf("%d", &cod);
    No_arv *noArv = arv_busca_no(arv->raiz, cod);
    if (noArv == NULL) {
        printf("\nFalha ao remover aluno! Curso digitado nao existe!\n");
    } else {
        No_lst **no = &(noArv->c->lst);
        printf("\nDigite o numero de matricula: ");
        scanf("%d", &v);
        if (lst_busca_rec(noArv->c->lst, v) == NULL) {
            printf("\nFalha ao remover aluno! Numero de matricula nao existe neste curso!\n");
        } else {
            lst_retira_rec(no, v);
            printf("\nAluno removido com Sucesso!\n");
        }
    }
}

void arv_imprime_vinc(No_arv* no) {

    No_lst* p = NULL;
    if (no == NULL) {
        return;
    }

    arv_imprime_vinc(no->esq);
    p = no->c->lst;
    while(p != NULL) {
        printf("\n Aluno de matricula: %d", p->aluno->mat);
        printf("\n Nome: %s", p->aluno->nome);
        printf("\n Curso: %s", no->c->nome);
        printf("\n Centro do curso: %s", no->c->centro);
        p = p->prox;
    }
    arv_imprime_vinc(no->dir);
}