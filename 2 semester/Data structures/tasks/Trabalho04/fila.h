typedef struct fila Fila;
typedef struct person Person;

Fila *fila_cria(void);
int fila_vazia(Fila *f);
void fila_insere(Fila *f, Person* p);
Person* fila_retira(Fila *f);
void fila_libera(Fila *f);
void fila_imprime(Fila *f);
void pessoa_imprime(Person *p);
Person *create_person ();
void pessoa_libera (Person *p);