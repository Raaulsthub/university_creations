#include <stdio.h>
#include <stdbool.h>

int cardapioF(){
    int escolha;
    printf("=========================");
    printf("\n|| CARDAPIO DE FUNCOES ||");
    printf("\n=========================");
    printf("\n\n  |1| Sequencia");
    printf("\n  |2| Comprimento");
    printf("\n  |3| Quebra");
    printf("\n  |4| Sair do programa");
    printf("\n\n   =>Sua escolha: ");
    scanf("%d", &escolha);
    while(escolha!=1 && escolha!=2 && escolha!=3 && escolha!=4){
    	printf("\n   =>Opcao invalida!! Digite novamente: ");
		scanf("%d", &escolha);
	}
	system("cls");
    return escolha;
}

int sequencia(){
    int n=-1, i, v, aux, qts=1;
    printf("\n\n=> Digite o tamanho da sequencia: ");
    scanf("%d", &n);
    while(n<=0){
        printf("\n=> Numero invalido! Digite o tamanho da sequencia: ");
        scanf("%d", &n);
    }
    printf("\n=> Digite sua senquencia de %d numeros: ", n);
    printf("\n[ * Se tiverem valores repetidos, a repeticao DEVE ocorrer de forma consecutiva * ]\n\n");
    printf("\n=> ");
    scanf("%d", &v);
    aux = v;
    for (i=0; i<n-1; i++){
        printf("\n=> ");
        scanf("%d", &v);
        if (v!=aux){
            qts++;
        }
        aux = v;
    }
    return qts;
}

void comprimento(int n){
    int i, x, aux, mseq=0, seq=1;
    printf("=> Digite um numero: ");
    scanf("%d", &x);
    aux = x;
    for (i=0; i<=(n-2); i++){
        printf("=> Digite um numero: ");
        scanf("%d", &x);
        if (x>aux){
            seq++;
        }
        else{
            if(seq>mseq){
                mseq = seq;
            }
            seq = 1;
        }
        aux = x;
    }
    if(seq>mseq){
        mseq = seq;
    }
    printf("\n=> Maior comprimento de um segmento crescente: %d", mseq);
}

bool quebra(x, y, z){
    int aux=1;
    while(aux<z){
        aux = aux * 10;
    }
    if ((x/aux)==y){
        if ((x-(y*aux))==z){
            return true;
        }
    }
    return false;
}



int main(){
    int a, x, n, n1, n2, sair=0, ctn;
    bool r;
    do{
        system("cls");
        a = cardapioF();
        switch(a){
            case 1:
                printf("=============");
                printf("\n|| OPCAO 1 ||");
                printf("\n=============");
                printf("\n\n=> SEQUENCIA");
                x = sequencia();
                printf("\n=>Existem %d numeros distintos na sequencia!", x);
                break;
            case 2:
                printf("=============");
                printf("\n|| OPCAO 2 ||");
                printf("\n=============");  
                printf("\n\n=> COMPRIMENTO");
                printf("\n\n=> Digite o tamanho da sequencia a ser escrita: ");
                scanf("%d", &x);
                while(x<=0){
                    printf("\n=> Numero invalido!!! Digite novamente: ");
                    scanf("%d", &x);
                }
                printf("\n");
                comprimento(x);
                break;
            case 3:
                printf("=============");
                printf("\n|| OPCAO 2 ||");
                printf("\n=============");  
                printf("\n\n=> QUEBRA");
                printf("\n\n=> Digite um numero positivo: ");
                scanf("%d", &n);
                while(n<=0){
                    printf("\n=> Valor invalido. Digite novamente: ");
                    scanf("%d", &n);
                }
                printf("\n\n=> Digite outro numero positivo: ");
                scanf("%d", &n1);
                while(n1<=0){
                    printf("\n=> Valor invalido. Digite novamente: ");
                    scanf("%d", &n1);
                }
                printf("\n\n=> Digite outro numero positivo: ");
                scanf("%d", &n2);
                while(n2<=0){
                    printf("\n=> Valor invalido. Digite novamente: ");
                    scanf("%d", &n2);
                }
                r = quebra(n, n1, n2);
                if (r==true){
                    printf("\n=> %d pode ser quebrado em %d e %d!!!", n, n1, n2);
                }
                else{
                    printf("\n=> %d Nao pode ser quebrado em %d e %d!!!", n, n1, n2);
                }
                break;
            case 4:
                sair = 1;
                break;
            default:
                //nao eh preciso, devido a teste na funcao cardapio.
                sair = 0;
        }
        printf("\n\n=> Digite 1 para continuar: ");
        scanf("%d", &ctn);
    }while(sair!=1);
    system("cls");
    printf("=> PROGRAMA FINALIZADO.");
    return 0;
}
