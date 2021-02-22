#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#define TAMANHO 500
//Checkar se uma peca x é um cavalo, por exemplo: abs(x) == CAVALO
#define PECA int
#define VAZIO 0
#define PEAO 1
#define CAVALO 2
#define BISPO 3
#define TORRE 4
#define RAINHA 5
#define REI 6

//Pensar nisto como se fosse uma função: Quando escrevermos PRETO(PEAO), o pre-processador vai fazer PRETO(-PEAO), como PEAO = 1, entao -PEAO = -1;
#define PRETO(x) (-x)
#define BRANCO(x) (x)
#define COR_PRETO -1
#define COR_BRANCO 1

typedef enum { Preto, Branco } Jogador;

//Cada PECA é identificada unicamente pela sua posicao, através desta struct
typedef struct 
{
    int x;
    int y;
} Posicao;

typedef struct
{
    int usados;
   Posicao pos[TAMANHO];

} ListaPosicao;

typedef struct 
{
    int tabuleiro[8][8];
   int nJogadas;

} Tabuleiro;

int IndicePos(Posicao p, ListaPosicao* lp);

bool OutraCor(PECA x, PECA y);
bool PecaInimiga(Tabuleiro t, Posicao peca1, Posicao check);
bool PosEQ(Posicao p1, Posicao p2);

Tabuleiro Novo_tabuleiro();

PECA RetornarPeca(Tabuleiro t, Posicao p);

ListaPosicao ListaVazia();
Posicao NewPos(int x, int y);
Posicao* PosicaoRei(Tabuleiro t, int cor);

void RetirarPos(Posicao p, ListaPosicao* lp);
void Retiraindice(int idx, ListaPosicao* lp);
void RetirarPos(Posicao p, ListaPosicao* lp);
void PrintarLista(ListaPosicao* lp);
void AdicionarPos(Posicao p, ListaPosicao* lp);
void AdicionarLista(ListaPosicao lp1, ListaPosicao* lp2);
void RetirarPosicoesEmXeque(ListaPosicao lp, ListaPosicao lp2);

char* JogadortoString(Jogador j);

Jogador OutroJogador(Jogador j);