#include <stdio.h>
#include <stdbool.h>

typedef struct aluno {
    float nota1;
    float nota2;
    int aulasAssistidas;
    float media;
    bool status;
} Aluno;

typedef struct disciplina {
    Aluno vet[5];
    int aulasMinistradas;
} Disciplina;

Disciplina readInfo (Disciplina dis) {
    printf("Digite o numero de aulas ministradas na disciplina: ");
    scanf("%d", &dis.aulasMinistradas);
    for (int i = 0; i < 5; i++)
    {
        printf("\nDigite a primeira nota do aluno %d: ", i + 1);
        scanf("%f", &dis.vet[i].nota1);
        printf("Digite a segunda nota do aluno %d: ", i + 1);
        scanf("%f", &dis.vet[i].nota2);
        printf("Digite o numero de aulas assistidas pelo aluno %d: ", i + 1);
        scanf("%d", &dis.vet[i].aulasAssistidas);
    }
    return dis;
}

Disciplina calcRes (Disciplina dis) {
    for (int i = 0; i < 5; i++)
    {
        dis.vet[i].media = (dis.vet[i].nota1 + dis.vet[i].nota2) / 2.0;
        if (dis.vet[i].media >= 6 && ((float)dis.vet[i].aulasAssistidas >= ((float)dis.aulasMinistradas * 75.0 / 100.0))) {
            dis.vet[i].status = true;
        } else {
            dis.vet[i].status = false;
        }
    }
    return dis;
}

void showRes (Disciplina dis) {
    for (int i = 0; i < 5; i++)
    {
        printf("\nResultado Aluno %d: \n", i + 1);
        printf("\nMedia Final: %.2f\n", dis.vet[i].media);
        if (dis.vet[i].status) {
            printf("Status: Aprovado\n");
        } else {
            printf("Status: Reprovado\n");
        }
    }
}

int main () {
    Disciplina dis;
    dis = readInfo (dis);
    dis = calcRes (dis);
    showRes (dis);
    return 0;
}