#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#define TAM 10
#define NUM_THREADS 8

/*
    IDEIA DO ALGORITIMO:
    Vetor eh separado em X particoes em que X eh o numero de threads,
    definido em NUM_THREADS. Apos, em threads separadas cada uma das 
    particoes eh ordenada com quicksort. Quando todas as threads
    terminarem o trabalho, as particoes do vetor sao intercaladas,
    tornando o vetor totalmente ordenado.
*/

// Struct para passar argumentos para uma thread
typedef struct arg_struct {
    int* vet;
    int ini;
    int fim;
    int pri;
}args;

// Funcao recursiva QuickSort
void* quickSort(void* argumentos)
{
    // recebendo argumentos
    int i, j, x, y;
    args *arg = (args*) argumentos;
    int left = arg->ini;
    int right = arg->fim;
    int* a = arg->vet;
    i = left;
    j = right;
    x = a[(left + right) / 2];


    while (i <= j)
    {
        while (a[i] < x && i < right)
        {
            i++;
        }
        while (a[j] > x && j > left)
        {
            j--;
        }
        if (i <= j)
        {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    // preparando argumentos para serem passados para as funções
    args b;
    b.vet = a;
    b.ini = left;
    b.fim =  j;
    b.pri = 0;

    // preparando argumentos para serem passados para as funções
    args c; 
    c.vet = a;
    c.ini = i;
    c.fim = right;
    c.pri = 0;

    if (j > left)
    {
        quickSort(&b);
    }
    if (i < right)
    {
        quickSort(&c);
    }
    return NULL;
}

// Funcao que printa o vetor
void mostra(int *vet, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%i\n", vet[i]);
    }
    printf("\n");
}


// Funcao que intercala dois vetores
void merge(int arr[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
}

// Funcao principal da ordenacao
void ordena(int *vet, int tam, int threads)
{
    // subdivide o vetor de acordo com o numero de threads
    int subdivisao = (tam / threads);
    //cria threadIds e bota num vetor
    pthread_t threadArray[threads];
    // cria vetor de argumentos a serem passados para as threads
    args a[threads];

    int j = 0;
    int i = 0;
    // chama o quicksort em uma nova thread para cada particao do vetor
    for (j = 0; j < threads; j++)
    {
        if(j == threads - 1) {
            a[j].fim = tam - 1;
        }
        else {
            a[j].fim = i + subdivisao - 1;
        }
        a[j].vet = vet;
        a[j].ini = i;
        a[j].pri = 1;
        pthread_create(&(threadArray[j]), NULL, &(quickSort), (void*)(&a[j]));
        i+= subdivisao;
    }

    // laco feito para esperar threads terminarem
    for(int i = 0; i < threads; i++)
    {
        pthread_join(threadArray[i], NULL);
    }
    
    // intercalacao entre as particoes dos vetores ordenadas por cada thread
    for(i = 1; i < threads; i ++) {
        merge(vet, 0, subdivisao*i - 1, subdivisao*(i+1) - 1);
    }

    // se o sobrarem elementos do vetor nao intercalados, eles sao intercalados agora
    if(tam % threads != 0) {
        merge(vet, 0, subdivisao*i - 1, tam - 1);
    }
}

int main()
{
    int vet[] = {1, 5, 7, 1, 4, 3, 1, 2, 5, 8};

    //Criando vetor aleatorio de TAM para teste
    /*
    int* vet = (int*) malloc (sizeof(int) * TAM);
    srand(time(NULL));
    for(int i=0; i < TAM; i++) {
        vet[i] = rand()%TAM;
    }
    */

    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    ordena(vet, TAM, NUM_THREADS);
    
    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;

    mostra(vet, TAM);
    printf("Tempo: %lf segundos.\n", elapsed);
}
