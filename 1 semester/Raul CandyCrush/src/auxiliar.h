/* Esse arquivo envolve a grande maioria das funções usadas no jogo, separadas por
área e entituladas com sua função*/

#define TAM 9
#define TAMDOFUNDO 10000
#define INICIODOTAB 140
#define FIMDOTAB 770
#define LARGDASCASAS 70
#define XINFO 180
#define YINFO 50
#define XBOTAOINICIAR 300
#define YBOTAOINICIAR 350
#define X2BOTAOINICIAR 500
#define Y2BOTAOINICIAR 450
#define XBOTAOINFO 300
#define YBOTAOINFO 550
#define X2BOTAOINFO 500
#define Y2BOTAOINFO 650
#define XVOLTAR 650
#define YVOLTAR 40
#define X2VOLTAR 750
#define Y2VOLTAR 100
#define LIMITECIRCULOSANDANTES 850
#define LIMITECIRCULOSANDANTES2 -50
#define PARAMETRODOCES 35.5
#define RAIODOCES 30
#define LADOSDOCES 30
#define BORDASINICIAL1 50
#define BORDASINICIAL2 750
#define VELDOSCIRCULOS 1
#define TAM_DOS_VETORES 100
#define TIME_SLEEP 1000
#define GAMEOVER_1 100
#define GAMEOVER_2 700
#define MOVIMENTOS 10
#define LADOS_CIRCULO 40
#define RAIOS_CIRCULO 30
#define RESETX 60
#define RESETY 700
#define CANDYX1 380
#define CANDYY1 45
#define CANDYX2 530
#define CANDYY2 95

float corfade = 1; //cores fade
int mx, my; //Coordenadas do mouse
int pontos = 0; //Pontuação do jogador
int doces[TAM][TAM];//Matriz de doces
int manipulado_linha, manipulado_coluna;//Identificadores da peça manipulada
int vetor_linhas[TAM_DOS_VETORES], vetor_colunas[TAM_DOS_VETORES]; //Vetores de eliminação
int idx = 0; //Controla as informações dos vetores de eliminação
int primeiroclick = 0; //Variavel que evita um bug
int troca_linha, troca_coluna; //Variavel controladora de trocas
int pontos_final = 0; //Variavel utilizada para animação no gameover
int reset = 0; //Varivel que controla o reset


//FUNÇÕES DE CORES
//
//

//Cores 'fade'
void fade()
{
    color(corfade);
    corfade += 0.1;
    if (corfade > 10)
    {
        corfade = 1;
    }
}

//Cor azul fraco
void azul_fraco()
{
    color(0.592, 0.666, 0.847);
}

//Cor azul forte
void azul_forte()
{
    color(0.0, 0.1, 0.4);
}



//FUNCÕES DE CENÁRIO
//
//

//Cor do fundo
void cor_fundo()
{
    azul_forte();
    rectFill(0, 0, TAMDOFUNDO, TAMDOFUNDO);
}

//Tabuleiro(parte gráfica)
void tabuleiro()
{
    float lx = INICIODOTAB + LARGDASCASAS, ly = INICIODOTAB + LARGDASCASAS;
    azul_fraco();
    rectFill(INICIODOTAB-10, INICIODOTAB-10, FIMDOTAB+10, FIMDOTAB+10);
    color(0.0, 0.0, 0.15);
    rectFill(INICIODOTAB, INICIODOTAB, FIMDOTAB, FIMDOTAB);
    azul_fraco();
    for(int i = 0; i < TAM-1; i++)
    {
        line(INICIODOTAB, ly, FIMDOTAB, ly);
        ly = ly + LARGDASCASAS;
    }
    for(int i = 0; i < TAM-1; i++)
    {
        line(lx, INICIODOTAB, lx, FIMDOTAB);
        lx = lx + LARGDASCASAS;
    }
}

//HUD
void hud(int movimentos_restantes)
{
    fade();
    text(10, 40, "PONTOS-> ");
    text(100, 40, pontos);
    text(10, 20, "MOVS RESTANTES -> ");
    text(190, 20, movimentos_restantes);
    rect(CANDYX1, CANDYY1, CANDYX2, CANDYY2);
    rect(CANDYX1 - 6, CANDYY1 - 6, CANDYX2 + 6, CANDYY2 + 6);
    text (400, 75, "CANDY CRUSH");
    azul_fraco();
    circleFill(RESETX, RESETY, RAIODOCES+30, LADOSDOCES);
    fade();
    text(RESETX - 25, RESETY + 5, "RESET");
}

