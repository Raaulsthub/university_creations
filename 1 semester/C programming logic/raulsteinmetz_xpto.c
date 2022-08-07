#include <stdio.h>
#include <math.h>

//Feito por Raul Steinmetz
//Compreendo que com a definição de escopo, poderia ter usado "escolha" como variável para todas as escolhas, mas achei que ficaria muito confuso.

int main(){
	char escolha1;
	printf("******************");
	printf("\n*      XPTO      *");
	printf("\n******************");
	printf("\n\n=>Menu Inicial");
	printf("\n\n a. Validação de data");
	printf("\n b. Diferença de horários");
	printf("\n c. Converção de temperatura");
	printf("\n d. Cálculo de material");
	printf("\n => Selecione uma opção: ");
	scanf("%c", &escolha1);
	if ((escolha1 == 'a') || (escolha1=='A')){
		int dia, mes, ano, escolha2;
		printf("\n\nA > Validação de data");
		printf("\n\nDia: ");
		scanf("%d", &dia);
		printf("\nMês: ");
		scanf("%d", &mes);
		printf("\nAno: ");
		scanf("%d", &ano);
		if ((mes==1) || (mes==3) || (mes==5) || (mes==7) || (mes==8) || (mes==10) || (mes==12)){
			if (dia>31){
				printf("Erro, data digitada não é válida!");
				return 0;
			}
		}
		else if ((mes==4) || (mes==6) || (mes==9) || (mes==11)){
			if(dia>30){
				printf("Erro, data digitada não é válida!");
				return 0;
			}
		}
		else if (mes==2){
			if ((ano%400==0) || ((ano%4==0) && (ano%100!=0))){
				if (dia>29){
					printf("Erro, data digitada não é válida!");
					return 0;
				}
			}
			else{
				if (dia>28){
					printf("Erro, data digitada não é válida!");
					return 0;
				}
			}
		}
		else if (mes>12){
			printf("Erro, data digitada não é válida!");
			return 0;
		}
		printf("\n\nFormatação de data");
		printf("\n\n 1. DD/MM/YYYY");
		printf("\n 2. YYYY-MM-DD");
		printf("\n 3. DD de [MÊS] de YYYY");
		printf("\n =>Escolha uma opção: ");
		scanf("%d", &escolha2);
		if (escolha2==1){
			if ((dia>=10) && (mes>=10))
				printf(" => %d/%d/%d", dia, mes, ano);
			else if ((dia>=10) && (mes<10))
				printf(" => %d/0%d/%d",dia, mes, ano);
			else if ((dia<10) && (mes>10))
				printf(" => 0%d/%d/%d", dia, mes, ano);
			else
				printf(" => 0%d/0%d/%d", dia, mes, ano);
		}
		else if (escolha2==2){
			printf(" => %d-%d-%d", ano, mes, dia);
		}
		else if (escolha2==3){
			if (mes==1)
				printf(" => %d de janeiro de %d", dia, ano);
			if (mes==2)
				printf(" => %d de fevereiro de %d", dia, ano);
			if (mes==3)
				printf(" => %d de março de %d", dia, ano);
			if (mes==4)
				printf(" => %d de abril de %d", dia, ano);
			if (mes==5)
				printf(" => %d de maio de %d", dia, ano);
			if (mes==6)
				printf(" => %d de junho de %d", dia, ano);
			if (mes==7)
				printf(" => %d de julho de %d", dia, ano);
			if (mes==8)
				printf(" => %d de agosto de %d", dia, ano);
			if (mes==9)
				printf(" => %d de setembro de %d", dia, ano);
			if (mes==10)
				printf(" => %d de outubro de %d", dia, ano);
			if (mes==11)
				printf(" => %d de novembro de %d", dia, ano);
			if (mes==12)
				printf(" => %d de dezembro de %d", dia, ano);
		}
		else{
			printf("Erro! Opção não consta no menu...");
			return 0;
		}			
	}
	else if ((escolha1 == 'b') || (escolha1=='B')){
		int h1, m1, h2, m2, horario1, horario2, diferenca, escolha3, hora, minuto;
		printf("\n\nB > Diferença de horários");
		printf("\n\n>Hora h1: ");
		scanf("%d", &h1);
		printf("\n>Minuto m1: ");
		scanf("%d", &m1);
		printf("\n>Hora h2: ");
		scanf("%d", &h2);
		printf("\n>Minuto m2: ");
		scanf("%d", &m2);
		if ((h1>24) || (h1<0) || (h2>24) || (h2<0) || (m1>59) || (m1<0) ||  (m2>59) || (m2<0)){
			printf("\nERRO! Horário informado não reconhecido.");
			return 0;
		}
		horario1 = h1*60 + m1;
		horario2 = h2*60 + m2;
		if (horario1<horario2)
			diferenca = horario2 - horario1;
		else
			diferenca = 1440 - (horario1 - horario2);//1440 é um dia em minutos	// diferença está em minutos por padrão
		printf("\n=>Formatos disponíveis");
		printf("\n 1.Padrão");
		printf("\n 2.Minutos");
		printf("\n 3.Segundos");
		printf("\n 4.Milisegundos");
		printf("\n=> Sua escolha: ");
		scanf("%d", &escolha3);
		if (escolha3==1){
			hora = diferenca/60;
			minuto = diferenca%60;
			printf("=> Diferença = %d horas e %d minutos", hora, minuto);
		}
		else if (escolha3==2)
			printf("=> Diferença = %dm", diferenca);
		else if (escolha3==3)
			printf("=> Diferença = %ds", diferenca*60);
		else if (escolha3==4)
			printf("=> Diferença = %dms", diferenca*60000);
		else{
			printf("ERRO. Opção não consta no menu!");
			return 0;
		}					
	}
	else if ((escolha1=='c') || (escolha1=='C')){
		float c, f, k, r;
		int escolha4;
		printf("\n\nC > Conversão de temperatura");
		printf("\n => Temperatura(°C): ");
		scanf("%f", &c);
		printf(" Tabela de conversões possíveis: ");
		printf("\n 1. Fahrenheit");
		printf("\n 2. Kelvin");
		printf("\n 3. Rankine");
		printf("\n => Converter para opção: ");
		scanf("%d", &escolha4);
		if (escolha4==1){
			f =(c*9/5)+32;
			printf(" => %.2f°C <=> %.1f°F", c, f);
		}
		else if (escolha4==2){
			k = c + 273.15;
			printf(" => %.2f°C <=> %.2fK", c, k);
		}
		else if (escolha4==3){
			r =(c*9/5)+491.67;
			printf(" => %.2f°C <=> %.2f°R", c, r);
		}
		else{
			printf("ERRO!Opção não consta no menu!");
			return 0;
		}
	}
	else if ((escolha1 == 'd') || (escolha1 == 'D')){
		float hp, cp, tijolos, am, custo;
		int escolha5;
		printf("\n\nD > Cálculo Material");
		printf("\nAltura da parede(m): ");
		scanf("%f", &hp);
		printf("Comprimento da parede(m): ");
		scanf("%f", &cp);
		printf("=>Tabela de tijolos");
		printf("\n 1. 6 furos");
		printf("\n 2. 8 furos");
		printf("\n 3. 9 furos");
		printf("\n=> Digite a opção desejada: ");
		scanf("%d", &escolha5);
		am = hp*cp;	
		if (escolha5==1){
			tijolos = am / 0.0266;
			tijolos = ceil(tijolos);
			custo = tijolos * 0.4;
		}
		else if (escolha5==2){
			tijolos = am / 0.0361;
			tijolos = ceil(tijolos);
			custo = tijolos * 0.7805;
		}
		else if (escolha5==3){
			tijolos = am / 0.0551;
			tijolos = ceil(tijolos);
			custo = tijolos * 0.89999;
		}
		else{
			printf("ERRO! Opção não consta no menu!");
			return 0;
		}
		printf("=> Tijolos necessários: %.0f unidades (R$%.2f)", tijolos, custo);
	}
	printf("\n*fim*");
	return 0;			
}



