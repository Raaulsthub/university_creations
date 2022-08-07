typedef struct pilha Pilha;
typedef struct doc Doc;

void pilha_imprime(Pilha *p);
Pilha* pilha_cria();
void pilha_libera(Pilha* p);
int pilha_vazia(Pilha* p);
void pilha_push(Pilha* p, Doc* d);
Doc* pilha_pop(Pilha* p);
Doc *create_doc ();
void doc_libera (Doc* d);
void doc_imprime(Doc *d);