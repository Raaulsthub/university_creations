#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "indices.h"


// Structs e funcoes de Indice
struct regAluno{
  int matr;
  char nome[25];
  int nota1;
  int nota2;
  int excluido;
};

//TODO: Implementar um indice (em memoria) para facilitar a busca dos registros do arquivo
//TODO: Alterar as funcoes de busca, insercao e exclusao para usar o indice

struct indice{
  int matr;
  int pos_seek;
};

// Structs e funcoes de arvore
struct no{
    Indice info;
    struct no* pai;
    struct no* esq;
    struct no* dir;
};

struct arvore{
    No * raiz;
    int linhaAtual;
};

void popula_arvore(FILE* arq, Arvore* arv) {
    reg_aluno aluno;
    Indice i;
    rewind(arq);

    while(fread(&aluno,sizeof(aluno), 1, arq)) {
        i.matr = aluno.matr;
        i.pos_seek = ftell(arq) - sizeof(aluno);
        arv_insere_no(arv, i);
    }
}

void mostra(FILE *arq){
  reg_aluno aluno;
  rewind(arq);
  while(fread(&aluno,sizeof(aluno), 1, arq))
    if (aluno.excluido == 0)
      printf("%d\t%s\t%d\t%d\n",aluno.matr, aluno.nome, aluno.nota1, aluno.nota2);
}

int pesquisa(FILE *arq, int matr, reg_aluno *al, Arvore* arv_indices){
  reg_aluno aluno;
  No* no = arv_busca_no(arv_indices->raiz, matr);
  if(no == NULL) {
    return 0;
  } else {
    fseek(arq, no->info.pos_seek, SEEK_SET);
    fread(&aluno, sizeof(aluno), 1, arq);

    if(aluno.excluido == 1)
      return 0;

    *al = aluno;
    return 1;
  }
  
}

void exclui(FILE *arq, int matr, Arvore* arv){
  reg_aluno aluno;
  if (pesquisa(arq, matr, &aluno, arv)){
    int excl = 1;
    printf("Excluindo: %s\n", aluno.nome);
    fseek(arq, -1*sizeof(int), SEEK_CUR);
    fwrite(&excl, sizeof(int), 1, arq);
    fflush(arq);
  }
}

void inclui(FILE *arq, Arvore* arv_indices){
  Indice i;
  reg_aluno aluno;
  fseek(arq, 0, SEEK_END);
  //printf("Pos=%d", ftell(arq));
  printf("Informe os dados do aluno (matr, nome, nota1 e nota2) \n");
  scanf("%d%s%d%d",&aluno.matr, aluno.nome, &aluno.nota1, &aluno.nota2);
  aluno.excluido=0;
  i.pos_seek = ftell(arq);
  fwrite(&aluno,sizeof(aluno),1,arq);
  i.matr = aluno.matr;
  // POS SEEK TEM QUE SABER O INDEX DA ULTIMA LINHA DO FILE
  arv_cria_no(i);
  arv_insere_no(arv_indices, i);
}

Arvore * arv_cria ()
{
    Arvore * arv = (Arvore *) malloc(sizeof(Arvore));
    arv->raiz = NULL;
    arv->linhaAtual = 0;
    return arv;
}

No * arv_cria_no (Indice v)
{
    No * no = (No *) malloc(sizeof(No));
    no->info.matr = v.matr;
    no->info.pos_seek = v.pos_seek;
    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;
    return no;
}

int arv_vazia (Arvore * arvore)
{
    return (arvore->raiz == NULL);
}

int arv_no_vazio (No * no)
{
    return (no->esq==NULL && no->dir == NULL);
}

No * arv_busca_raiz (Arvore * arvore)
{
    return (arvore->raiz);
}

No* arv_busca_filho(No * no, int dir){
    if (dir)
        return no->dir;
    else return no->esq;
}

Indice arv_busca_valor(No * no){
    return no->info;
}

void arv_libera_arvore(Arvore * arv){

    arv_libera_no(arv->raiz);
    free(arv);
}

static void arv_libera_no(No * no){
    if (no==NULL)
        return;
    arv_libera_no(no->esq);
    arv_libera_no(no->dir);
    free(no);

}

