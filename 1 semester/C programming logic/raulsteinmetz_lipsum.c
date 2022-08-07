#include <stdio.h>
#include <stdlib.h>

char menu_inicial(){
    char op;
    printf("****************************\n");
    printf("* GESTAO DE ESTOQUE LIPSUM *\n");
    printf("****************************\n");
    printf("Opcoes: \n");
    printf("|   C. Criacao\n");
    printf("|   R. Consulta\n");
    printf("|   U. Atualizacao\n");
    printf("|   D. Remocao\n");
    printf("|   E. Encerrar\n");
    printf(">Selecione uma opcao: ");
    scanf(" %c", &op);
    while (op!='c' && op!='C' && op!='r' && op!='R' && op!='u' && op!='U' && op!='d' && op!='D' && op!='e' && op!='E'){
        printf("Codigo invalido...\n");
        printf(">Digite novamente a opcao escolhida: ");
        scanf(" %c", &op);
	}
	system("cls");
    return op;
}

int menu_criacao(){
    int op;
    printf("C > Operacoes: \n");
    printf("|   1. Inserir produto\n");
    printf("|   2. Inserir produto na posicao\n");
    printf("|   3. Voltar\n");
    printf(">Selecione uma operacao: ");
    scanf("%d", &op);
    while (op!=1 && op!=2 && op!=3){
        printf(">Codigo digitado eh invalido...\n");
        printf(">Selecione uma operacao: ");
        scanf("%d", &op);
    }
    system("cls");
    return op;
}

int estoque_scan(int vet[], int tam, int cod){
    for (int i=0; i<tam; i++){
        if (vet[i]==cod){
            return -2;
        }
    }    
    for (int i=0; i<tam; i++){
        if (vet[i]==-1){
            return i;
        }
    }
    return -1;
}

void mostra_estoque(int vetC[], int vetQ[], float vetP[], int tam){
    int a=0;
    for (int i=0; i<tam; i++){
        if(vetC[i]!=-1){
            printf("%d. [%d] R$%.2f (%du)\n", i, vetC[i], vetP[i], vetQ[i]);
            a++;
        }
    }
    if (a==0){
        printf(">O estoque estah vazio...\n");
    }
}

void posiciona_prod(int vet_cod[], int vet_qt[], float vet_prec[], int tam, int pos, int cod, int qt, float prec){
    //arrumando vetor apos a posicao
    int sobrescrito_cod = vet_cod[pos];
    int sobrescrito_qt = vet_qt[pos];
    float sobrescrito_p = vet_prec[pos];
    int corrente_cod, corrente_qt;
    float corrente_p;
    vet_cod[pos] = cod;
    vet_qt[pos] = qt;
    vet_prec[pos] = prec;
    for (int i = pos + 1; i < tam; i++){
        corrente_cod = vet_cod[i];
        corrente_qt = vet_qt[i];
        corrente_p = vet_prec[i];
        vet_cod[i] = sobrescrito_cod;
        vet_qt[i] = sobrescrito_qt;
        vet_prec[i] = sobrescrito_p;
        if (corrente_cod == -1){
            return;
        }
        sobrescrito_cod = corrente_cod;
        sobrescrito_qt = corrente_qt;
        sobrescrito_p = corrente_p;
    }
    // arrumando vetor antes da posicao
    for(int i = 0; i < pos; i++){
        corrente_cod = vet_cod[i];
        corrente_qt = vet_qt[i];
        corrente_p = vet_prec[i];
        vet_cod[i] = sobrescrito_cod;
        vet_qt[i] = sobrescrito_qt;
        vet_prec[i] = sobrescrito_p;
        if(corrente_cod == -1){
            return;
        }
        sobrescrito_cod = corrente_cod;
        sobrescrito_qt = corrente_qt;
        sobrescrito_p = corrente_p;
    }
}