//Menu inicial
void menu_inicial()
{
    cor_fundo();
    azul_fraco();
    rectFill(BORDASINICIAL1, BORDASINICIAL1, BORDASINICIAL2, BORDASINICIAL2);
    azul_forte();
    rectFill(BORDASINICIAL1+25, BORDASINICIAL1+25, BORDASINICIAL2-25, BORDASINICIAL2-25);
    fade();
    rect(300, 140, 500, 240);
    text(345, 195, "CANDY CRUSH");
    color(0.592, 0.666, 0.847);
    rectFill(XBOTAOINICIAR , YBOTAOINICIAR, X2BOTAOINICIAR, Y2BOTAOINICIAR);
    azul_forte();
    text(375, 405, "JOGAR");
    azul_fraco();
    rectFill(XBOTAOINFO , YBOTAOINFO, X2BOTAOINFO, Y2BOTAOINFO);
    azul_forte();
    text(355, 605, "COMO JOGAR");
    color(0.039, 0.690, 1);
}

//Desenha os doces
void draw_doces()
{
    for(int l = 0; l < TAM; l++)
    {
        for(int c = 0; c < TAM; c++)
        {
            int cordc = INICIODOTAB + LARGDASCASAS*c;
            int cordl = INICIODOTAB + LARGDASCASAS*l;
            switch(doces[l][c])
            {
                case 1:
                    color(0.039, 0.690, 1);
                    circleFill(cordc + PARAMETRODOCES, cordl + PARAMETRODOCES, RAIODOCES, LADOSDOCES);
                    break;
                case 2:
                    color(0.631, 0.039, 1);
                    circleFill(cordc + PARAMETRODOCES, cordl + PARAMETRODOCES, RAIODOCES, LADOSDOCES-25);
                    break;
                case 3:
                    color(0.976, 0.450, 0.043);
                    circleFill(cordc + PARAMETRODOCES, cordl + PARAMETRODOCES, RAIODOCES, LADOSDOCES-26);
                    break;
                case 4:
                    color(0.298, 0.941, 0.807);
                    circleFill(cordc + PARAMETRODOCES, cordl + PARAMETRODOCES, RAIODOCES, LADOSDOCES-27);
                    break;

            }
        }
    }
}

//Como jogar
void info()
{
    cor_fundo();
    color(0.592, 0.666, 0.847);
    text(XINFO, 220, "No jogo candy crush seu objetivo princiapal");
    text(XINFO, 240, "eh formar conjuntos de doces, para que esses");
    text(XINFO, 260, "sejam eliminados em troca de pontuacao.");
    text(XINFO, 280, "Os conjuntos podem ser formados em fileiras");
    text(XINFO, 300, "ou em formato de L. O jogo eh simples, mas tome");
    text(XINFO, 320, "cuidado, os movimentos sao limitados!!! Alem disso,");
    text(XINFO, 340, "so podem ser trocados de lugar os doces que estao");
    text(XINFO, 360, "'colados', ou seja, suas posicoes nao podem diferir");
    text(XINFO, 380, "mais que uma casa!!");
    text(XINFO, 400, "DIVIRTA-SE!!!");
    rectFill(XVOLTAR, YVOLTAR, X2VOLTAR, Y2VOLTAR);
    azul_forte();
    text(670, 75, "VOLTAR!");
}


//FUNÇÕES QUE ENVOLVEM DIRETAMENTE A LOGICA DO JOGO
//
//

//Cria doces do tabuleiro
void cria_doces()
{
    srand(time(NULL));
    for(int l = 0; l < TAM; l++)
    {
        for(int c = 0; c < TAM; c++)
        {
            doces[l][c] = (rand()%4) + 1;
        }
    }
}

