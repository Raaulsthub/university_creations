#include <stdio.h>

#define TAMANHO 500

struct usuario{
    char sexo;
    int idade;
    int qtdade;
};

typedef struct usuario Usuario;

void leVetor(int tam, Usuario *vet){
    for (int i = 0; i < tam; i++){
        printf("\n USUARIO %d\n\n", i + 1);
        printf("Digite seu sexo [m/f]: ");
        scanf(" %c", &vet[i].sexo);
        printf("Digite sua idade: ");
        scanf("%d", &vet[i].idade);
        printf("Digite a quantidade de livros lidos em 2020: ");
        scanf("%d", &vet[i].qtdade);
    }
}

int calculaQtidadeLivros(int tam, Usuario *vet){
    int qt = 0;
    for (int i = 0; i < tam; i++){
        if(vet[i].idade < 10){
            qt += vet[i].qtdade;
        }
    }
    return qt;
}

int calculaQtidadeMulheres(int tam, Usuario *vet){
    int qt = 0;
    for (int i = 0; i < tam; i++){
        if(vet[i].sexo == 'f' && vet[i].qtdade >= 5){
            qt++;
        }
    }
    return qt;
}

int main(){
    Usuario pessoas[TAMANHO];
    int qtidadeL, qtidadeM;
    leVetor(TAMANHO, pessoas);
    qtidadeL = calculaQtidadeLivros(TAMANHO, pessoas);
    qtidadeM = calculaQtidadeMulheres(TAMANHO, pessoas);
    printf("\n\nA quantidade total de livros lidos por menores de 10 anos foi %d\n", qtidadeL);
    printf("A quantidade de mulheres que leram 5 livros ou mais foi %d\n\n", qtidadeM);
    return 0;
}