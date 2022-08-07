#include <stdio.h>
#include "menu.h"
#include "fila.h"
#include "pilha.h"

int main () {
    Fila* lstPri = fila_cria ();
    Fila* lst = fila_cria ();
    Pilha* pilha = pilha_cria ();

    menu (&lstPri, &lst, &pilha);
    
    fila_libera (lstPri);
    fila_libera (lst);
    pilha_libera (pilha);

    return 0;
}