#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define TAM 50

void titulo(){
    printf("||===================||\n");
    printf("|| CRIPTOGRAFIA LAB1 ||\n");
    printf("||===================||\n\n");
}

char menu_codificacao(){
    char op;
    printf("C. Cofificacao\n");
    printf("D. Decodificacao\n");
    printf("S. Encerrar programa e sair\n");
    printf("=> Digite sua escolha: ");
    scanf(" %c", &op);
    while (op!='c' && op!='C' && op!='d' && op!='D' && op!='s' && op!='S'){
        printf("=> Codigo invalido... Digite novamente a opcao escolhida: ");
        scanf(" %c", &op);
	}
	system("cls");
    return op;
}

void zenitPolar(char s[]){
    char zenit[] = "zenitZENIT", polar[] = "polarPOLAR";
    for (int i = 0; s[i] != '\0'; i++){
        for (int j=0; zenit[j] != '\0'; j++){
            if (s[i] == zenit[j]){
                s[i] = polar[j];
            } 
            else{
                if (s[i] == polar[j]){
                    s[i] = zenit[j];
                }
            }
        }
    }
}

void repeticoes(char s[]){
    char sobreposto, corrente, aux[100], aux0[100];
    int k, j, i = 0, vezes, itr = 0;
    while (i < strlen(s)){
        if ((s[i] >= 48 && s[i] <= 57) || (s[i] == '*')){
            aux0[itr] = '*';
            aux0[itr + 1] = s[i];
            itr = itr + 2;
        }
        else{
            aux0[itr] = s[i];
            itr++;
        }
        i++;
    }
    aux0[itr] = '\0';
    strcpy(s, aux0);
    i = 0;
    itr = 0;
    while (i < strlen(s)){
        vezes = 0;
        for (j = i; j < strlen(s); j++){
            if (s[j] != s[i]){
                break;
            }
            vezes++;
        }
        if ((vezes > 1) && (s[i] != '*')){
            aux[itr] = vezes + 48;
            aux[itr + 1]  = s[i];
            itr = itr + 2;
            i = i + vezes;
        }
        else{
            aux[itr] = s[i];
            itr++;
            i++;
        }
    }
    aux[itr] = '\0';
    itr = 0;
    i = 0;
    strcpy(s, aux); 
}

void cesar(char s[]){
    char alfa[] = "abcdefghijklmABCDEFGHIJKLM", beta[] = "nopqrstuvwxyzNOPQRSTUVWXYZ";
    for (int i = 0; s[i] != '\0'; i++){
        for (int j=0; alfa[j] != '\0'; j++){
            if (s[i] == alfa[j]){
                s[i] = beta[j];
            }
            else if (s[i] == beta[j]){
                s[i] = alfa[j];
            }
        }
    }
}

void codifica(char s[]){
    int continuar;
    printf("=> PASSO 1: Codificando em ZENIT POLAR... ");
    zenitPolar(s);
    printf("\n=> Passo 1 concluido. Digite 1 para ver a string atual: ");
    scanf("%d", &continuar);
    printf("=> ");
    puts(s);
    printf("=> PASSO 2: Codificando por repeticoes... ");
    repeticoes(s);
    printf("\n=> Passo 2 concluido. Digite 1 para ver a string atual: ");
    scanf("%d", &continuar);
    printf("=> ");
    puts(s);
    printf("=> PASSO 3: Codificando em CIFRA DE CESAR... ");
    cesar(s);
    printf("\n=> Passo 3 concluido. Digite 1 para ver a string final: ");
    scanf("%d", &continuar);
    printf("=> ");
    puts(s);
}

void decodificar_repeticoes(char s[]){
    char copia[100];
    int i = 0, j, rep, itr = 0;
    while (i<strlen(s)){
        if (s[i]>=48 && s[i]<=57){
            if(s[i-1] != '*'){
                switch(s[i]){
                    case '2':
                        rep = 2;
                        break;
                    case '3':
                        rep = 3;
                        break;
                    case '4':
                        rep = 4;
                        break;
                    case '5':
                        rep = 5;
                        break;
                    case '6':
                        rep = 6;
                        break;
                    case '7':
                        rep = 7;
                        break;
                    case '8':
                        rep = 8;
                        break;
                    case '9':
                        rep = 9;
                        break;
                    default:
                        rep = 10;
                        break;
                }
                for (j = 0; j < rep; j++){
                    copia[itr] = s[i + 1];
                    itr++;
                }
                i = i + 2;
            }
            else{
                copia[itr] = s[i];
                itr++;
                i++;
            }
        }
        else{
            copia[itr] = s[i];
            itr++;
            i++;
        }
    }
    copia[itr] = '\0';
    itr = 0;
    i = 0;
    while (i < strlen(copia)){
        if (copia[i] == '*'){
            s[itr] = copia[i+1];
            i = i + 2;
        }
        else{
            s[itr] = copia[i];
            i++;
        }
        itr++;
    }
    s[itr] = '\0';
}

void decodifica(char s[]){
    int continuar;
    printf("=> PASSO 1: Decodificando em CIFRA DE CESAR... ");
    cesar(s);
    printf("\n=> Passo 1 concluido. Digite 1 para ver a string atual: ");
    scanf("%d", &continuar);
    printf("=> ");
    puts(s);
    printf("=> PASSO 2: Decodificando por repeticoes... ");
    decodificar_repeticoes(s);
    printf("\n=> Passo 2 concluido. Digite 1 para ver a string atual: ");
    scanf("%d", &continuar);
    printf("=> ");
    puts(s);
    printf("=> PASSO 3: Decodificando em ZENIT POLAR... ");
    zenitPolar(s);
    printf("\n=> Passo 3 concluido. Digite 1 para ver a string final: ");
    scanf("%d", &continuar);
    printf("=> ");
    puts(s);
}

int main(){
    char op, string[TAM];
    int continuar;
    while(op!='S' && op!='s'){
        titulo();
        op = menu_codificacao();
        switch (op){
            case 'c': case 'C':
                titulo();
                printf("=> OPCAO C: CODIFICACAO\n");
                printf("=> Digite a string a ser codificada, que deve conter apenas alfanumericos e asteriscos: ");
                fflush(stdin);
                fgets(string, sizeof(string), stdin);
                if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = '\0';
                codifica(string);
                break;
            case 'd': case 'D':
                titulo();
                printf("=> OPCAO D: DECODIFICACAO\n");
                printf("=> Digite a string a ser decodificada, que deve conter apenas alfanumericos e asteriscos: ");
                fflush(stdin);
                fgets(string, sizeof(string), stdin);
                if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = '\0';
                decodifica(string);
                break;
            case 's': case 'S':
                titulo();
                printf("=> OPCAO S: SAIR DO PROGRAMA\n");
                break;
            default:
                //nao necessario
                break;
        }
        printf("=> Digite 1 para continuar: ");
        scanf("%d", &continuar);
        system("cls");
    }
    return 0;
}