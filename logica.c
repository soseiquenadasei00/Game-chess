#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "CamadadeDados.h"
#include "chess.h"
#include "file.h"

//Movimentos no tabuleiro 
Posicao ParaFrente(PECA peca, Posicao p) {
	if (peca < 0) {
		return NewPos(p.x - 1, p.y);
	}
	else
		return NewPos(p.x + 1, p.y);
}

Posicao ParaDireita(Posicao p) {
	return NewPos(p.x, p.y + 1);
}

Posicao ParaEsquerda(Posicao p) {
	return NewPos(p.x, p.y - 1);
}

Posicao ParaTras(PECA peca, Posicao p)
{
	if (peca < 0)
	{
		return NewPos(p.x + 1, p.y);
	}
	else
		return NewPos(p.x - 1, p.y);
}



//MOVIMENTOS DAS PEÇAS

//Nas funcoes de movimento ja se leva em conta as casas que a peca poder conquistar a outra peca
//Neste caso, tambem estamos a checar se o Peao tem algum obstaculo
ListaPosicao MovimentoPeao(Tabuleiro t, Posicao p) {
	PECA peca = RetornarPeca(t, p);
	ListaPosicao res = ListaVazia();

	Posicao frentep = ParaFrente(peca, p);

	if (RetornarPeca(t,frentep) == 0)  AdicionarPos(frentep, &res);

	if (p.x == 1 || p.x == 6) 
	{ //se esta na posicao original
		if (RetornarPeca(t, frentep) == 0) {
			if (RetornarPeca(t, ParaFrente(peca, frentep)) == 0)  AdicionarPos(ParaFrente(peca, frentep), &res);
		}
	}
	//RetonarPeca Retorna nulo caso seja uma posicao invalida
	//Por exemplo, o peao preto na coluna 0, nao tem esquerda. Seria -1, que nao � uma posicao valida do tabuleiro
	Posicao frente_esq_p = ParaEsquerda(frentep); 
	PECA fe = RetornarPeca(t, frente_esq_p);
	if (OutraCor(peca, fe)) AdicionarPos(frente_esq_p, &res);
	
	//Notar que OutraCor retorna um bool, caso duas pecas sejam de cor diferentes, Ou seja, inimigas
	Posicao frente_dir_p = ParaDireita(frentep);
	PECA fd = RetornarPeca(t, frente_dir_p);
	if (OutraCor(peca, fd)) AdicionarPos(frente_dir_p, &res);

	return res;
}


