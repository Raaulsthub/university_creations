typedef struct indice Indice;
typedef struct regAluno reg_aluno;


// ARVORE BINARIA
typedef struct no No;
typedef struct arvore Arvore;


static void arv_libera_no(No * no);
static void arv_insere_no2(No * no, Indice v);

static void arv_insere (No* pai, No* filho, int dir);

static void arv_remove_no3(No * filho);
static int arv_remove_no2(No * no, Indice v);

static No * encontra_maior(No * no);
static No * encontra_menor(No * no);

Arvore * arv_cria ();
No * arv_cria_no (Indice v);
int arv_vazia (Arvore * arvore);
int arv_no_vazio (No * no);
No * arv_busca_raiz (Arvore * arvore);
No* arv_busca_filho(No * no, int dir);
Indice arv_busca_valor(No * no);
No * arv_busca_no(No * no, int v);
void arv_libera_arvore(Arvore * arv);
void arv_insere_no(Arvore * arv, Indice v);
int arv_remove_no(Arvore * arv, Indice v);

void mostra(FILE *arq);
int pesquisa(FILE *arq, int matr, reg_aluno *al, Arvore* arv_indices);
void exclui(FILE *arq, int matr, Arvore* arv);
void inclui(FILE *arq, Arvore* arv_indices);