void criacao(int vet_cod[], float vet_prec[], int vet_qt[], int tam){
    int a, pos;
    a = menu_criacao();
    switch(a){
        int cod, qt, idx, pos, aux, continuar;
        float p;
        case 1: 
            printf(">Opcao 1: Inserir Produto\n");
            printf(">Digite o codigo do produto: ");
            scanf("%d", &cod);
            printf(">Digite a quantidade do produto: ");
            scanf("%d", &qt);
            printf(">Digite o preco unitario do produto: ");
            scanf("%f", &p);
            idx = estoque_scan(vet_cod, 10, cod);
            if (idx==-1){
                printf(">ERRO!!! Estoque estah lotado!!!\n");
                printf(">Produto nao foi inserido...\n");
                printf(">Digite 1 para continuar: ");
                scanf("%d", &continuar); 
            }
            else if (idx==-2){
                printf(">ERRO!!! Codigo ja existe no estoque!!!\n");
                printf(">Produto nao foi inserido...\n");
                printf(">Digite 1 para continuar: ");
                scanf("%d", &continuar);
            }
            else{
                vet_cod[idx] = cod;
                vet_prec[idx] = p;
                vet_qt[idx] = qt;
                printf(">Produto inserido com sucesso!\n");
                printf(">Situacao atual do estoque: \n");
                mostra_estoque(vet_cod, vet_qt, vet_prec, 10);
                printf(">Digite 1 para continuar: ");
                scanf("%d", &continuar);
            }
            system("cls");
            break;
        case 2: 
            printf(">Opcao 2: Inserir produto na posicao\n");
            printf(">Digite o codigo do produto: ");
            scanf("%d", &cod);
            printf(">Digite a quantidade do produto: ");
            scanf("%d", &qt);
            printf(">Digite o preco unitario do produto: ");
            scanf("%f", &p);
            printf(">Digite a posicao na qual quer inserir o produto: ");
            scanf("%d", &pos);
            while (pos<0 || pos>=tam){
            	printf(">Posicao invalida. Digite novamente:  ");
            	scanf("%d", &pos);
			}
            idx = estoque_scan(vet_cod, 10, cod);
            if (idx==-1){
                printf(">ERRO!!! Estoque estah lotado!!!\n");
                printf(">Produto nao foi inserido...\n");
                printf(">Digite 1 para continuar: ");
                scanf("%d", &continuar);
            }
            else if (idx==-2){
                printf(">ERRO!!! Codigo ja existe no estoque!!!\n");
                printf(">Produto nao foi inserido...\n");
                printf(">Digite 1 para continuar: ");
                scanf("%d", &continuar);
            }
            else{
                posiciona_prod(vet_cod, vet_qt, vet_prec, tam, pos, cod, qt, p);
                printf(">Produto inserido com sucesso na posicao desejada!!\n");
                printf(">Situacao atual do estoque: \n");
                mostra_estoque(vet_cod, vet_qt, vet_prec, 10);
                printf(">Digite 1 para continuar: ");
                scanf("%d", &continuar);
            }
            system("cls");
            break; 
        case 3:
            printf(">Opcao 3: Voltar\n");
            printf(">Digite 1 para continuar: ");
            scanf("%d", &continuar);
            system("cls");
            break;
        default:
            //nao vai ser necessario...
			break;                    
    }
}

int menu_consulta(){
	int op;
	printf("R>Operacoes: \n");
	printf("|   1. Listar todos os produtos\n");
	printf("|   2. Buscar produto por codigo\n");
	printf("|   3. Unidades em estoque\n");
	printf("|   4. Valor em estoque\n");
	printf("|   5. Voltar\n");
	printf(">Selecione uma operacao: ");
	scanf("%d", &op);
    while (op!=1 && op!=2 && op!=3 && op!=4 && op!=5){
        printf(">Codigo digitado eh invalido...\n");
        printf(">Selecione uma operacao: ");
        scanf("%d", &op);
    }
    system("cls");
    return op;
}

int espacos_livres(int vet[], int tam){
    int livres=0;
    for (int i=0; i<tam; i++){
        if(vet[i]==-1){
            livres++;
        }
    }
    return livres;
}

int achar_produto(int vet[], int tam, int cod){
    int pos;
    for (pos=0; pos<tam; pos++){
        if (vet[pos]==cod){
            return pos;
        }
    }
    return -1;
}

int contador_unidades(int vet[], int tam){
    int s=0;
    for (int i=0; i<tam; i++){
        if (vet[i]!=-1){
            s = s + vet[i];
        }
    }
    return s;
}