//Marca os doces a serem eliminados
void marca_eliminados()
{
    for(int l = 0; l < TAM; l++)
    {
        for(int c = 0; c < TAM; c++)
        {
            if (c != -1)
            {
                if((l == 0 || l == TAM - 1) && c != 0 && c != TAM-1)
                {
                    if(doces[l][c] == doces[l][c-1] && doces[l][c] == doces[l][c+1])
                    {
                        vetor_linhas[idx] = l;
                        vetor_colunas[idx] = c - 1;
                        idx++;
                        vetor_linhas[idx] = l;
                        vetor_colunas[idx] = c;
                        idx++;
                        vetor_linhas[idx] = l;
                        vetor_colunas[idx] = c + 1;
                        idx++;
                    }
                }
                else if((c == 0 || c == TAM - 1) && (l != 0 && l != TAM-1))
                {
                    if(doces[l][c] == doces[l-1][c] && doces[l][c] == doces[l+1][c])
                    {
                        vetor_linhas[idx] = l - 1;
                        vetor_colunas[idx] = c;
                        idx++;
                        vetor_linhas[idx] = l;
                        vetor_colunas[idx] = c;
                        idx++;
                        vetor_linhas[idx] = l + 1;
                        vetor_colunas[idx] = c;
                        idx++;
                    }
                }
                else if((l != 0 && l != TAM-1) && (c != 0 && c != TAM-1))
                {
                    if(doces[l][c] == doces[l][c-1] && doces[l][c] == doces[l][c+1])
                    {
                        vetor_linhas[idx] = l;
                        vetor_colunas[idx] = c - 1;
                        idx++;
                        vetor_linhas[idx] = l;
                        vetor_colunas[idx] = c;
                        idx++;
                        vetor_linhas[idx] = l;
                        vetor_colunas[idx] = c + 1;
                        idx++;
                    }
                    if(doces[l][c] == doces[l-1][c] && doces[l][c] == doces[l+1][c])
                    {
                        vetor_linhas[idx] = l - 1;
                        vetor_colunas[idx] = c;
                        idx++;
                        vetor_linhas[idx] = l;
                        vetor_colunas[idx] = c;
                        idx++;
                        vetor_linhas[idx] = l + 1;
                        vetor_colunas[idx] = c;
                        idx++;
                    }
                }
            }
        }
    }
}

//Zera vetores que guardam os eliminados
void zera_vetores()
{
    for (int i = 0; i < TAM_DOS_VETORES; i++)
    {
        vetor_colunas[i] = -1;
        vetor_linhas[i] = -1;
    }
}

//Elimina peças
void elimina()
{
    for (int i = 0; i <= idx; i++)
    {
        doces[vetor_linhas[i]][vetor_colunas[i]] = -1;
    }
    zera_vetores();
    pontos = pontos + idx*10;
    idx = 0;
}

//Repõe peças
void repor()
{
    int repos=0;
    for(int c = 0; c < TAM; c++)
    {
        for(int l = 0; l < TAM; l++)
        {
            if(doces[l][c] == -1)
            {
                repos=1;
                for(int j = l; j > 0; j--)
                {
                    doces[j][c] = doces[j - 1][c];
                }
                doces[0][c] = (rand()%4) + 1;
            }
        }
    }
    if(repos==1){
        Sleep(TIME_SLEEP);
    }
}

//Sublinha peça a ser trocada
void sublinhar()
{
    fade();
    rect(INICIODOTAB + manipulado_coluna*LARGDASCASAS, INICIODOTAB + manipulado_linha*LARGDASCASAS, INICIODOTAB + (manipulado_coluna + 1)* LARGDASCASAS, INICIODOTAB + (manipulado_linha+1)*LARGDASCASAS);
}

//Troca as peças
void troca()
{
    int aux = doces[manipulado_linha][manipulado_coluna];
    doces[manipulado_linha][manipulado_coluna] = doces[troca_linha][troca_coluna];
    doces[troca_linha][troca_coluna] = aux;
}


//FUNÇÃO DE GAMEOVER
//
//

//Menu de fim de jogo
void game_over(int *movimentos_restantes)
{
    azul_fraco();
    rectFill(GAMEOVER_1, GAMEOVER_1, GAMEOVER_2, GAMEOVER_2);
    azul_forte();
    rectFill(GAMEOVER_1 + 50, GAMEOVER_1 + 50, GAMEOVER_2 - 50, GAMEOVER_2 - 50);
    fade();
    text(GAMEOVER_1 + 220, GAMEOVER_1 + 180, "O JOGO ACABOU!!!!");
    text(GAMEOVER_1 + 200, GAMEOVER_1 + 300, "SUA PONTUACAO FOI ");
    text(GAMEOVER_1 + 380, GAMEOVER_1 + 300, pontos_final);
    if(pontos_final < pontos)
    {
        pontos_final += 10;
    }
    azul_fraco();
    rectFill(GAMEOVER_1 + 160, GAMEOVER_2 - 200, GAMEOVER_2 - 150, GAMEOVER_2-150);
    fade();
    text(GAMEOVER_1 + 227, GAMEOVER_2 - 170, "JOGAR NOVAMENTE");
    if(reset == 1)
    {
        pontos = 0;
        *movimentos_restantes = MOVIMENTOS;
        primeiroclick = -1;
    }
}
