#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "util.h"

int main(void) {
    int op, op2;
    NoCl* clientes;
    lst_cria_cliente(&clientes);
    NoCont* contas;
    lst_cria_conta(&contas);
    NoTr* transacoes;
    cria_tr(&transacoes);
    init(&clientes, &contas, &transacoes);
    final_free_cl(clientes);
    final_free_cont(contas);
    final_free_tr(transacoes);
}