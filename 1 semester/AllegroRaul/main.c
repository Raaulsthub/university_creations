#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <time.h>
#include <math.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600
#define SUPERIORRIGHT_REFERENCE_X 700
#define SUPERIORRIGHT_REFERENCE_Y 100
#define FPS 120.0
#define CONTINUARX 25
#define CONTINUARY 10
#define REC_CONTINUARXY1 30
#define REC_CONTINUARX2 340
#define REC_CONTINUARY2 100
#define PLAYX 50
#define PLAYY 200
#define VOLTARX 600
#define VOLTARY 500
#define TUTORIALX1 30
#define TUTORIALY1 305
#define TUTORIALX2 410
#define TUTORIALY2 385
#define SAIRX1 30
#define SAIRY1 405
#define SAIRX2 250
#define SAIRY2 485
#define MAISINFORMACOESX 50
#define ESPACAMENTO_GAME_OVER 50
#define SPAWN_DOTSX 550
#define SPAWN_DOTSAMPLITUDEY 600
#define SPAWN_DOTSAMPLITUDEX 950
#define QUANT_INICIAL 50



typedef struct reddots
{
    float raio;
    float x;
    float y;
    float speed;
}Dot;

struct specialdots
{
    float raio;
    float x;
    float y;
    float speed;
    int tipo;
};

void inits()
{
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
}

void pre_game(ALLEGRO_BITMAP* pregame_background, ALLEGRO_FONT* titulos50, ALLEGRO_FONT* escrita22, ALLEGRO_COLOR white)
{
    al_draw_bitmap(pregame_background, 0, 0, 0);
    al_draw_text(titulos50, white, SCREENWIDTH/2-270, SCREENHEIGHT/2+150, ALLEGRO_ALIGN_CENTER, "SINUOUS");
    al_draw_text(titulos50, white, SCREENWIDTH/2-100, SCREENHEIGHT/2+200, ALLEGRO_ALIGN_CENTER, "AVOID THE RED DOTS");
    al_draw_text(escrita22, white, SUPERIORRIGHT_REFERENCE_X-300, SUPERIORRIGHT_REFERENCE_Y-95, ALLEGRO_ALIGN_LEFT, "Criado por Raul Steinmetz ");
    al_draw_text(escrita22, white, SUPERIORRIGHT_REFERENCE_X-300, SUPERIORRIGHT_REFERENCE_Y-70, ALLEGRO_ALIGN_LEFT, "Orientado por Patrícia Pitthan");
    al_draw_text(titulos50, white, CONTINUARX + 15 , CONTINUARY + 25, ALLEGRO_ALIGN_LEFT, "CONTINUAR");
}

void init_menu(ALLEGRO_BITMAP* iniciar_background, ALLEGRO_FONT* titulos42, ALLEGRO_FONT* titulos72, ALLEGRO_COLOR white)
{
    al_draw_bitmap(iniciar_background, 0, 0, 0);
    al_draw_text(titulos42, white, CONTINUARX, CONTINUARY, ALLEGRO_ALIGN_LEFT, "SINUOUS - AVOID THE RED DOTS");
    al_draw_text(titulos72, white, PLAYX, PLAYY, ALLEGRO_ALIGN_LEFT, "JOGAR");
    al_draw_text(titulos72, white, PLAYX, PLAYY + 100, ALLEGRO_ALIGN_LEFT, "TUTORIAL");
    al_draw_text(titulos72, white, PLAYX, PLAYY + 200, ALLEGRO_ALIGN_LEFT, "SAIR");
}

