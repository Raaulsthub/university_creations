typedef struct no_arv No_arv;
typedef struct curso Curso;
typedef struct arvore Arvore;
typedef struct no No_lst;
typedef struct aluno Al;

Arvore *arv_cria();
void arv_insere_curso(Arvore *arv);
No_arv *arv_get_raiz(Arvore *arv);
void imprime_asc(No_arv *no);
void arv_exclui_curso(Arvore *arv);
No_lst *get_list(Arvore *arv, int v);
void arv_imprime_vinc(No_arv* no);
void arv_libera_arvore(Arvore * arv);

void lst_cria(No_lst **inicio);
void lst_libera(No_lst **inicio);
void lst_insere_ordenado(Arvore *arv);
No_lst *lst_busca_rec(No_lst *inicio, int v);
void lst_imprime(Arvore* arv);
void lst_retira(Arvore* arv);