ListaPosicao MovimentoCavalo(Tabuleiro t, Posicao p) 
{
	PECA peca = RetornarPeca(t, p);
	ListaPosicao res = ListaVazia();

	Posicao frenCav = ParaFrente(peca, ParaFrente(peca, p)); // Movimentar 2 para frente
	Posicao esqCav = ParaEsquerda(ParaEsquerda(p));// Movimentar 2 para esquerda
	Posicao dirCav = ParaDireita(ParaDireita(p)); //Movimentar 2 para direita 
	Posicao baiCav = ParaTras(peca, ParaTras(peca, p)); //Movimenta 2 para rtas


	if (peca > 0) { //PARA OS CAVALOS BRANCOS

			//Pra cima Direita
		if (RetornarPeca(t, ParaDireita(frenCav)) <= 0)
		{
			Posicao novaPosicao = ParaDireita(frenCav);
			AdicionarPos(novaPosicao, &res);

		}
		//Pra cima esquerda
		if (RetornarPeca(t, ParaEsquerda(frenCav)) <= 0)
		{
			Posicao novaPosicao1 = ParaEsquerda(frenCav);
			AdicionarPos(novaPosicao1, &res);
		}
		//Pro meio direita cima 
		if (RetornarPeca(t, ParaFrente(peca, dirCav)) <= 0)
		{
			Posicao novaPosica3 = ParaFrente(peca, dirCav);
			AdicionarPos(novaPosica3, &res);
		}
		//Pro meio direita baixo
		if (RetornarPeca(t, ParaTras(peca, dirCav)) <= 0)
		{
			Posicao novaPosica4 = ParaTras(peca, dirCav);
			AdicionarPos(novaPosica4, &res);
		}
		//Pro meio esquerda cima 
		if (RetornarPeca(t, ParaFrente(peca, esqCav)) <= 0)
		{
			Posicao novaPosica5 = ParaFrente(peca, esqCav);
			AdicionarPos(novaPosica5, &res);
		}

		//Pro meio esquerda baixo
		if (RetornarPeca(t, ParaTras(peca, esqCav)) <= 0)
		{
			Posicao novaPosica6 = ParaTras(peca, esqCav);
			AdicionarPos(novaPosica6, &res);
		}

		//Pra baixo direita
		if (RetornarPeca(t, ParaDireita(baiCav)) <= 0)
		{
			Posicao novaPosicao7 = ParaDireita(baiCav);
			AdicionarPos(novaPosicao7, &res);
		}
		//Pra baixo esquerda
		if (RetornarPeca(t, ParaEsquerda(baiCav)) <= 0)
		{
			Posicao novaPosicao8 = ParaEsquerda(baiCav);
			AdicionarPos(novaPosicao8, &res);
		}
		else return res;
	}
	else // PARA OS CAVALOS PRETOS
	{
		//Pra cima Direita
		if (RetornarPeca(t, ParaDireita(frenCav)) >= 0)
		{
			Posicao novaPosicao = ParaDireita(frenCav);
			AdicionarPos(novaPosicao, &res);

		}
		//Pra cima esquerda
		if (RetornarPeca(t, ParaEsquerda(frenCav)) >= 0)
		{
			Posicao novaPosicao1 = ParaEsquerda(frenCav);
			AdicionarPos(novaPosicao1, &res);
		}
		//Pro meio direita cima 
		if (RetornarPeca(t, ParaFrente(peca, dirCav)) >= 0)
		{
			Posicao novaPosica3 = ParaFrente(peca, dirCav);
			AdicionarPos(novaPosica3, &res);
		}
		//Pro meio direita baixo
		if (RetornarPeca(t, ParaTras(peca, dirCav)) >= 0)
		{
			Posicao novaPosica4 = ParaTras(peca, dirCav);
			AdicionarPos(novaPosica4, &res);
		}
		//Pro meio esquerda cima 
		if (RetornarPeca(t, ParaFrente(peca, esqCav)) >= 0)
		{
			Posicao novaPosica5 = ParaFrente(peca,esqCav);
			AdicionarPos(novaPosica5, &res);
		}

		//Pro meio esquerda baixo
		if (RetornarPeca(t, ParaTras(peca, esqCav)) >= 0)
		{
			Posicao novaPosica6 = ParaTras(peca, esqCav);
			AdicionarPos(novaPosica6, &res);
		}

		//Pra baixo direita
		if (RetornarPeca(t, ParaDireita(baiCav)) >= 0)
		{
			Posicao novaPosicao7 = ParaDireita(baiCav);
			AdicionarPos(novaPosicao7, &res);
		}
		//Pra baixo esquerda
		if (RetornarPeca(t, ParaEsquerda(baiCav)) >= 0)
		{
			Posicao novaPosicao8 = ParaEsquerda(baiCav);
			AdicionarPos(novaPosicao8, &res);
		}
		else return res;
	}
	return res;
}


