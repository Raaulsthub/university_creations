#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COLUNAS 3

typedef struct municipio
{
    char* nome;
    int populacao;
    int** dados; //matriz de dados
} Municipio;

void menuPrincipal (Municipio* mun, int n, int d, int* atual);

void cabecalho () {
    system("cls");
    printf("\t*************************************\n\t*    Gerenciamente de Municipios    *\n\t*************************************\n");
}

void inicializar (int* n, int* d) {
    cabecalho ();
    printf("\n--> Digite o numero de municipios que deseja gerenciar: \n-> ");
    scanf("%d", &(*n));
    printf("\n--> Digite a quantidade de dias que deseja registrar por municipio: \n-> ");
    scanf("%d", &(*d));
}

void alocar (Municipio* mun, int n, int d) {
    for (int i = 0; i < n; i++)
    {
        mun[i].dados = (int**) malloc (d * sizeof(int*));
        for (int j = 0; j < d; j++)
        {
            mun[i].dados[j] = (int*) malloc (COLUNAS * sizeof(int));
        }
    }
}

void esvaziar (Municipio* mun, int n, int d) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < d; i++){
            for(int j = 0; j < COLUNAS; j++) {
                mun[k].dados[i][j] = -1;
            }
        }
    }
}

void liberar (Municipio* mun, int n, int d) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            free (mun[i].dados[j]);
        }
        free (mun[i].dados);
        if (mun[i].nome != NULL) free (mun[i].nome);
    }
    free (mun);
}

char* lerMunicipio (Municipio* mun, int atual) {
    char s[100];
    int chave;
    do {
        chave = 0;
        scanf(" %[^\n]", s);
        for (int i = 0; i < atual; i++)
        {
            if(strcmp(s, mun[i].nome) == 0) chave = 1;
        }
        if (chave == 1) printf("\n--> !!!ERRO!!! Nome ja adicionado\n  -> Digite outro nome: ");
    } while (chave == 1);
    char* s2 = (char*) malloc ((strlen (s) + 1) * sizeof (char));
    strcpy (s2, s);
    return s2;
}

void inserir (Municipio* mun, int n, int d, int* atual) {
    cabecalho ();
    char op;
    if ((*atual) < n) {
        printf("\n-> Digite o nome do municipio que voce deseja adicionar: ");
        mun[*atual].nome = lerMunicipio (mun, (*atual));
        printf("\n\n-> Digite a populacao do municipio que voce deseja adicionar: ");
        scanf("%d", &mun[*atual].populacao);
        printf("\n\n--> Municipio adicionado com sucesso!\n");
        (*atual)++;
    } else {
        printf("\n--> !!!ERRO!!! Numero total de municipios ja preenchidos\n");
    }
    printf("\n  -> Digite qualquer caracter para voltar ao menu principal: ");
    scanf (" %c", &op);
    menuPrincipal (mun, n, d, atual);
}

void buscar (Municipio* mun, int n, int d, int* atual) {
    cabecalho ();
    char op, s[100];
    int chave = 0, idx;
    printf("\n-> Digite o nome do municipio que voce deseja pesquisar: ");
    scanf(" %[^\n]", s);
    for (int i = 0; i < (*atual); i++)
    {
        if(strcmp(s, mun[i].nome) == 0) {
            chave = 1;
            idx = i;
        } 
    }
    if (chave == 1) {
        cabecalho ();
        printf("\n    Cidade: %s \tPopulacao: %d Habitantes\n", mun[idx].nome, mun[idx].populacao);
        printf("\n\t\t\tDados:\n");
        for (int i = 0; i < d; i++)
        {
            if (mun[idx].dados[i][0] < 0) {     //verifica se os dados ainda não foram preenchidos, vendo se uma das posições permanece em numeros negativos
                printf("\nDia: --   Casos Confirmados: ---   Obitos: ---\n");
            } else {
                printf("\nDia: %2d   Casos Confirmados: %3d   Obitos: %3d\n", mun[idx].dados[i][0], mun[idx].dados[i][1], mun[idx].dados[i][2]);
            }    
        }      
    } else {
        printf("\n--> !!!ERRO!!! Nome nao encontrado\n");
    }
    printf("\n  -> Digite qualquer caracter para voltar ao menu principal: ");
    scanf (" %c", &op);
    menuPrincipal (mun, n, d, atual);
}

void menu01 (Municipio* mun, int n, int d, int* atual) {
    cabecalho ();
    char op;
    printf("\n--> 1. Inserir um novo municipio\n");
    printf("\n--> 2. Buscar um municipio ja cadastrado\n");
    printf("\n--> 3. Voltar\n");
    printf("\n-> Digite a operacao desejada: ");
    scanf(" %c", &op);
    while ((op != '1') && (op != '2') && (op != '3')) {
        printf("\n--> !!!ERRO!!! Valor Invalido\n  -> Digite novamente: ");
        scanf(" %c", &op);
    }
    switch (op)
    {
    case '1' :
        inserir (mun, n, d, atual);
        break;
    case '2' :
        buscar (mun, n, d, atual);
        break;
    case '3' :
        menuPrincipal (mun, n, d, atual);
        break;
    }
}

//verifica a existencia de um valor igual em um mesmo dado dentro da matriz de um municipio
bool verificarCopia (Municipio* mun, int idx, int d, int var, int col) {
    for (int i = 0; i < d; i++)
    {
        if (mun[idx].dados[i][col] == var) return true;
    }
    return false;
}

