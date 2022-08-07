/* ESTRUTURAS DE DADOS */

typedef struct cliente Cliente;                                             //Struct de cliente
typedef struct noCl NoCl;                                                   //No para a lista de clientes

typedef struct transacao Transacao;                                         //Struct de transacao
typedef struct noTr NoTr;                                                   //No para a lista de transacoes

typedef struct conta Conta;                                                 //Struct de conta
typedef struct noCont NoCont;                                               //No para lista de contas

/* RELATORIOS */

void r1 (NoCl** client, NoCont** cont);                                     //Relatorio 1
void r2 (NoCont** inicio);                                                  //Relatorio 2
void r3 (NoTr** inicio);                                                    //Relatorio 3
void r4 (NoCont** inicio);                                                  //Relatorio 4
void r5 (NoCont** inicio);                                                  //Relatorio 5

/* FUNCOES DE CLIENTES */ 
void lst_cria_cliente (NoCl** inicio);                                      //Criacao da lista de clientes
int insere_cliente(NoCl **inicio);                                          //Insercao de clientes
NoCl* busca_cliente(NoCl* inicio, char* cpf);                               //Funcao que retorna ponteiro para no de cliente
int retira_cliente(NoCl** inicio, NoTr* tr, NoCont** cont);                 //Funcao que exclui cliente
void listar_clientes(NoCl** inicio);                                        //Funcao que lista clientes
void final_free_cl(NoCl* cl);                                               //Free's nos nos e structs clientes

/* FUNCOES DE CONTAS */

void lst_cria_conta (NoCont** inicio);                                      //Criacao da lista de contas
int insere_conta(NoCont **inicio, NoCl *client, char* cpf);                 //Insercao de conta
NoCont* busca_conta(NoCont* inicio, int num);                               //Funcao que retorna ponteiro para no de conta
int retira_conta(NoCont** iniciom, NoTr* tr);                               //Funcao que exclui conta
void listar_contas (NoCont** inicio);                                       //Funcao que lista contas
void final_free_cont(NoCont* c);                                            //Free's nos nos e structs contas

/* FUNCOES  DE TRANSACOES*/

void cria_tr (NoTr** inicio);                                               //Criacao da lista de transacoes
void insere_tr (NoTr** inicio, NoCont** cont, int num, int tipo, int num2); //Insercao de transacoes
void retira_tr (NoTr** inicio, int cod);                                    //Funcao que exclui transacao
NoTr* busca_tr (NoTr* inicio, int cod);                                     //Funcao que busca transacao
void listar_transacoes(NoTr* inicio);                                       //Funcao que lista transacoes
void final_free_tr(NoTr* tr);                                               //Frees nos nos e structs transacoes