ListaPosicao MovimentoBispo(Tabuleiro t, Posicao p)
{
	PECA peca = RetornarPeca(t, p);
	ListaPosicao res = ListaVazia();

	int x = p.x;
	int y = p.y;

	//Pra diagonal superior direita 
	for (int i = x; i >= 0; i--)
	{
		p.x--;
		p.y++;
		if (RetornarPeca(t, p) == 0)
		{
			AdicionarPos(p, &res);
		}
		else if (!OutraCor(RetornarPeca(t, p), peca)) break;

		if (OutraCor(peca, RetornarPeca(t, p)))
		{
			AdicionarPos(p, &res);
			break;
		}
	}

	p.x = x;
	p.y = y;
	//Pra diagonal inferior direita
	for (int i = 0; i < 8; i++)
	{
		p.x++;
		p.y++;
		if (RetornarPeca(t, p) == 0)
		{
			AdicionarPos(p, &res);
		}

		else if (!OutraCor(RetornarPeca(t, p), peca)) break;

		else if (OutraCor(peca, RetornarPeca(t, p)))
		{
			AdicionarPos(p, &res);
			break;
		}
	}
	//Pra diagonal superior esquerda

	p.x = x;
	p.y = y;
	for (int i = x; i >= 0; i--)
	{
		p.x--;
		p.y--;
		if (RetornarPeca(t, p) == 0)
		{
			AdicionarPos(p, &res);
		}

		else if (!OutraCor(RetornarPeca(t, p), peca)) break;

		else if (OutraCor(peca, RetornarPeca(t, p)))
		{
			AdicionarPos(p, &res);
			break;
		}
	}

	p.x = x;
	p.y = y;
	//Pra diagonal inferior esquerda
	for (int i = y; i >= 0; i--)
	{
		p.x++;
		p.y--;
		if (RetornarPeca(t, p) == 0) 
		{
			AdicionarPos(p, &res);
		}

		else if (!OutraCor(RetornarPeca(t, p), peca)) break;

		else if (OutraCor(peca, RetornarPeca(t, p)))
		{
			AdicionarPos(p, &res);
			break;
		}
	}
	return res;
}


ListaPosicao MovimentoTorre(Tabuleiro t, Posicao p)
{
	PECA peca = RetornarPeca(t, p);
	ListaPosicao res = ListaVazia();
	int x = p.x;
	int y = p.y;

	//Para cima 
	for (int i = x; i >= 0 ; i--)
	{
		p.x--;

		if (RetornarPeca(t, p) == 0)
		{
			AdicionarPos(p, &res);
		}
		else if (!OutraCor(RetornarPeca(t, p), peca)) break;
	
		else if (OutraCor(RetornarPeca(t, p), peca)) {
			AdicionarPos(p, &res);
			break;
		}
	}

	p.x = x;
	p.y = y;
	//Para baixo
	for (int i = x; i < 8; i++)
	{

		p.x++;
		if (RetornarPeca(t, p) == 0)
		{
			AdicionarPos(p, &res);
		}

		else if (!OutraCor(RetornarPeca(t, p), peca)) break;
		
		else if (OutraCor(RetornarPeca(t, p), peca)) 
		{
			AdicionarPos(p, &res);
			break;
		}
	}
	p.x = x;
	p.y = y;
	//Para direita
	for (int i = y; i < 8; i++)
	{
		p.y++;
		 if (RetornarPeca(t, p) == 0)
		 { 
			AdicionarPos(p, &res);
		 }

		else if (!OutraCor(RetornarPeca(t, p), peca)) break;

		else if (OutraCor(RetornarPeca(t, p), peca)) 
		 {
			AdicionarPos(p, &res);
			break;
		}
	}
	p.x = x;
	p.y = y;
	//Para esquerda
	for (int i = y; i >= 0; i--)
	{
		p.y--;
		if (RetornarPeca(t, p) == 0)
		{
			AdicionarPos(p, &res);
		}

		else if (!OutraCor(RetornarPeca(t, p), peca)) break;

		else if (OutraCor(RetornarPeca(t, p), peca)) 
		{
			AdicionarPos(p, &res);
			break;
		}
	}
	return res;
}


ListaPosicao MovimentoRainha(Tabuleiro t, Posicao p)
{
	ListaPosicao lp = ListaVazia();
	AdicionarLista(MovimentoBispo(t,p), &lp);
	AdicionarLista(MovimentoTorre(t,p), &lp);
	return lp;
}


