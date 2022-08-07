#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct triangulo {
    int ladoA;
    int ladoB;
    int ladoC;
    char tipo[20];
    bool ehTriangulo;
} Triangulo;

Triangulo verificarTriangulo (Triangulo tri) {
    if ((tri.ladoA < tri.ladoB + tri.ladoC) && (tri.ladoB < tri.ladoA + tri.ladoC) && (tri.ladoC < tri.ladoA + tri.ladoB)) {
        tri.ehTriangulo = true;
        if (tri.ladoA == tri.ladoB && tri.ladoB == tri.ladoC) {
            strcpy(tri.tipo, "Equilatero");
        } else if (tri.ladoA != tri.ladoB && tri.ladoB != tri.ladoC && tri.ladoA != tri.ladoC) {
            strcpy(tri.tipo, "Escaleno");
        } else {
            strcpy(tri.tipo, "Isosceles");
        }
    } else {
        tri.ehTriangulo = false;
    }
    return tri;
}

int main() {
    Triangulo tri;
    printf("Digite um valor inteiro para o lado A: ");
    scanf("%d", &tri.ladoA);
    printf("Digite um valor inteiro para o lado B: ");
    scanf("%d", &tri.ladoB);
    printf("Digite um valor inteiro para o lado C: ");
    scanf("%d", &tri.ladoC);
    tri = verificarTriangulo(tri);
    if (tri.ehTriangulo) {
        printf("E um Triangulo do tipo %s.", tri.tipo);
    } else {
        printf("Nao e um Triangulo.");
    }
    return 0;
}