float valor_total(int vet_qt[], float vet_prec[], int tam){
    float valor=0;
    for (int i=0; i<tam; i++){
        if (vet_qt[i]!=-1){
            valor = valor + (float) vet_qt[i] * vet_prec[i];
        }
    }
    return valor;
}

void consulta(int vet_cod[], float vet_prec[], int vet_qt[], int tam){
	int a, livres, continuar, cod, pos, unidades;
    float valor;
	a = menu_consulta();
    switch(a){
        case 1:
            printf(">Opcao 1: Estoque: \n");
            mostra_estoque(vet_cod, vet_qt, vet_prec, 10);
            livres = espacos_livres(vet_cod, tam);
            printf(">Existem %d espacos livres!!!\n", livres);
            printf(">Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        case 2:
            printf(">Opcao 2: Buscar produto por codigo\n");
            printf(">Digite o codigo do produto: ");
            scanf("%d", &cod);
            pos = achar_produto(vet_cod, tam, cod);
            if (pos==-1){
                printf(">Alerta!!! Produto nao encontrado!!!\n");
            }
            else{
                printf("%d. [%d] R$%.2f (%du)\n", pos, vet_cod[pos], vet_prec[pos], vet_qt[pos]);
            }
            printf(">Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        case 3:
            printf(">Opcao 3: Unidades em estoque\n");
            unidades = contador_unidades(vet_qt, tam);
            printf(">Ao total, o estoque possui %d unidades", unidades); 
            printf("\n>Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        case 4:
            printf(">Opcao 4: Valor total do estoque\n");
            valor = valor_total(vet_qt, vet_prec, tam);
            printf("> O valor total do estoque eh R$%.2f", valor);
            printf("\n>Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        case 5:
            printf(">Opcao 5: Voltar\n");
            printf(">Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        default:
            //nao serah preciso
            break;
    }
    system("cls");
}

int menu_atualizacao(){
	int op;
	printf("U>Operacoes: \n");
	printf("|   1. Atualizar produto\n");
	printf("|   2. Trocar produtos\n");
	printf("|   3. Aplicar taxa\n");
	printf("|   4. Ordenar estoque\n");
	printf("|   5. Voltar\n");
	printf(">Selecione uma operacao: ");
	scanf("%d", &op);
    while (op!=1 && op!=2 && op!=3 && op!=4 && op!=5){
        printf(">Codigo digitado eh invalido...\n");
        printf(">Selecione uma operacao: ");
        scanf("%d", &op);
    }
    system("cls");
    return op;    
}

void troca(int vet_cod[], float vet_prec[], int vet_qt[], int pos1, int pos2){
    int auxInt;
    float auxFloat;
    if(vet_cod[pos1]==-1 && vet_cod[pos2]==-1){
        printf("Alerta!!! Troca nao realizada, visto que as duas posicoes estao vazias...");
    }
    else if(vet_cod[pos1]==-1 && vet_cod[pos2]!=-1){
        vet_cod[pos1] = vet_cod[pos2];
        vet_prec[pos1] = vet_prec[pos2];
        vet_qt[pos1] = vet_qt[pos2];
        vet_cod[pos2] = -1;
        vet_prec[pos2] = -1;
        vet_qt[pos2] = -1;
        printf("Troca realizada com sucesso");
    }
    else if(vet_cod[pos1]!=-1 && vet_cod[pos2]==-1){
        vet_cod[pos2] = vet_cod[pos1];
        vet_prec[pos2] = vet_prec[pos1];
        vet_qt[pos2] = vet_qt[pos1];
        vet_cod[pos1] = -1;
        vet_prec[pos1] = -1;
        vet_qt[pos1] = -1;
        printf("Troca realizada com sucesso");
    }
    else{
        auxInt = vet_cod[pos1];
        vet_cod[pos1] = vet_cod[pos2];
        vet_cod[pos2] = auxInt;
        auxInt = vet_qt[pos1];
        vet_qt[pos1] = vet_qt[pos2];
        vet_qt[pos2] = auxInt;
        auxFloat = vet_prec[pos1];
        vet_prec[pos1] = vet_prec[pos2];
        vet_prec[pos2] = auxFloat;
        printf("Troca realizada com sucesso");
    }
}

void aplica_taxa(float vet[], float taxa, int tam){
    taxa = taxa/100;
    for (int i=0; i<tam; i++){
        if (vet[i]!=-1){
            vet[i] = vet[i] + vet[i]*taxa;
        }
    }
}

int menu_ordenacao(){
    int tipo;
    printf(">Escolha a maneira de ordenar o estoque: \n");
    printf("|   1.Codigo\n");
    printf("|   2.Quantidade\n");
    printf("|   3.Preco\n");
    printf(">Selecione um tipo: ");
    scanf("%d", &tipo);
    while (tipo!=1 && tipo!=2 && tipo!=3){
        printf(">Codigo digitado eh invalido...\n");
        printf(">Selecione uma operacao: ");
        scanf("%d", &tipo);
    }
    return tipo;
}

void bubble_sortINT(int vet_ord[], int vet_n[], float vet_prec[], int tam, int ordem){
    int auxInt;
    float auxFloat;
    if (ordem==0){
        for (int i=0; i<tam-1; i++){
            for (int j=i; j<tam; j++){
                if((vet_ord[i] > vet_ord[j] || vet_ord[i]==-1) && vet_ord[j]!=-1){
                    auxInt = vet_ord[i];
                    vet_ord[i] = vet_ord[j];
                    vet_ord[j] = auxInt;
                    auxInt = vet_n[i];
                    vet_n[i] = vet_n[j];
                    vet_n[j] = auxInt;
                    auxFloat = vet_prec[i];
                    vet_prec[i] = vet_prec[j];
                    vet_prec[j] = auxFloat;
                }
            }
        }
    }
    else{
        for (int i=0; i<tam-1; i++){
            for (int j=i; j<tam; j++){
                if(vet_ord[i] < vet_ord[j]){
                    auxInt = vet_ord[i];
                    vet_ord[i] = vet_ord[j];
                    vet_ord[j] = auxInt;
                    auxInt = vet_n[i];
                    vet_n[i] = vet_n[j];
                    vet_n[j] = auxInt;
                    auxFloat = vet_prec[i];
                    vet_prec[i] = vet_prec[j];
                    vet_prec[j] = auxFloat;
                }
            }
        }
        
    }
}

void bubble_sortFLOAT(int vet_ord[], int vet_n[], float vet_prec[], int tam, int ordem){
    int auxInt;
    float auxFloat;
    if (ordem==0){
        for (int i=0; i<tam-1; i++){
            for (int j=i; j<tam; j++){
                if((vet_prec[i] > vet_prec[j] || vet_prec[i]==-1) && vet_prec[j]!=-1){
                    auxInt = vet_ord[i];
                    vet_ord[i] = vet_ord[j];
                    vet_ord[j] = auxInt;
                    auxInt = vet_n[i];
                    vet_n[i] = vet_n[j];
                    vet_n[j] = auxInt;
                    auxFloat = vet_prec[i];
                    vet_prec[i] = vet_prec[j];
                    vet_prec[j] = auxFloat;
                }
            }
        }
    }
    else{
        for (int i=0; i<tam-1; i++){
            for (int j=i; j<tam; j++){
                if(vet_prec[i] < vet_prec[j]){
                    auxInt = vet_ord[i];
                    vet_ord[i] = vet_ord[j];
                    vet_ord[j] = auxInt;
                    auxInt = vet_n[i];
                    vet_n[i] = vet_n[j];
                    vet_n[j] = auxInt;
                    auxFloat = vet_prec[i];
                    vet_prec[i] = vet_prec[j];
                    vet_prec[j] = auxFloat;
                }
            }
        }
        
    }
}

void ordenacao(int vet_cod[], int vet_qt[], float vet_prec[], int tam, int tipo){
    int ordem;
    printf("Digite a ordem [0=crescente 1=decrescente]: ");
    scanf("%d", &ordem);
    while(ordem!=0 && ordem!=1){
        printf("Codigo digitado invalido. Digite novamente: ");
        scanf("%d", &ordem);
    }
    switch (tipo){
        case 1:
            bubble_sortINT(vet_cod, vet_qt, vet_prec, tam, ordem);
            printf("\n>Situacao do estoque:\n ");
            mostra_estoque(vet_cod, vet_qt, vet_prec, tam);
            break;
        case 2:
            bubble_sortINT(vet_qt, vet_cod, vet_prec, tam, ordem);
            printf("\n>Situacao do estoque:\n ");
            mostra_estoque(vet_cod, vet_qt, vet_prec, tam);
            break;
        case 3:
            bubble_sortFLOAT(vet_cod, vet_qt, vet_prec, tam, ordem);
            printf("\n>Situacao do estoque:\n ");
            mostra_estoque(vet_cod, vet_qt, vet_prec, tam);
            break;
        default:
            //nao sera necessario
            break;
    }
}

void atualizacao(int vet_cod[], float vet_prec[], int vet_qt[], int tam){
    int a, cod, pos, novaquant, continuar, pos1, pos2, tipo;
    float novoprec, taxa;
    a = menu_atualizacao();
    switch(a){
        case 1:
            printf(">Opcao 1: Atualizar produto\n");
            printf(">Digite o codigo do produto a ser atualizado: ");
            scanf("%d", &cod);
            pos = achar_produto(vet_cod, tam, cod);
            if (pos==-1){
                printf(">Alerta!!! Produto nao encontrado!!!\n");
                printf("Atualizacao nao pode ser feita...");
            }
            else{
                printf(">Digite a quantidade nova do produto(-1=> nao alterar): ");
                scanf("%d", &novaquant);
                if (novaquant<0){
                    printf(">Quantidade nao alterada.");
                }
                else{
                    vet_qt[pos] = novaquant;
                    printf(">Quantidade alterada!");
                }
                printf("\n>Digite o novo preco do produto: ");
                scanf("%f", &novoprec);
                if (novoprec<0){
                    printf(">Quantidade nao alterada.");
                }
                else{
                    vet_prec[pos] = novoprec;
                    printf(">Quantidade alterada.");
                }
            }
            printf("\n>Situacao do estoque:\n ");
            mostra_estoque(vet_cod, vet_qt, vet_prec, tam); 
            printf("\n>Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        case 2:
            printf(">Opcao 2: Trocar produtos\n");
            printf(">Digite posicao do primeiro produto: ");
            scanf("%d", &pos1);
            while(pos1>=tam || pos1<0){
                printf("Posicao inexistente...\n");
                printf("Digite uma posicao valida: ");
                scanf("%d", &pos1);
            }
            printf(">Digite a posicao do segundo produto: ");
            scanf("%d", &pos2);            
            while(pos2>=tam || pos2<0 || pos2==pos1){
                printf("Posicao inexistente ou igual a primeira...\n");
                printf("Digite uma posicao valida: ");
                scanf("%d", &pos2);
            }
            troca(vet_cod, vet_prec, vet_qt, pos1, pos2);
            printf("\nSituacao atual do estoque: \n");
            mostra_estoque(vet_cod, vet_qt, vet_prec, tam);
            printf(">Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        case 3:
            printf(">Opcao 3: Aplicar taxa\n");
            printf("Digite a taxa a ser aplicada nos produtos (%%): ");
            scanf("%f", &taxa);
            aplica_taxa(vet_prec, taxa, tam);
            printf("\nSituacao atual do estoque: \n");
            mostra_estoque(vet_cod, vet_qt, vet_prec, tam);
            printf(">Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        case 4:
            printf(">Opcao 4: Ordenar estoque:\n");
            tipo = menu_ordenacao();
            ordenacao(vet_cod, vet_qt, vet_prec, tam, tipo);
            printf(">Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
        case 5:
            printf(">Opcao 5: Voltar\n");
            printf(">Digite 1 para continuar: ");
            scanf("%d", &continuar);
            break;
    }
    system("cls");
}

int menu_remocao(){
	int op;
	printf("U>Operacoes: \n");
	printf("|   1. Deletar produto por codigo\n");
	printf("|   2. Deletar produtos por faixa\n");
	printf("|   3. Limpar estoque\n");
	printf("|   4. Voltar\n");
	printf(">Selecione uma operacao: ");
	scanf("%d", &op);
    while (op!=1 && op!=2 && op!=3 && op!=4){
        printf(">Codigo digitado eh invalido...\n");
        printf(">Selecione uma operacao: ");
        scanf("%d", &op);
    }
    system("cls");
    return op; 
}

int remove_prod(int vet_cod[], int vet_qt[], float vet_prec[], int tam, int cod){
    for (int i=0; i<tam; i++){
        if(vet_cod[i]==cod){
            vet_cod[i] = -1;
            vet_qt[i] = -1;
            vet_prec[i] = -1;
            return 1;
        }
    }
    return -1;
}

int deleta_faixa(float vet_prec[], int vet_cod[], int vet_qt[], float v1, float v2, int tam){
    int qts=0;
    for (int i=0; i<tam; i++){
        if (vet_prec[i]>=v1 && vet_prec[i]<=v2){
            vet_prec[i] = -1;
            vet_cod[i] = -1;
            vet_qt[i] = -1;
            qts++;
        } 
    }
    return qts;
}

int limpa_estoque(int vet_cod[], float vet_prec[], int vet_qt[], int tam){
    int qts=0;
    for (int i=0; i<tam; i++){
        if(vet_cod[i]!=-1){
            vet_cod[i] = -1;
            vet_prec[i] = -1;
            vet_qt[i] = -1;
            qts++;
        }
    }
    return qts;
}

void remocao(int vet_cod[], float vet_prec[], int vet_qt[], int tam){
    int a, cod, sit, continuar, qts;
    float v1, v2;
    a = menu_remocao();
    switch(a){
        case 1:
            printf(">Opcao 1: Deletar produto por codigo\n");
            printf(">Digite o codigo do produto: ");
            scanf("%d", &cod);
            sit = remove_prod(vet_cod, vet_qt, vet_prec, tam, cod);
            if (sit==-1){
                printf(">Codigo nao encontrado. Remocao nao foi efetuada!!!\n");
            }
            else{
                printf(">Remocao efetuada.\n");
                printf(">Situacao do estoque: \n");
                mostra_estoque(vet_cod, vet_qt, vet_prec, tam);
            }
            break;
        case 2:
            printf(">Opcao 2: Deletar produtos por faixa: \n");
            printf(">Digite o primeiro valor parametro: ");
            scanf("%f", &v1);
            while(v1<0){
                printf("Valor invalido. Digite um valor positivo: ");
                scanf("%f", &v1);
            }
            printf(">Digite o segundo valor parametro: ");
            scanf("%f", &v2);
            while (v2<=v1){
                printf(">O segundo parametro nao pode ser maior que o primeiro...");
                printf(">Digite novamente: ");
                scanf("%f", &v2);
            }
            qts = deleta_faixa(vet_prec, vet_cod, vet_qt, v1, v2, tam);
            printf("Foram deletados %d itens do estoque\n", qts);
            mostra_estoque(vet_cod, vet_qt, vet_prec, tam);
            break;
        case 3:
            printf(">Opcao 3: Limpar estoque\n");
            qts = limpa_estoque(vet_cod, vet_prec, vet_qt, tam);
            printf(">Foram deletados %d itens do estoque\n", qts);
            printf(">Situacao do estoque: \n");
            mostra_estoque(vet_cod, vet_qt, vet_prec, tam);
            break;
        case 4:
            printf(">Opcao 4: Voltar\n");
            break;
        default:
            //nao sera preciso
            break;
    }
    printf(">Digite 1 para continuar: ");
    scanf("%d", &continuar);
    system("cls");
}

int main(){
    int cod_prod[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int quant_prod[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    float preco_prod[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    char a=0;
    while (a!='e' && a!='E'){
        a = menu_inicial();
        switch(a){
            case 'c': case 'C':
                criacao(cod_prod, preco_prod, quant_prod, 10);
                break;
			case 'r': case 'R':
				consulta(cod_prod, preco_prod, quant_prod, 10);
                break; 
            case 'u': case 'U':
                atualizacao(cod_prod, preco_prod, quant_prod, 10);
                break;
            case 'd': case 'D':
                remocao(cod_prod, preco_prod, quant_prod, 10);
                break;
            case 'e': case 'E':
                printf("Programa encerrado!!!");
                break;
            default:
                //nao ira precisar
                break;
        }
    }
    return 0;
}