void help_1(ALLEGRO_BITMAP* info_background, ALLEGRO_FONT* escrita16, ALLEGRO_FONT* titulos42, ALLEGRO_FONT* titulos50, ALLEGRO_COLOR white)
{
    al_draw_bitmap(info_background, 0, 0, 0);
    al_draw_text(escrita16, white, 50, 10, ALLEGRO_ALIGN_LEFT, "Infelizmente, astronauta, você está sozinho... A nave mãe ");
    al_draw_text(escrita16, white, 50, 35, ALLEGRO_ALIGN_LEFT, "não possuí suprimentos para seu resgate. Em alguns segundos, ");
    al_draw_text(escrita16, white, 50, 60, ALLEGRO_ALIGN_LEFT, "sua posição será alvo de uma chuva de fragmentos vermelhos,");
    al_draw_text(escrita16, white, 50, 85, ALLEGRO_ALIGN_LEFT, "vindos diretamente de uma explosão na estrela do sistema atual.");
    al_draw_text(escrita16, white, 50, 110, ALLEGRO_ALIGN_LEFT, "Sua vida, infelizmente acaba aqui, mas seus ultimos instantes");
    al_draw_text(escrita16, white, 50, 135, ALLEGRO_ALIGN_LEFT, "podem ser muito valiosos pra humanidade. Sua nave, como bem sabe");
    al_draw_text(escrita16, white, 50, 160, ALLEGRO_ALIGN_LEFT, "está fazendo a captação de imagens, para a futura expedição");
    al_draw_text(escrita16, white, 50, 185, ALLEGRO_ALIGN_LEFT, "ao Red Planet c-142. Se você aguentar mais um pouco, vamos finalmente");
    al_draw_text(escrita16, white, 50, 210, ALLEGRO_ALIGN_LEFT, "descobrir onde está o minério energético que trará de volta nosso sol.");
    al_draw_text(escrita16, white, 50, 235, ALLEGRO_ALIGN_LEFT, "Portanto, faça de tudo para não ser atingido, sua nave tem proteção");
    al_draw_text(escrita16, white, 50, 260, ALLEGRO_ALIGN_LEFT, "para apenas 3 choques com fragmentos e é controlada pelo seu mouse.");
    al_draw_text(escrita16, white, 50, 285, ALLEGRO_ALIGN_LEFT, "A humanidade depende de você, evite os fragmentos vermelhos, ou melhor:");
    al_draw_text(titulos42, white, SCREENWIDTH/2, 350, ALLEGRO_ALIGN_CENTER, "AVOID THE RED DOTS!!!");
    al_draw_text(titulos50, white, VOLTARX, VOLTARY, ALLEGRO_ALIGN_LEFT, "VOLTAR");
    al_draw_text(titulos50, white, MAISINFORMACOESX, VOLTARY, ALLEGRO_ALIGN_LEFT, "COMO JOGAR");
}

void help_2(ALLEGRO_BITMAP* info_background, ALLEGRO_FONT* titulos72, ALLEGRO_FONT* escrita16, ALLEGRO_FONT* titulos50, ALLEGRO_COLOR white, ALLEGRO_COLOR darkgreen, ALLEGRO_COLOR darkblue, ALLEGRO_COLOR purple, ALLEGRO_COLOR green, ALLEGRO_COLOR bright_green)
{
    al_draw_bitmap(info_background, 0, 0, 0);
    al_draw_text(titulos72, white, SCREENWIDTH/2, 20, ALLEGRO_ALIGN_CENTER, "COMO JOGAR");
    al_draw_text(escrita16, white, SCREENWIDTH/2, 120, ALLEGRO_ALIGN_CENTER, "1 -> Seu objetivo principal é ficar desviando dos pontos vermelhos pelo");
    al_draw_text(escrita16, white, SCREENWIDTH/2, 150, ALLEGRO_ALIGN_CENTER, "maior tempo possível, arrastando seu mouse, da forma que achar mais eficiente.");
    al_draw_text(escrita16, white, SCREENWIDTH/2, 180, ALLEGRO_ALIGN_CENTER, "2 -> Você possuí tres vidas, inicialmente, e perde uma a cada choque com ");
    al_draw_text(escrita16, white, SCREENWIDTH/2, 210, ALLEGRO_ALIGN_CENTER, "pontos vermelhos, sendo que a cada choque, você fica imortal por 3 segundos.");
    al_draw_text(escrita16, white, SCREENWIDTH/2, 240, ALLEGRO_ALIGN_CENTER, "3 -> A velocidade dos 'red dots' aumenta conforme sua pontuação e level, .");
    al_draw_text(escrita16, white, SCREENWIDTH/2, 270, ALLEGRO_ALIGN_CENTER, "ou seja, sobreviver ficará mas difícil a cada 'level up'(subida de fase)");
    al_draw_text(escrita16, white, SCREENWIDTH/2, 300, ALLEGRO_ALIGN_CENTER, "4 -> Você ganha pontuação por estar vivo e ao se movimentar recebe pontos bonus.");
    al_draw_text(escrita16, white, SCREENWIDTH/2, 330, ALLEGRO_ALIGN_CENTER, "5 -> Você pode ganhar 30 pontos + habilidades bonus enconstando nos especiais: ");
    al_draw_filled_circle(SCREENWIDTH/2 - 200, 367, 10, darkgreen);
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 200, 359, ALLEGRO_ALIGN_CENTER, "S");
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 150, 360, ALLEGRO_ALIGN_LEFT, " -> Invulnerabilidade por 4 segundos");
    al_draw_filled_circle(SCREENWIDTH/2 - 200, 397, 10, darkblue);
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 200, 389, ALLEGRO_ALIGN_CENTER, "G");
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 150, 390, ALLEGRO_ALIGN_LEFT, " -> Repelir inimigos por 5 segundos");
    al_draw_filled_circle(SCREENWIDTH/2 - 200, 427, 10, purple);
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 200, 419, ALLEGRO_ALIGN_CENTER, "T");
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 150, 420, ALLEGRO_ALIGN_LEFT, " -> Velocidade dos inimigos reduzida por 4.5 segundos");
    al_draw_filled_circle(SCREENWIDTH/2 - 200, 457, 10, green);
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 200, 449, ALLEGRO_ALIGN_CENTER, "M");
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 150, 450, ALLEGRO_ALIGN_LEFT, " -> Tamanho dos inimigos reduz por 5 segundos");
    al_draw_filled_circle(SCREENWIDTH/2 - 200, 487, 10, bright_green);
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 200, 479, ALLEGRO_ALIGN_CENTER, "1");
    al_draw_text(escrita16, white, SCREENWIDTH/2 - 150, 480, ALLEGRO_ALIGN_LEFT, " -> Ganha uma vida adicional");
    al_draw_text(titulos50, white, VOLTARX, VOLTARY + 25, ALLEGRO_ALIGN_LEFT, "VOLTAR");
}