ListaPosicao MovimentoRei(Tabuleiro t, Posicao p)
{
	PECA peca = RetornarPeca(t, p);
	ListaPosicao lp = ListaVazia();
	if (peca > 0)
	{
		//Pra cima 
		if (RetornarPeca(t, ParaFrente(peca, p)) <= 0) AdicionarPos(ParaFrente(peca, p), &lp);
		//Pra direita 
		if (RetornarPeca(t, ParaDireita(p)) <= 0) AdicionarPos(ParaDireita(p), &lp);
		//Pra esquerda 
		if (RetornarPeca(t, ParaEsquerda(p)) <= 0) AdicionarPos(ParaEsquerda(p), &lp);
		//Pra baixo
		if (RetornarPeca(t, ParaTras(peca, p)) <= 0) AdicionarPos(ParaTras(peca, p), &lp);
		//Pra diagonal superior direita
		if (RetornarPeca(t, ParaFrente(peca, ParaDireita(p))) <= 0) AdicionarPos(ParaFrente(peca, ParaDireita(p)), &lp);
		//Pra diagonal superior esquerda
		if (RetornarPeca(t, ParaFrente(peca, ParaEsquerda(p))) <= 0) AdicionarPos(ParaFrente(peca, ParaEsquerda(p)), &lp);
		//Pra diagonal inferior direita 
		if (RetornarPeca(t, ParaTras(peca, ParaDireita(p))) <= 0) AdicionarPos(ParaTras(peca, ParaDireita(p)), &lp);
		//Pra diagonal inferior esquerda
		if (RetornarPeca(t, ParaTras(peca, ParaEsquerda(p))) <= 0) AdicionarPos(ParaTras(peca, ParaEsquerda(p)), &lp);
	}
	else
	{
		//Pra cima 
		if (RetornarPeca(t, ParaFrente(peca, p)) >= 0) AdicionarPos(ParaFrente(peca, p), &lp);
		//Pra direita 
		if (RetornarPeca(t, ParaDireita(p)) >= 0) AdicionarPos(ParaDireita(p), &lp);
		//Pra esquerda 
		if (RetornarPeca(t, ParaEsquerda(p)) >= 0) AdicionarPos(ParaEsquerda(p), &lp);
		//Pra baixo
		if (RetornarPeca(t, ParaTras(peca, p)) >= 0) AdicionarPos(ParaTras(peca, p), &lp);
		//Pra diagonal superior direita
		if (RetornarPeca(t, ParaFrente(peca, ParaDireita(p))) >= 0) AdicionarPos(ParaFrente(peca, ParaDireita(p)), &lp);
		//Pra diagonal superior esquerda
		if (RetornarPeca(t, ParaFrente(peca, ParaEsquerda(p))) >= 0) AdicionarPos(ParaFrente(peca, ParaEsquerda(p)), &lp);
		//Pra diagonal inferior direita 
		if (RetornarPeca(t, ParaTras(peca, ParaDireita(p))) >= 0) AdicionarPos(ParaTras(peca, ParaDireita(p)), &lp);
		//Pra diagonal inferior esquerda
		if (RetornarPeca(t, ParaTras(peca, ParaEsquerda(p))) >= 0) AdicionarPos(ParaTras(peca, ParaEsquerda(p)), &lp);
	}
	return lp;
}

//FIM DOS MOVIMENTOS DAS PEÇAS


//Retira todas as posicoes que iriam para fora da matriz do tabuleiro
void RetirarPosOOB/*out of bounds*/(Tabuleiro t, ListaPosicao* lp) 
{
	int i = 0;
	while(i < lp->usados)
	{
		if (lp->pos[i].x > 7 || lp->pos[i].x < 0) 
		{
			RetirarPos(lp->pos[i], lp);
			continue;
		} 
		else if (lp->pos[i].y > 7 || lp->pos[i].y < 0) 
		{
			RetirarPos(lp->pos[i], lp);
			continue;
		}
		i++;
	}
}