void menu02 (Municipio* mun, int n, int d, int* atual) {
    cabecalho ();
    char s[100], op;
    int chave = 0, idx, var;
    printf("\n-> Digite o nome do municipio que voce deseja complementar: ");
    scanf(" %[^\n]", s);
    for (int i = 0; i < (*atual); i++)
    {
        if(strcmp(s, mun[i].nome) == 0) {
            chave = 1;
            idx = i;
        } 
    }
    if (chave == 1) {
        cabecalho ();
        printf("\n--> Pereenchimento da Matriz de Dados de %s:\n", mun[idx].nome);
        for (int i = 0; i < d; i++)
        {   
            printf("\n  -> Digite o numero (a partir do primeiro caso no estado) de um dia que deseja preencher: ");
            scanf("%d", &var);
            while ((var <= 0) || verificarCopia (mun, idx, d, var, 0)) {
                printf("\n--> !!!ERRO!!! Valor Invalido\n\n -> Digite novamente: ");
                scanf("%d", &var);
            }
            mun[idx].dados[i][0] = var;
            printf("\n  -> Digite a quantidade de casos confirmados nesse dia: ");
            scanf("%d", &var);
            while (var < 0) {
                printf("\n--> !!!ERRO!!! Valor Invalido\n\n -> Digite novamente: ");
                scanf("%d", &var);
            }
            mun[idx].dados[i][1] = var;
            printf("\n  -> Digite a quantidade de obitos confirmados nesse dia: ");
            scanf("%d", &var);
            while (var < 0) {
                printf("\n--> !!!ERRO!!! Valor Invalido\n\n -> Digite novamente: ");
                scanf("%d", &var);
            }
            mun[idx].dados[i][2] = var;
        }
        printf("\n\n--> Dados atualizados com sucesso!\n");
    } else {
        printf("\n--> !!!ERRO!!! Nome nao encontrado\n");
    }
    printf("\n  -> Digite qualquer caracter para voltar ao menu principal: ");
    scanf (" %c", &op);
    menuPrincipal (mun, n, d, atual);
}

void menu03 (Municipio* mun, int n, int d, int* atual) {
    cabecalho ();
    char op;
    int tConf, nConf, tObi, nObi, nIdx;
    float inc100 = 0, mor100 = 0;
    printf("\n\t  Dados Epidemiologicos Gerais:\n");
    printf("\n|\tMunicipio: | Confirmados: | Novos Confirmados: | Incidencia / 100 mil hab: | Obitos: | Novos Obitos: | Mortalidade / 100 mil hab: |\n");
    for (int i = 0; i < (*atual); i++)
    {   
        tConf = 0, nConf = 0, tObi = 0, nObi = 0, inc100 = 0, mor100 = 0, nIdx = 0;
        for (int j = 0; j < d; j++)
        {
            tConf += mun[i].dados[j][1];
            tObi += mun[i].dados[j][2];
            if (mun[i].dados[j][0] > mun[i].dados[nIdx][0]) nIdx = j;
        }
        nConf = mun[i].dados[nIdx][1];
        nObi = mun[i].dados[nIdx][2];
        inc100 = (float) tConf / (float) mun[i].populacao * 100000.0;
        mor100 = (float) tObi / (float) mun[i].populacao * 100000.0;
        if (mun[i].dados[0][0] < 0)     //verifica se os dados ainda não foram preenchidos, vendo se uma das posições permanece em numeros negativos
            printf("\n| %16s |   --------   |    ------------    |     -----------------     |  -----  |   ---------   |     ------------------     |\n", mun[i].nome);
        else 
            printf("\n| %16s | %12d | %18d | %25.1f | %7d | %13d | %26.1f |\n", mun[i].nome, tConf, nConf, inc100, tObi, nObi, mor100);
    }  
    printf("\n  -> Digite qualquer caracter para voltar ao menu principal: ");
    scanf (" %c", &op);
    menuPrincipal (mun, n, d, atual);
}

void menuPrincipal (Municipio* mun, int n, int d, int* atual) {
    char op;
    cabecalho ();
    printf("\n--> 1. Insercao ou busca de municipios\n");
    printf("\n--> 2. Preenchimento de dados\n");
    printf("\n--> 3. Listagem de municipios\n");
    printf("\n--> 4. Sair\n");
    printf("\n-> Digite a operacao desejada: ");
    scanf(" %c", &op);
    while ((op != '1') && (op != '2') && (op != '3') && (op != '4')) {
        printf("\n--> !!!ERRO!!! Valor Invalido\n  -> Digite novamente: ");
        scanf(" %c", &op);
    }
    switch (op)
    {
    case '1' :
        menu01 (mun, n, d, atual);
        break;
    case '2' :
        menu02 (mun, n, d, atual);
        break;
    case '3' :
        menu03 (mun, n, d, atual);
        break;
    case '4' :
        break;
    }
}

int main () {
    int n, d, atual = 0;   //Número de municípios e de dias, e indice atual de municipios adicionados
    inicializar (&n, &d);
    Municipio* mun = (Municipio*) malloc (n * sizeof (Municipio));
    alocar (mun, n, d);
    esvaziar (mun, n, d);
    menuPrincipal (mun, n, d, &atual);
    liberar (mun, n, d);

    return 0;
}