void hud(ALLEGRO_FONT* escrita22, ALLEGRO_COLOR white, int vidas, float pontos, float tempo, int level, ALLEGRO_COLOR transparente)
{
    al_draw_filled_rectangle(0, 0, 165, 140, transparente);
    al_draw_text(escrita22, white, 5, 10, ALLEGRO_ALIGN_LEFT, "VIDAS: ");
    al_draw_textf(escrita22, white, 90, 10, ALLEGRO_ALIGN_LEFT, "%d", vidas);
    al_draw_text(escrita22, white, 5, 40, ALLEGRO_ALIGN_LEFT, "TEMPO: ");
    al_draw_textf(escrita22, white, 90, 40, ALLEGRO_ALIGN_LEFT, "%.2f", tempo);
    al_draw_text(escrita22, white, 5, 70, ALLEGRO_ALIGN_LEFT, "PONTOS: ");
    al_draw_textf(escrita22, white, 90, 70, ALLEGRO_ALIGN_LEFT, "%.0f", pontos);
    al_draw_text(escrita22, white, 5, 100, ALLEGRO_ALIGN_LEFT, "LEVEL: ");
    al_draw_textf(escrita22, white, 90, 100, ALLEGRO_ALIGN_LEFT, "%d", level);
}

void sublinhar(int controlador_geral, float x, float y, ALLEGRO_COLOR white, ALLEGRO_COLOR bright_blue, float raio)
{
    if(controlador_geral == 1)
    {
        if(x > REC_CONTINUARXY1 && y > REC_CONTINUARXY1 && x < REC_CONTINUARX2 && y < REC_CONTINUARY2)
        {
            al_draw_rectangle(REC_CONTINUARXY1, REC_CONTINUARXY1, REC_CONTINUARX2, REC_CONTINUARY2, white, 2);
        }
    }
    else if(controlador_geral == 2)
    {
        if(x > PLAYX - 20 && y > PLAYY + 5 && x < PLAYX + 265 &&  y < PLAYY + 90)
        {
            al_draw_rectangle(PLAYX - 20, PLAYY + 5, PLAYX + 265, PLAYY + 90, white, 2);
        }
        if(x > TUTORIALX1 && y > TUTORIALY1 && x < TUTORIALX2 && y < TUTORIALY2)
        {
            al_draw_rectangle(TUTORIALX1, TUTORIALY1, TUTORIALX2, TUTORIALY2, white, 2);
        }
        if(x > SAIRX1 && y > SAIRY1 && x < SAIRX2 && y < SAIRY2)
        {
            al_draw_rectangle(PLAYX - 20, PLAYY + 205, PLAYX + 200, PLAYY + 285, white, 2);
        }
    }
    else if(controlador_geral == 3)
    {
        if (x > VOLTARX - 10 && y > VOLTARY && x < VOLTARX + 190 && y < VOLTARY + 60)
        {
            al_draw_rectangle(VOLTARX - 10, VOLTARY, VOLTARX + 190, VOLTARY + 60, white, 2);
        }
        if(x > MAISINFORMACOESX- 10 && y > VOLTARY && x < MAISINFORMACOESX + 350 && y < VOLTARY + 65)
        {
            al_draw_rectangle(MAISINFORMACOESX - 10, VOLTARY, MAISINFORMACOESX + 350, VOLTARY + 65, white, 2);
        }
    }
    else if(controlador_geral == 4)
    {
        if (x > VOLTARX - 10 && y > VOLTARY + 25 && x < VOLTARX + 190 && y < VOLTARY + 85)
        {
            al_draw_rectangle(VOLTARX - 10, VOLTARY + 25, VOLTARX + 190, VOLTARY + 85, white, 2);
        }
    }
    else if(controlador_geral == 6)
    {
        if(x > SCREENWIDTH/2 - 260 && y > SCREENHEIGHT - 155 && x <  SCREENWIDTH/2 - 45 && y < SCREENHEIGHT - 115)
        {
            al_draw_rectangle(SCREENWIDTH/2 - 260, SCREENHEIGHT - 155, SCREENWIDTH/2 - 45, SCREENHEIGHT - 115, white, 2);
        }
        else if(x > SCREENWIDTH/2 + 40 && y > SCREENHEIGHT - 155 && x <  SCREENWIDTH - 120 && y < SCREENHEIGHT - 115)
        {
            al_draw_rectangle(SCREENWIDTH/2 + 40, SCREENHEIGHT - 155, SCREENWIDTH - 120, SCREENHEIGHT - 115, white, 2);
        }
    }
}