//Retira todas as posicoes que iriam permitir que duas pecas aliadas ficassem na mesma coordenada
void RetirarPosRedundantes(Tabuleiro t, ListaPosicao* lp,Posicao p) {
	PECA peca = RetornarPeca(t, p);
	int i = 0;
	if (peca>0) 
	{
		while (i <= lp->usados) {
			if (RetornarPeca(t, lp->pos[i]) > 0) 
			{
				RetirarPos(lp->pos[i], lp);
				continue;
			}
			i++;
		}
	}
	else if(peca<0) 
	{	
		while (i <= lp->usados) 
		{
			if (RetornarPeca(t, lp->pos[i]) < 0) 
			{
				RetirarPos(lp->pos[i], lp);
				continue;
			}
			i++;
		}
	}
}

//Utilizamos esta função para remover tanto posicoes fora do tabuleiro como redundantes
void RetirarPosInvalidas(Tabuleiro t, ListaPosicao* lp, Posicao p) 
{
	RetirarPosRedundantes(t, lp, p);
	RetirarPosOOB(t, lp);
}



//Assume-se que existe uma peca na posicao old, e que a posicao nova vem de uma lista das posicoes possiveis para aquela peca, caso contrario comportamento indefinido
Tabuleiro Movimentar(Tabuleiro t, Posicao old, Posicao nova) 
{
	t.tabuleiro[nova.x][nova.y] = t.tabuleiro[old.x][old.y];
	t.tabuleiro[old.x][old.y] = 0;
	return t;
}

//Funcao que ira retonar uma lista com os possiveis movimentos de todas as pecas de um dado jogador.
ListaPosicao PosicoesDisponiveis(Tabuleiro t, Jogador j)
{
	//Comecamos a verificar a cor do jogador no qual queremos obter a lista total de movimentos
	int cor;
	if (j == Branco) cor = 1;
	else cor = -1;

	//Assim sendo, iremos percorrer todo o tabuleiro 
	ListaPosicao total = ListaVazia();
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			Posicao p = NewPos(x, y);
			PECA peca = RetornarPeca(t, p);

			//Caso a peca num tabuleiro seja da cor do nosso jogador actual, entao adicionar todos os possiveis movimentos dessas pecas na lista total
			if (!OutraCor(peca, cor)) {
				switch (peca) {
				case PEAO:
				{
					ListaPosicao movpeao = MovimentoPeao(t, p);
					RetirarPosInvalidas(t, &movpeao, p);
					AdicionarLista(movpeao, &total);
					break;
				}
				case CAVALO:
				{
					ListaPosicao movcavalo = MovimentoCavalo(t, p);
					RetirarPosInvalidas(t, &movcavalo, p);
					AdicionarLista(movcavalo, &total);
					break;
				}
				case BISPO:
				{
					ListaPosicao movbispo = MovimentoBispo(t, p);
					RetirarPosInvalidas(t, &movbispo, p);
					AdicionarLista(movbispo, &total);
					break;
				}
				case TORRE:
				{
					ListaPosicao movtorre = MovimentoTorre(t, p);
					RetirarPosInvalidas(t, &movtorre, p);
					AdicionarLista(movtorre, &total);
					break;
				}
				case RAINHA:
				{
					ListaPosicao movrainha = MovimentoRainha(t, p);
					RetirarPosInvalidas(t, &movrainha, p);
					AdicionarLista(movrainha, &total);
					break; 
				}
				case REI:
				{
					ListaPosicao movrei = MovimentoRei(t, p);
					RetirarPosInvalidas(t, &movrei, p);
					AdicionarLista(movrei, &total);
					break;
				}
				case 0:
					break;
				}
			}
		}
	}
	return total;
}

//Retorna true se o jogador j colocou o outro jogador em xeque
bool Xeque(Tabuleiro t, Jogador j) {
	ListaPosicao aux = ListaVazia();
	
	aux = PosicoesDisponiveis(t, j);
	Posicao rei;
	if (j == Branco) rei = *PosicaoRei(t, COR_PRETO);
	else rei = *PosicaoRei(t, COR_BRANCO);

	for (int i = 0; i < aux.usados; i++) {
		if (PosEQ(rei, aux.pos[i])) return true;
	}
	return false;
}


