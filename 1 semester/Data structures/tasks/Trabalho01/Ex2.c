#include <stdio.h>

#define TAMANHO_DO_VETOR 5

struct retangulo{
    float base;
    float altura;
    float perimetro;
    float area;
};

typedef struct retangulo Retangulo;

void ler_retangulos(Retangulo ret[], int tam){
    for (int i = 0; i < tam; i++){
        printf("Base %d: ", i + 1);
        scanf("%f", &ret[i].base); 
        printf("Altura %d: ", i + 1);
        scanf("%f", &ret[i].altura);
    }
}

void calculaPeriArea(Retangulo ret[], int tam){
    for (int i = 0; i < tam; i++){
        ret[i].perimetro = ret[i].base * 2 +  ret[i].altura * 2;
        ret[i].area = ret[i].base * ret[i].altura;
    }
}

void imprime_ret(Retangulo ret[], int tam){
    for (int i = 0; i < tam; i++){
        printf("Retangulo %d\n", i+1);
        printf("Perimetro: %.2f\n", ret[i].perimetro);
        printf("Area: %.2f\n\n", ret[i].area);
    }
}

int main(void){
    Retangulo ret[5];
    ler_retangulos(ret, TAMANHO_DO_VETOR);
    calculaPeriArea(ret, TAMANHO_DO_VETOR);
    imprime_ret(ret, TAMANHO_DO_VETOR);
}