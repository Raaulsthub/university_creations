#include <stdio.h>

float pow (float base, int expo) {
    float res = 1;
    for (int i = expo; i > 0; i--) {
        res *= base;
    }
    return res;
}

void calc_esfera (float r, float *area, float *volume) {
    *area = 4 * pow(r, 2);
    *volume = 4 * pow(r, 3) / 3;
}

int main () {
    float r, area, volume;
    printf("Digite o raio desejado: ");
    scanf("%f", &r);
    calc_esfera (r, &area, &volume);
    printf("Area: %.2f \nVolume: %.2f", area, volume);
    return 0;
}