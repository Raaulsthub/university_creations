#include <stdio.h>
#include <stdlib.h>

int main(){
	srand(time(NULL));
	//seta uma seed para randomizar diferentemente a cada execu��o
	int c1, c2, vict1, def1, minha_carta, vict2, def2;
	float pv1, pv2, pd1, pd2;
	//Op��o um -> N�o trocando a carta
	//Valor 0 -> Estar com o A's de espadas
	for (c1=0; c1<1000000; c1++){
		minha_carta = rand() % 3;
		if (minha_carta == 0)
			vict1 = vict1 + 1;
		else
			def1 = def1 + 1;
	}
	//Calculando porcentagens
	pd1 = (float) def1/c1;
	pd1 = pd1 * 100; 
	pv1 = (float) vict1/c1;
	pv1 = pv1 * 100;
	//Op��o dois -> Trocando a carta
	//Valor 0 -> Estar com o A's de espadas
	for (c2=0; c2<1000000; c2++){
		minha_carta = rand() % 3;
		if (minha_carta == 0)
			def2 = def2 + 1;
		else
			vict2 = vict2 + 1;
	}
	//Calculando porcentagens
	pd2 = (float) def2/c2;
	pd2 = pd2 * 100; 
	pv2 = (float) vict2/c2;
	pv2 = pv2 * 100;
	printf(">Estrategia 1 (sem mudanca de carta): ");
	printf("\n	Partidas jogadas: %d", c1);
	printf("\n	Partidas ganhas: %d", vict1);
	printf("\n	Partidas perdidas: %d", def1);
	printf("\n	%% de derrotas: %.2f%%", pd1);
	printf("\n	%% de vitorias: %.2f%%", pv1);
	printf("\n\n>Estrategia 2 (com mudanca de carta): ");
	printf("\n	Partidas jogadas: %d", c2);
	printf("\n	Partidas ganhas: %d", vict2);
	printf("\n	Partidas perdidas: %d", def2);
	printf("\n	%% de derrotas: %.2f%%", pd2);
	printf("\n	%% de vitorias: %.2f%%", pv2);
	if (vict1>vict2)
		printf("\n\nRecomendacao do algoritimo: N�o mudar a carta!");
	else
		printf("\n\nRecomendacao do algoritimo: Mudar a carta!");
}