bool XequeMate(Tabuleiro t, Jogador j) {
	ListaPosicao lp = ListaVazia();

	//Verificamos se o Rei esta em xeque a tem 0 movimentos possiveis na sua Lista de Posicoes 
	if (j == Branco) {
		Posicao reiPreto = *PosicaoRei(t, COR_PRETO);
		if (Xeque(t, j)) {
			RetirarPosicoesEmXeque(PosicoesDisponiveis(t, j), MovimentoRei(t, reiPreto));
			return lp.usados == 0;
		}
	}
	else {
		Posicao reiBranco = *PosicaoRei(t, COR_BRANCO);
		if (Xeque(t, j)) {
			RetirarPosicoesEmXeque(PosicoesDisponiveis(t, j), MovimentoRei(t, reiBranco));
			return lp.usados == 0;
		}
	}
	return false;
}


//Duas funcoes para implementacao do Roque
void AddRoque(Tabuleiro t, Posicao p, ListaPosicao* lp) {
	PECA peca = RetornarPeca(t, p);

	//Se o rei for branco
	if (peca == BRANCO(REI)) {   
		if (p.x == 0 && p.y == 4) {
			//Checamos se as torres estao nas posicoes certas e se do rei ate a torre as Posicoes estao vazias
			if (t.tabuleiro[p.x][p.y + 1] == 0 && t.tabuleiro[p.x][p.y + 2] == 0 && t.tabuleiro[p.x][p.y + 3] == BRANCO(TORRE)) {
				Posicao nova;
				nova.x = p.x;
				nova.y = p.y + 2;
				AdicionarPos(nova, lp);
			}
			else if (t.tabuleiro[p.x][p.y - 1] == 0 && t.tabuleiro[p.x][p.y - 2] == 0 && t.tabuleiro[p.x][p.y - 3] == 0 && t.tabuleiro[p.x][p.y - 4] == BRANCO(TORRE)) {
				Posicao nova;
				nova.x = p.x;
				nova.y = p.y - 3;
				AdicionarPos(nova, lp);
			}
		}
	}
	//Se o rei for preto
	if (peca == PRETO(REI)) { 
		if (p.x == 7 && p.y == 4) {
			//Checamos se as torres estao nas posicoes certas e se do rei ate a torre as Posicoes estao vazias
			if (t.tabuleiro[p.x][p.y + 1] == 0 && t.tabuleiro[p.x][p.y + 2] == 0 && t.tabuleiro[p.x][p.y + 3] == PRETO(TORRE)) {
				Posicao nova;
				nova.x = p.x;
				nova.y = p.y + 2;
				AdicionarPos(nova, lp);
			}
			else if (t.tabuleiro[p.x][p.y - 1] == 0 && t.tabuleiro[p.x][p.y - 2] == 0 && t.tabuleiro[p.x][p.y - 3] == 0 && t.tabuleiro[p.x][p.y - 4] == PRETO(TORRE)) {
				Posicao nova;
				nova.x = p.x;
				nova.y = p.y - 3;
				AdicionarPos(nova, lp);
			}
		}
	}
}

Tabuleiro Roque(Tabuleiro t, Posicao old, Posicao nova) {
	PECA peca = RetornarPeca(t, old);
	Tabuleiro tnovo;

	if (abs(nova.y - old.y) == 2) {
		if (peca == abs(REI)) {
			Posicao torre; torre.x = old.x; torre.y = 7;
			Posicao torreNova; torreNova.x = torre.x; torreNova.y = torre.y - 2;
			tnovo = Movimentar(t, torre, torreNova);
		}
	}
	else if (abs(nova.y - old.y) == 3) {
		if (peca == abs(REI)) {
			Posicao torre; torre.x = old.x; torre.y = 0;
			Posicao torreNova; torreNova.x = torre.x; torreNova.y = torre.y + 2;
			tnovo = Movimentar(t, torre, torreNova);
		}
	}
	return tnovo;
}

//Funcao que retornar 1 valor aleatorio sendo ele 0 ou 1.
int randomPlayer() {
	int i;
	srand((unsigned int)time(NULL));

	for (i = 0; i < 1; i++)
		return (rand() % 2);
}