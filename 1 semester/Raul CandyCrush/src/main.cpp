/*
    AUTOR DO JOGO: Raul Steinmetz
    AUTOR DA API CANVAS 2D: Cesar Tadeu Pozzer

    Para fins de correção:
    - Os quesitos cumpridos foram:
        1. Cenário do jogo
        2. Menu inicial e sessão de "como jogar" // Opcional
        3. Contador de pontos
        4. Contador de movimentos
        5. Trocas, remoção e reposição de peças
        6. GameOver e Reset //Opcional
    - Observação
        -> Algumas vezes ocorre um efeito visual,
           por conta da velocidade das peças,
           que faz parecer que a eliminação das peças nãp
           ocorreu, mas garanto que ela ocorre, porém, cairam
           peças iguais no lugar, por meio da reposição das
           peças.
 */


#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include <time.h>
#include "auxiliar.h"

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

int iniciar = 0; //Controlador do menuinicial
int foi_selecionado = 0; //Controlador de trocas
int movimentos_restantes = MOVIMENTOS; //Movimentos restantes
int pontu; //Controla trocas inválidas

//Render
void render()
{
    if(iniciar == 0)
    {
        menu_inicial();
    }
    else if(iniciar == 2)
    {
        info();
    }
    else if(iniciar == 1)
    {
       cor_fundo();
       tabuleiro();
       hud(movimentos_restantes);
       draw_doces();
       marca_eliminados();
       elimina();
       repor();
       if(foi_selecionado == 1)
       {
           sublinhar();
       }
       else if(foi_selecionado == 2)
       {
           troca();
           draw_doces();
           pontu = pontos;
           marca_eliminados();
           elimina();
           repor();
           if (pontu < pontos)
           {
               movimentos_restantes--;
           }
           else
           {
               troca();
           }
           foi_selecionado = 0;
       }
       if(movimentos_restantes == 0)
       {
           game_over(&movimentos_restantes);
       }
    }
}

//Controle de Mouse
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   mx = x; //guarda as coordenadas do mouse para exibir dentro da render()
   my = y;

   if(iniciar != 1)
   {
       if (button == 0 && (mx >= XBOTAOINICIAR && my >= YBOTAOINICIAR && mx <= X2BOTAOINICIAR && my <= Y2BOTAOINICIAR))
       {
           iniciar = 1;
       }
       else if(button == 0 && (mx >= XBOTAOINFO && my >= YBOTAOINFO && mx <= X2BOTAOINFO && my <= Y2BOTAOINFO))
       {
           iniciar = 2;
       }
       if(iniciar == 2)
       {
           if(button == 0 && (mx >= XVOLTAR && my >= YVOLTAR && mx <= X2VOLTAR && my <= Y2VOLTAR))
           {
               iniciar = 0;
           }
       }
   }
   if(iniciar == 1)
   {
       if (state == 0)
       {
           primeiroclick++;
       }
       if(state == 0 && mx >= INICIODOTAB && my >= INICIODOTAB && mx <= FIMDOTAB && my <= FIMDOTAB && foi_selecionado == 0 && primeiroclick > 1)
       {
           manipulado_linha = (int)(my-INICIODOTAB)/LARGDASCASAS;
           manipulado_coluna = (int)(mx-INICIODOTAB)/LARGDASCASAS;
           foi_selecionado = 1;
       }
       else if(state == 0 && mx >= INICIODOTAB && my >= INICIODOTAB && mx <= FIMDOTAB && my <= FIMDOTAB && foi_selecionado == 1)
       {
           int permissao = 0;
           troca_linha = (int)(my-INICIODOTAB)/LARGDASCASAS;
           troca_coluna = (int)(mx-INICIODOTAB)/LARGDASCASAS;
           if(troca_linha - manipulado_linha <= 1 && troca_coluna - manipulado_coluna <= 1 && manipulado_linha - troca_linha <=1 && manipulado_coluna - troca_coluna <= 1 && (troca_linha == manipulado_linha || troca_coluna == manipulado_coluna))
           {
               permissao = 1;
           }
           if(permissao == 1)
           {
               foi_selecionado = 2;
           }
           else
           {
               foi_selecionado = 0;
           }
       }
       if(movimentos_restantes == 0)
       {
           if(state == 0 && mx >= GAMEOVER_1 + 160 && my >= GAMEOVER_2 - 200 && mx <= GAMEOVER_2 - 150 && my <= GAMEOVER_2 - 150)
           {
               reset = 1;
           }
       }
       if(state == 0)
       {
           int distReset = sqrt((mx - RESETX) * (mx - RESETX) + (my - RESETY) * (my  - RESETY));
           if (distReset < RAIODOCES + 30)
           {
               pontos = 0;
               movimentos_restantes = 10;
           }

       }

   }
}

//Controle de Teclado
void keyboard(int key)
{
   printf("\nClicou Tecla: %d" , key);
}


//Controle de Teclado
void keyboardUp(int key)
{
   printf("\nLiberou Tecla: %d" , key);
}

//Main
int main(void)
{
   printf("Instrucoes:\n");
   printf("-> O jogo eh controlado por meio do movimento do mouse e do botao 'mouse 1'\n");
   printf("-> Para mover pecas, deve-se clicar uma vez em cada uma\n");
   printf("-> Para usar outra funcionalidade, usar 'mouse 1' tambem\n\n");

   cria_doces();
   zera_vetores();
   int screenWidth = 800, screenHeight = 800; //largura e altura inicial da tela. Alteram com o redimensionamento de tela.
   init(&screenWidth, &screenHeight, "Candy Crush");
   run();
}