void arv_insere_no(Arvore * arv, Indice v){
    if (arv->raiz==NULL){
        No * filho = arv_cria_no (v);
        arv->raiz = filho;
        return;
    }
    arv_insere_no2(arv->raiz, v);
}

static void arv_insere_no2(No * no, Indice v){
    if (no==NULL) return;

    if (v.matr < no->info.matr)
    {
        if (no->esq==NULL){
            No * filho = arv_cria_no (v);
            arv_insere(no, filho, 0);
            return;
        }

        arv_insere_no2(no->esq, v);
    }
    else {
        if (no->dir==NULL){
            No * filho = arv_cria_no (v);
            arv_insere(no, filho, 1);
            return;
        }

        arv_insere_no2(no->dir, v);
    }

}

int arv_remove_no(Arvore * arv, Indice v){
    if (arv->raiz==NULL) return 0;

    return arv_remove_no2(arv->raiz, v);
}


static int arv_remove_no2(No * no, Indice v){
    if (no==NULL) return 0;

    if (no->info.matr == v.matr)
    {
        arv_remove_no3(no);
        return 1;
    }

    if (v.matr < no->info.matr)
        return arv_remove_no2(no->esq, v);
    else return arv_remove_no2(no->dir, v);

}

static void arv_remove_no3(No * filho){

    if (filho->esq==NULL && filho->dir == NULL)
    {
        if (filho->pai->esq==filho)
            filho->pai->esq = NULL;
        else filho->pai->dir = NULL;
        free(filho);
        return;
    }
    if (filho->esq!=NULL) {

        No * maior = encontra_maior(filho->esq);
        filho->info = maior->info;

        arv_remove_no3(maior);
        return;
    }
    else{

        No * menor = encontra_menor(filho->dir);
        filho->info = menor->info;

        arv_remove_no3(menor);
        return;
    }

}

No * arv_busca_no(No * no, int v){
    if (no==NULL)
        return NULL;

    if (no->info.matr==v)
        return no;
    if (v < no->info.matr)
        return arv_busca_no(no->esq, v);

    return arv_busca_no(no->dir, v);

}

static No * encontra_maior(No * no)
{
    if (no->dir==NULL) return no;
    return encontra_maior(no->dir);
}

static No * encontra_menor(No * no)
{
    if (no->esq==NULL) return no;
    return encontra_menor(no->esq);
}

static void arv_insere (No* pai, No* filho, int dir)
{
    if (dir)
        pai->dir = filho;
    else
        pai->esq = filho;

    filho->pai = pai;

}

void imprime (No* h) {
    if (h == NULL) return;
    printf("%d ", h->info.matr);
    printf("%d\n", h->info.pos_seek);
    imprime(h->esq);
    imprime(h->dir);
}

int main(){
    int matr, op;
    reg_aluno aluno;
    FILE *arq;

    Arvore* arv_indices = arv_cria();

    if (access("alunos.dat", F_OK) == 0)
        arq=fopen("alunos.dat","r+"); // arquivo existe
    else
        arq=fopen("alunos.dat","w+"); // arquivo nao existia
    
    popula_arvore(arq, arv_indices);
    
    do {
        printf("\nMenu\n 1. Mostrar todos\n 2. Pesquisar\n 3. Incluir\n 4. Excluir\n 5. Sair\nInforme uma opcao: ");
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("\nAlunos gravados no arquivo: \n");
                mostra(arq);
                break;
            case 2:
                printf("\nDigite a matricula a ser buscada: ");
                scanf("%d",&matr);
                if(pesquisa(arq, matr, &aluno, arv_indices)) {
                    printf("\nAluno encontrado:\n");
                    printf("%d\t%s\t%d\t%d\n",aluno.matr, aluno.nome, aluno.nota1, aluno.nota2);
                } else
                    printf("\nA matricula %d nao foi encontrada!\n",matr);
                break;
            case 3:
                inclui(arq, arv_indices);
                break;
            case 4:
                printf("\nDigite a matricula a ser excluida: ");
                scanf("%d",&matr);
                exclui(arq, matr, arv_indices);
                break;
            case 5:
                printf("\nSaindo...\n\n");
                break;
            default: printf("\nOpcao invalida!\n");
                break;
        }
    } while(op != 5);
    fclose(arq);

    return 0;
}

