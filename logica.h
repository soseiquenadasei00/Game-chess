#include "camadaDeDados.h"
//Funcoes Auxiliares que so facilitam nossa vida:
void RetirarPosInvalidas(Tabuleiro t, ListaPosicao *lp, Posicao p);
void RetirarPosRedundantes(Tabuleiro t, ListaPosicao *lp, Posicao p);
void RetirarPosOOB/*out of bounds*/(Tabuleiro t, ListaPosicao* lp);
ListaPosicao PosicoesDisponiveis(Tabuleiro t, Jogador j);
int randomPlayer();


//Funcoes essenciais:
ListaPosicao MovimentoPeao(Tabuleiro t, Posicao p);
ListaPosicao MovimentoCavalo(Tabuleiro t, Posicao p);
ListaPosicao MovimentoBispo(Tabuleiro t, Posicao p);
ListaPosicao MovimentoTorre(Tabuleiro t, Posicao p);
ListaPosicao MovimentoRainha(Tabuleiro t, Posicao p);
ListaPosicao MovimentoRei(Tabuleiro t, Posicao p);



//Funcoes mecanicas:
bool Xeque(Tabuleiro t, Jogador j);
bool XequeMate(Tabuleiro t, Jogador j);
Tabuleiro Movimentar(Tabuleiro t, Posicao old, Posicao nova);
void AddRoque(Tabuleiro t, Posicao p, ListaPosicao* lp);
Tabuleiro Roque(Tabuleiro t, Posicao old, Posicao nova);