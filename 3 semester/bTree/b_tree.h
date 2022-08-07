typedef struct arv_b_no *Arv_b_no;
typedef struct aluno Aluno;
typedef struct index Index;

Arv_b_no arv_b_cria(void);

void arv_b_free(Arv_b_no b);
int arv_b_pos_seek(Arv_b_no b, int chave, int *achou);

void arv_insere(Arv_b_no b, int chave, int pos_seek);

void btPrintKeys(Arv_b_no t);

void arv_b_map(FILE* arq, Arv_b_no root);

Aluno* criar_aluno();
int recuperar_matricula(Aluno* a);
char* recuperar_nome(Aluno* a);
int recuperar_idade(Aluno* a);
char* recuperar_curso(Aluno* a);
int tam_struct();

struct aluno
{
    int matricula;
    char nome[30];
    char curso[30];
    int idade;
};