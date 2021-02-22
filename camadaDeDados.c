#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "chess.h"
#include "CamadadeDados.h"
#include <malloc.h>
#include <stdbool.h>


//Funcao que verifica se a peca é inimiga 
bool PecaInimiga(Tabuleiro t, Posicao peca1, Posicao check) {
    int outraPeca = t.tabuleiro[check.x][check.y];
    int peca = t.tabuleiro[peca1.x][peca1.y];

    if (peca > 0 && outraPeca < 0) return true;
    else if (peca < 0 && outraPeca > 0) return true;
    else return false;
}
//Tabuleiro Inicial
Tabuleiro Novo_tabuleiro()
{
    Tabuleiro* t = malloc(sizeof(Tabuleiro));
    
    t->nJogadas = 1;
    int i, j;
    
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            t->tabuleiro[i][j] = VAZIO;
        }
    }
    //Base das peças brancas
    t->tabuleiro[1][0] = BRANCO(PEAO);
    t->tabuleiro[1][1] = BRANCO(PEAO);
    t->tabuleiro[1][2] = BRANCO(PEAO);
    t->tabuleiro[1][3] = BRANCO(PEAO);
    t->tabuleiro[1][4] = BRANCO(PEAO);
    t->tabuleiro[1][5] = BRANCO(PEAO);
    t->tabuleiro[1][6] = BRANCO(PEAO);
    t->tabuleiro[1][7] = BRANCO(PEAO);

    t->tabuleiro[0][0] = BRANCO(TORRE);
    t->tabuleiro[0][1] = BRANCO(CAVALO);
    t->tabuleiro[0][2] = BRANCO(BISPO);
    t->tabuleiro[0][3] = BRANCO(RAINHA);
    t->tabuleiro[0][4] = BRANCO(REI);
    t->tabuleiro[0][5] = BRANCO(BISPO);
    t->tabuleiro[0][6] = BRANCO(CAVALO);
    t->tabuleiro[0][7] = BRANCO(TORRE);


    //Base das peças pretas
    t->tabuleiro[6][0] = PRETO(PEAO);
    t->tabuleiro[6][1] = PRETO(PEAO);
    t->tabuleiro[6][2] = PRETO(PEAO);
    t->tabuleiro[6][3] = PRETO(PEAO);
    t->tabuleiro[6][4] = PRETO(PEAO);
    t->tabuleiro[6][5] = PRETO(PEAO);
    t->tabuleiro[6][6] = PRETO(PEAO);
    t->tabuleiro[6][7] = PRETO(PEAO);

    t->tabuleiro[7][0] = PRETO(TORRE);
    t->tabuleiro[7][1] = PRETO(CAVALO);
    t->tabuleiro[7][2] = PRETO(BISPO);
    t->tabuleiro[7][3] = PRETO(RAINHA);
    t->tabuleiro[7][4] = PRETO(REI);
    t->tabuleiro[7][5] = PRETO(BISPO);
    t->tabuleiro[7][6] = PRETO(CAVALO);
    t->tabuleiro[7][7] = PRETO(TORRE);
    
    return *t;
}

//Funcao que retorna a peca em relação a posicao no tabuleiro
PECA RetornarPeca(Tabuleiro t, Posicao p) {
    if ((p.x < 8 && p.x >= 0) && (p.y < 8 && p.y >= 0)) {
        return t.tabuleiro[p.x][p.y];
    }
    else return NULL;
}
//Inicializar a nulo 
ListaPosicao ListaVazia() {
    ListaPosicao aux;
    aux.usados = 0;
    return aux;
}

// Funcao utilizada para adicionar posições em uma lista
void AdicionarPos(Posicao p, ListaPosicao* lp) {
    lp->pos[lp->usados] = p;
    lp->usados++;
}

//Funcao que printa uma lista
void PrintarLista(ListaPosicao* lp) {
    char print;
    for (int i = 0; i < lp->usados; i++) {
        Posicao p = lp->pos[i];
        switch (lp->pos[i].y) {
        case 0: print = 'A'; break;
        case 1: print = 'B'; break;
        case 2: print = 'C'; break;
        case 3: print = 'D'; break;
        case 4: print = 'E'; break;
        case 5: print = 'F'; break;
        case 6: print = 'G'; break;
        case 7: print = 'H'; break;
        default: break;
        }
       printf("|%d%c| ", lp->pos[i].x+1, print);
        
    }
}

//Funcao retorna o indice da posicao case esteja na lista, ou -1 caso nao esteja
int IndicePos(Posicao p, ListaPosicao* lp) {
    for (int i = 0; i < lp->usados; i++) {
        if (PosEQ(lp->pos[i], p)) return i;
    } 
    return -1;
}
//Funcao que compara duas posições
bool PosEQ(Posicao p1, Posicao p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void RetirarPos(Posicao p, ListaPosicao* lp) 
{  
    int idx = IndicePos(p, lp);
    if (idx == -1) {
        return;
    }
    else {
        Retiraindice(idx, lp);
    }
}
// 1-3 5-6  4-4 6-6
//  0   1    2   3
// se fizer retirar idx [1]
// 1-3  4-4  6-6

void Retiraindice(int idx, ListaPosicao *lp) {
    for (int i = idx; i < (*lp).usados; i++) {
        lp->pos[i] = lp->pos[i + 1];
    }
    lp->usados--;
}

Posicao NewPos(int x, int y) {
    Posicao p = { x , y };
    return p;
}

//BIG BRAIN
// menos vezes mais == negativo
// mais vezes mais == positivo
//menos vezes menos == negativo
bool OutraCor(PECA x, PECA y) {
    return x * y < 0;
}

Posicao* PosicaoRei(Tabuleiro t, int cor) {
    Posicao p; p.x = 0;

    while (p.x < 8) {
        p.y = 0;
        while (p.y < 8) {
            if (t.tabuleiro[p.x][p.y] == cor*REI) return &p;
            p.y++;
        }
        p.x++;
    }
    return NULL;
}

//Funcao que adiciona todas as Posicoes de uma lista lp1, numa outra lista lp2
void AdicionarLista(ListaPosicao lp1, ListaPosicao* lp2)
{ 
    for (int i = 0; i < lp1.usados; i++) {
        AdicionarPos(lp1.pos[i], lp2);
    }
}
//Funcao que pega em duas listas e retirar as posições em Xeque 
//É utilizada como auxiliar da função Xeque Mate
void RetirarPosicoesEmXeque(ListaPosicao lp, ListaPosicao lp2) {
    for (int i = 0; i < lp2.usados; i++) {
        if (PosEQ(lp2.pos[i], lp.pos[i])) RetirarPos(lp2.pos[i], &lp2);
    }
}

const char* brancostr = "branco";
const char* pretostr = "preto";
char* JogadortoString(Jogador j) 
{
    if (j == Branco) return brancostr;
    else return pretostr;
}

Jogador OutroJogador(Jogador j)
{
    if (j == Branco) return Preto;
    else return Branco;
}