void game_over(ALLEGRO_COLOR transparente, ALLEGRO_FONT* titulos42, ALLEGRO_COLOR white, ALLEGRO_FONT* hud22, float pontos, float tempo, float level)
{
    al_draw_filled_rectangle(ESPACAMENTO_GAME_OVER + 50, ESPACAMENTO_GAME_OVER, SCREENWIDTH - ESPACAMENTO_GAME_OVER - 50, SCREENHEIGHT - ESPACAMENTO_GAME_OVER, transparente);
    al_draw_text(titulos42, white, SCREENWIDTH/2, SCREENHEIGHT/2 - 200, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_text(hud22, white, SCREENWIDTH/2 - 80, SCREENHEIGHT/2 -50, ALLEGRO_ALIGN_LEFT, "PONTOS: ");
    al_draw_textf(hud22, white, SCREENWIDTH/2 + 30, SCREENHEIGHT/2 -50, ALLEGRO_ALIGN_LEFT, "%.0f", pontos);
    al_draw_text(hud22, white, SCREENWIDTH/2 - 80, SCREENHEIGHT/2, ALLEGRO_ALIGN_LEFT, "TEMPO: ");
    al_draw_textf(hud22, white, SCREENWIDTH/2 + 30, SCREENHEIGHT/2, ALLEGRO_ALIGN_LEFT, "%.2f", tempo);
    al_draw_text(hud22, white, SCREENWIDTH/2 + 50, SCREENHEIGHT - 150, ALLEGRO_ALIGN_LEFT, "JOGAR NOVAMENTE");
    al_draw_text(hud22, white, SCREENWIDTH/2 - 250, SCREENHEIGHT - 150, ALLEGRO_ALIGN_LEFT, "VOLTAR AO MENU");
    al_draw_text(hud22, white, SCREENWIDTH/2 - 80, SCREENHEIGHT/2 + 50, ALLEGRO_ALIGN_LEFT, "LEVEL: ");
    al_draw_textf(hud22, white, SCREENWIDTH/2 + 30, SCREENHEIGHT/2 + 50, ALLEGRO_ALIGN_LEFT, "%.0f", level);
}

void first_spawn(Dot *dot, float *soltar_especial, int raio_azul, int quant_max)
{
    for(int i = 0; i < quant_max; i++)
    {
        if (i % 2 == 0)
        {
            dot[i].raio = raio_azul - (rand()%raio_azul)/10.0 - raio_azul/10.0;    
        }
        else
        {
            dot[i].raio = raio_azul + raio_azul/10.0 + (rand()%raio_azul)/10.0;
        }
        dot[i].x = SPAWN_DOTSX + rand() % SPAWN_DOTSAMPLITUDEX;
        dot[i].y = - (rand()%SPAWN_DOTSAMPLITUDEY);
        dot[i].speed = (rand()%5 + 5)/10.0;
    }
}

void manipula_dots(Dot *dot, int quant_atual, int *estado, ALLEGRO_COLOR red, int raio, float *tempo_da_colisao, float tempo, int *vidas, float x, float y, ALLEGRO_COLOR blue, double *raio_do_escudo, ALLEGRO_COLOR bright_green, float *tempo_especial,  ALLEGRO_COLOR transparente, ALLEGRO_COLOR bright_blue, int *level)
{
    for(int i = 0; i < quant_atual; i++)
    {
        if(*estado == 0)
        {
            al_draw_filled_circle(dot[i].x, dot[i].y, dot[i].raio, red);
            if((x - dot[i].x)*(x - dot[i].x) + (y - dot[i].y)*(y - dot[i].y) - (raio + dot[i].raio)*(raio + dot[i].raio) < (dot[i].raio * dot[i].raio))
            {
                *vidas = *vidas - 1;
                *estado = 1;
                *tempo_da_colisao = tempo;
                dot[i].x = -50;
                dot[i].y = -50; 
            }
        }
        else if(*estado == 1)
        {
            al_draw_filled_circle(x, y, raio * 2, blue);
            al_draw_filled_circle(dot[i].x, dot[i].y, dot[i].raio, red);
            if(tempo > *tempo_da_colisao + 3)
            {
                *estado = 0;
            }
        }
        else if(*estado == 2)
        {
            al_draw_filled_circle(x, y, *raio_do_escudo, bright_green);
            al_draw_filled_circle(dot[i].x, dot[i].y, dot[i].raio, red);
            if((x - dot[i].x)*(x - dot[i].x) + (y - dot[i].y)*(y - dot[i].y) - (*raio_do_escudo + dot[i].raio)*(*raio_do_escudo + dot[i].raio) < (dot[i].raio * dot[i].raio))
            {
                dot[i].x = -50;
                dot[i].y = -50; 
            }
            if (tempo > *tempo_especial + 4)
            {
                *estado = 0;
            }
            if (*raio_do_escudo > raio + 2)
            {
                *raio_do_escudo -= 0.0005;
            }
        }
        else if(*estado == 3)
        {
            al_draw_filled_circle(x, y, raio * 10, transparente);
            al_draw_filled_circle(dot[i].x, dot[i].y, dot[i].raio, red);
            if((x - dot[i].x)*(x - dot[i].x) + (y - dot[i].y)*(y - dot[i].y) - (raio*10.3 + dot[i].raio)*(raio*10.3+ dot[i].raio) < (dot[i].raio * dot[i].raio))
            {
                if(dot[i].y > y)
                {
                    if(*level > 4)
                    {
                        dot[i].y += 3;
                    }
                    dot[i].y += 10;
                }
                else
                {
                    if(*level > 4)
                    {
                        dot[i].y -= 3;
                    }
                    dot[i].y -= 10;
                }
            }
            if (tempo > *tempo_especial + 4)
            {
                *estado = 0;
            }
        }
        else if(*estado == 4)
        {
            al_draw_filled_circle(dot[i].x, dot[i].y, dot[i].raio, red);
            dot[i].x = dot[i].x - dot[i].speed * 0.2;
            dot[i].y = dot[i].y + dot[i].speed * 0.2;
            if((x - dot[i].x)*(x - dot[i].x) + (y - dot[i].y)*(y - dot[i].y) - (raio + dot[i].raio)*(raio + dot[i].raio) < (dot[i].raio * dot[i].raio))
            {
                *vidas = *vidas - 1;
                *estado = 1;
                *tempo_da_colisao = tempo;
                dot[i].x = -50;
                dot[i].y = -50; 
            }
            if (tempo > *tempo_especial + 4.5)
            {
                *estado = 0;
            }
        }
        else if(*estado == 5)
        {
            al_draw_filled_circle(dot[i].x, dot[i].y, dot[i].raio * 0.5, red);
            if((x - dot[i].x)*(x - dot[i].x) + (y - dot[i].y)*(y - dot[i].y) - (raio + dot[i].raio*0.15)*(raio + dot[i].raio*0.15) < (dot[i].raio*0.15 * dot[i].raio*0.15))
            {
                *vidas = *vidas - 1;
                *estado = 1;
                *tempo_da_colisao = tempo;
                dot[i].x = -50;
                dot[i].y = -50; 
            }
            if (tempo > *tempo_especial + 5)
            {
                *estado = 0;
            }
        }
        al_draw_filled_circle(x, y, raio, bright_blue);
    }
}

void respawn(Dot *dot, int quant_atual, int estado, int raio, int level)
{
    for(int i = 0; i < quant_atual; i++)
    {
        if(dot[i].y > SCREENWIDTH + 10 || dot[i].x < -10)
        {
            if (i % 2 == 0)
            {
                dot[i].raio = raio - (rand()%raio)/10.0 - raio/10.0;    
            }
            else
            {
                dot[i].raio = raio + raio/10.0 + (rand()%raio)/10.0;
            }
            dot[i].x = SPAWN_DOTSX + rand() % SPAWN_DOTSAMPLITUDEX;
            dot[i].y = - (rand()%SPAWN_DOTSAMPLITUDEY);
            if(level < 10)
            {
                dot[i].speed = (rand()%5 + 7)/10.0 + 0.2 * level;
            }
        }
        if(estado != 4)
        {
            dot[i].x = dot[i].x - dot[i].speed;
            dot[i].y = dot[i].y + dot[i].speed;
        }
    }
}

void specials(struct specialdots *special, ALLEGRO_FONT* escrita12, ALLEGRO_COLOR darkgreen, int raio, double *raio_do_escudo, int *estado, float x, float y, ALLEGRO_COLOR white, ALLEGRO_COLOR darkblue, ALLEGRO_COLOR purple, ALLEGRO_COLOR green, ALLEGRO_COLOR bright_green, int *vidas)
{
    switch(special->tipo)
    {
        case 1:
            al_draw_filled_circle(special->x, special->y, special->raio, darkgreen);
            al_draw_text(escrita12, white, special->x, special->y - 6, ALLEGRO_ALIGN_CENTER, "S");
            if((x - special->x)*(x - special->x) + (y - special->y)*(y - special->y) - (raio + special->raio)*(raio + special->raio) < (special->raio * special->raio))
            {
                *raio_do_escudo = raio * 5;
                *estado = 2;
            }
            break;
        case 2:
            al_draw_filled_circle(special->x, special->y, special->raio, darkblue);
            al_draw_text(escrita12, white, special->x, special->y - 6, ALLEGRO_ALIGN_CENTER, "G");
            if((x - special->x)*(x - special->x) + (y - special->y)*(y - special->y) - (raio + special->raio)*(raio + special->raio) < (special->raio * special->raio))
            {
                *estado = 3;
            }
            break;
        case 3:
            al_draw_filled_circle(special->x, special->y, special->raio, purple);
            al_draw_text(escrita12, white, special->x, special->y - 6, ALLEGRO_ALIGN_CENTER, "T");
            if((x - special->x)*(x - special->x) + (y - special->y)*(y - special->y) - (raio + special->raio)*(raio + special->raio) < (special->raio * special->raio))
            {
                *estado = 4;
            }
            break;
        case 4:
            al_draw_filled_circle(special->x, special->y, special->raio, green);
            al_draw_text(escrita12, white, special->x, special->y - 6, ALLEGRO_ALIGN_CENTER, "M");
            if((x - special->x)*(x - special->x) + (y - special->y)*(y - special->y) - (raio + special->raio)*(raio + special->raio) < (special->raio * special->raio))
            {
                *estado = 5;
            }
            break;
        case 5:
            al_draw_filled_circle(special->x, special->y, special->raio, bright_green);
            al_draw_text(escrita12, white, special->x, special->y - 6, ALLEGRO_ALIGN_CENTER, "1");
            if((x - special->x)*(x - special->x) + (y - special->y)*(y - special->y) - (raio + special->raio)*(raio + special->raio) < (special->raio * special->raio))
            {
                *vidas = *vidas + 1;
            }
            break;
    }
}

int main()
{
    al_init();
    int controlador_geral = 1, quantmax = 500, quant_atual = QUANT_INICIAL, raio = 5, vidas = 3;
    bool running = true;
    float x = 0, y = 0, tempo = 0, pontos = 0;
    long int controlador_pontos = 0;
    Dot dot[quantmax];
    struct specialdots special;
    int estado = 0, level = 1, pontos_anteriores = 0, restart = 0;
    float controla_especiaisA = 0, controla_especiaisB = 0, soltar_especial = 0;
    double raio_do_escudo = 0;
    float cursor_atualx = 0, cursor_atualy = 0, levelup = 0;
    float tempo_especial = 0, tempo_da_colisao = 0;

    srand(time(NULL));
    first_spawn(&dot[0], &soltar_especial, raio, quantmax);
    inits();

    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_BITMAP* pregame_background = NULL;
    ALLEGRO_BITMAP* iniciar_background = NULL;
    ALLEGRO_BITMAP* info_background = NULL;
    ALLEGRO_FONT* titulos42 = al_load_font("titulos.ttf", 42, 0);
    ALLEGRO_FONT* titulos50 = al_load_font("titulos.ttf", 50, 0);
    ALLEGRO_FONT* titulos72 = al_load_font("titulos.ttf", 72, 0);
    ALLEGRO_FONT* escrita22 = al_load_font("unispace rg.ttf", 22, 0);
    ALLEGRO_FONT* escrita16 = al_load_font("unispace rg.ttf", 16, 0);
    ALLEGRO_FONT* hud16 = al_load_font("titulos.ttf", 16, 0);
    ALLEGRO_FONT* hud22 = al_load_font("titulos.ttf", 22, 0);
    ALLEGRO_FONT* escrita12 = al_load_font("unispace rg.ttf", 12, 0);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR player_color = white;
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR bright_blue = al_map_rgb(14, 235, 235);
    ALLEGRO_COLOR blue = al_map_rgb(55, 65, 200);
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR transparente = al_map_rgba(0, 0, 18, 0.9);
    ALLEGRO_COLOR darkgreen = al_map_rgb(8, 90, 19);
    ALLEGRO_COLOR darkblue = al_map_rgb(0, 0, 153);
    ALLEGRO_COLOR purple = al_map_rgb(102, 0, 204);
    ALLEGRO_COLOR green = al_map_rgb(0, 204, 102);
    ALLEGRO_COLOR bright_green = al_map_rgb(128, 255, 0);
    display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0/60.0);
    pregame_background = al_load_bitmap("pregame_background.jpg");
    iniciar_background = al_load_bitmap("iniciar_background.jpg");
    info_background = al_load_bitmap("info_background.jpg");
    al_install_mouse();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_hide_mouse_cursor(display);
    al_start_timer(timer);

    while(running)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            running = false;
        }
        if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            x = event.mouse.x;
            y = event.mouse.y;
        }
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(controlador_geral == 1)
            {
                if(event.mouse.button & 1)
                {
                    if(x > REC_CONTINUARXY1 && y > REC_CONTINUARXY1 && x < REC_CONTINUARX2 && y < REC_CONTINUARY2)
                    {
                        controlador_geral = 2;
                    }

                }
            }
            else if(controlador_geral == 2)
            {
                if(event.mouse.button & 1)
                {
                    if(x > PLAYX - 20 && y > PLAYY + 5 && x < PLAYX + 265 &&  y < PLAYY + 90)
                    {
                        controlador_geral = 5;
                        x = SCREENWIDTH/2;
                        y = SCREENHEIGHT/2;
                    }
                    if(x > TUTORIALX1 && y > TUTORIALY1 && x < TUTORIALX2 && y < TUTORIALY2)
                    {
                        controlador_geral = 3;
                    }
                    if(x > SAIRX1 && y > SAIRY1 && x < SAIRX2 && y < SAIRY2)
                    {
                        running = false;
                    }
                }
            }
            else if(controlador_geral == 3)
            {
                if(event.mouse.button & 1)
                {
                    if (x > VOLTARX - 10 && y > VOLTARY && x < VOLTARX + 190 && y < VOLTARY + 60)
                    {
                        controlador_geral = 2;
                    }
                    if(x > MAISINFORMACOESX- 10 && y > VOLTARY && x < MAISINFORMACOESX + 350 && y < VOLTARY + 65)
                    {
                        controlador_geral = 4;
                    }
                }
            }
            else if(controlador_geral == 4)
            {
               if(event.mouse.button & 1)
               {
                    if (x > VOLTARX - 10 && y > VOLTARY + 25 && x < VOLTARX + 190 && y < VOLTARY + 85)
                    {
                        controlador_geral = 3;
                    }
               }
            }
            else if(controlador_geral == 6)
            {
                if(x > SCREENWIDTH/2 - 260 && y > SCREENHEIGHT - 155 && x <  SCREENWIDTH/2 - 45 && y < SCREENHEIGHT - 115)
                {
                    controlador_geral = 2;
                    restart = 1;
                }
                else if(x > SCREENWIDTH/2 + 40 && y > SCREENHEIGHT - 155 && x <  SCREENWIDTH - 120 && y < SCREENHEIGHT - 115)
                {
                    controlador_geral = 5;
                    restart = 1;
                }
            }
        }
        if (controlador_geral == 1)
        {
            pre_game(pregame_background, titulos50, escrita22, white);
        }
        else if(controlador_geral == 2)
        {
            init_menu(iniciar_background, titulos42, titulos72, white);
        }
        else if (controlador_geral == 3)
        {
            help_1(info_background, escrita16, titulos42, titulos50, white);    
        }
        else if(controlador_geral == 4)
        {
            help_2(info_background, titulos72, escrita16, titulos50, white, darkgreen, darkblue, purple, green, bright_green);
        }
        sublinhar(controlador_geral, x, y, white, bright_blue, raio);
        if (restart == 1)
        {
            level = 1;
            pontos = 1;
            vidas = 3;
            tempo = 0;
            estado = 0;
            first_spawn(&dot[0], &soltar_especial, raio, quantmax);
            quant_atual = QUANT_INICIAL;
            soltar_especial = 0;
            restart = 0;
            pontos_anteriores = 0;
        }
        al_draw_filled_circle(x, y, raio, bright_blue);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {   
            if(controlador_geral == 5)
            {
                al_grab_mouse(display);
                al_clear_to_color(black);
                hud(hud16, white, vidas, pontos, tempo, level, transparente);
                manipula_dots(&dot[0], quant_atual, &estado, red, raio, &tempo_da_colisao, tempo, &vidas, x, y, blue, &raio_do_escudo, bright_green, &tempo_especial, transparente, bright_blue, &level);
                respawn(&dot[0], quant_atual, estado, raio, level);
                if(soltar_especial == 1)
                {
                    specials(&special, escrita12, darkgreen, raio, &raio_do_escudo, &estado, x, y, white, darkblue, purple, green, bright_green, &vidas);
                    if((x - special.x)*(x - special.x) + (y - special.y)*(y - special.y) - (raio + special.raio)*(raio + special.raio) < (special.raio * special.raio))
                    {
                        soltar_especial = 0;
                        pontos += 30;
                        tempo_especial = tempo;
                    }
                    if(special.x < 0 || special.y > SCREENHEIGHT)
                    {
                       soltar_especial = 0;
                    }
                    special.x--;
                    special.y++;
                }
                if(vidas < 1)
                {
                    controlador_geral = 6;
                }
                if(level < 8)
                {
                    pontos = pontos + 0.2 * level;
                }
                else
                {
                    pontos = pontos + 1.6;
                }
                tempo = tempo + 1/FPS;
                if(pontos > pontos_anteriores + 500 * level)
                {
                    levelup = 1;
                    if (quant_atual < quantmax)
                    {
                        quant_atual += 10;
                    }
                    level = level + 1;
                    pontos_anteriores = pontos;
                }
                if (levelup >= 1 && levelup < 120)
                {
                    levelup++;
                    al_draw_text(titulos42, white, SCREENWIDTH/2 + 25, SCREENHEIGHT/2 - 200, ALLEGRO_ALIGN_CENTER, "LEVEL UP");
                }
                controla_especiaisA++;
                if (controla_especiaisA > controla_especiaisB + 500 + rand()%100 && soltar_especial == 0)
                {
                    controla_especiaisB = controla_especiaisA;
                    soltar_especial = 1;
                    special.tipo = (rand()%5) + 1;
                    special.x = SPAWN_DOTSX + rand() % SPAWN_DOTSAMPLITUDEX;;
                    special.y = - (rand()%SPAWN_DOTSAMPLITUDEY);
                    special.raio = raio - raio/10 - (rand()%raio)/10 + 3;
                }
                if(x != cursor_atualx || y != cursor_atualy)
                {
                    pontos++;
                    cursor_atualx = x;
                    cursor_atualy = y;
                }        
            }
            if(controlador_geral == 6)
            {
                al_clear_to_color(black);
                for(int i = 0; i < quant_atual; i++)
                {
                    al_draw_filled_circle(x, y, raio, bright_blue);
                    al_draw_filled_circle(dot[i].x, dot[i].y, dot[i].raio, red);
                    dot[i].x = dot[i].x - dot[i].speed;
                    dot[i].y = dot[i].y + dot[i].speed;
                    respawn(&dot[0], quant_atual, 4, raio, level);
                }
                game_over(transparente, titulos42, white, hud22, pontos, tempo, level);
                sublinhar(controlador_geral, x, y, white, bright_blue, raio);
            } 
            al_flip_display();
        }
    }

    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_uninstall_mouse();
    al_destroy_bitmap(pregame_background);
    al_destroy_bitmap(iniciar_background);
    al_destroy_bitmap(info_background);
    al_destroy_timer(timer);
    al_destroy_font(titulos42);
    al_destroy_font(titulos50);
    al_destroy_font(escrita22);
    al_destroy_font(titulos72);
    al_destroy_font(escrita16);
    al_destroy_font(hud16);
    al_destroy_font(hud22);
    al_destroy_font(escrita12);
    return 0;
}

//PARA COMPILAR CODIGO ABAIXO
//gcc main.c -o main $(pkg-config allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_ttf-5 allegro_font-5 allegro_image-5 allegro-5 allegro_font-5 --libs --cflags)