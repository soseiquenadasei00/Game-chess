#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"
#include "file.h"
#include "CamadadeDados.h"
#include "Logica.h"


//TODA A LOGICA DO JOGO

//Mostra o tabuleiro com base no estado atual 
void tabuleiroPrint(Tabuleiro t)
{
    int i, j;
    int c = 0, k = 0, g = 0;
    //Branco= minuscula e Preta = maiscula
    char peao = 'p', cavalo = 'h', torre = 't', bispo = 'b', rainha = 'q', rei = 'k', Peao = 'P', Cavalo = ' H', Torre = 'T', Bispo = 'B', Rainha = 'Q', Rei = 'K';

    printf("\n    A B C D E F G H\n");
   
    printf("  x-----------------x");
    printf("\n");
    for (i = 0; i < 8; i++)
    {
       
        
        printf("%d | ", k + 1);
        k++;
        
        for (j = 0; j < 8; j++)
        {
            
            if (t.tabuleiro[i][j] == 1) printf("%c ", Peao);
            else if (t.tabuleiro[i][j] == 2) printf("%c ", Cavalo);
            else if (t.tabuleiro[i][j] == 3) printf("%c ", Bispo);
            else if (t.tabuleiro[i][j] == 4) printf("%c ", Torre);
            else if (t.tabuleiro[i][j] == 5) printf("%c ", Rainha);
            else if (t.tabuleiro[i][j] == 6) printf("%c ", Rei);

            //Pe�as Pretas
            else if (t.tabuleiro[i][j] == (-1)) printf("%c ", peao);
            else if (t.tabuleiro[i][j] == (-2)) printf("%c ", cavalo);
            else if (t.tabuleiro[i][j] == (-3)) printf("%c ", bispo);
            else if (t.tabuleiro[i][j] == (-4)) printf("%c ", torre);
            else if (t.tabuleiro[i][j] == (-5)) printf("%c ", rainha);
            else if (t.tabuleiro[i][j] == (-6)) printf("%c ", rei);

            else if ((i + j) % 2 == 0) printf("  ");
            else printf("X ");

        }

        printf("| %d\n", c + 1);
        c++;
    }
    printf("  x-----------------x");
    printf("\n    A B C D E F G H\n");
    
}

Posicao GetPosicao() // Retorna uma posicao (peca que utilizador quer)
{
    Posicao novaPosicao;

    printf("Indique qual a linha, e aperte enter\n");
    int i;
    scanf("%d%*c", &i);
    i = i - 1;
    printf("Indique qual a coluna\n");
    char j;
    scanf("%c%*c", &j);
    novaPosicao.x = i;
    switch (j) {
    case 'A': novaPosicao.y = 0; break;
    case 'B': novaPosicao.y = 1; break;
    case 'C': novaPosicao.y = 2; break;
    case 'D': novaPosicao.y = 3; break;
    case 'E': novaPosicao.y = 4; break;
    case 'F': novaPosicao.y = 5; break;
    case 'G': novaPosicao.y = 6; break;
    case 'H': novaPosicao.y = 7; break;
    case 'a': novaPosicao.y = 0; break;
    case 'b': novaPosicao.y = 1; break;
    case 'c': novaPosicao.y = 2; break;
    case 'd': novaPosicao.y = 3; break;
    case 'e': novaPosicao.y = 4; break;
    case 'f': novaPosicao.y = 5; break;
    case 'g': novaPosicao.y = 6; break;
    case 'h': novaPosicao.y = 7; break;
    default: printf("Coordenada Invalida!"); break;
    }
    return novaPosicao;
}




void InicializacaoNovoJogo(char* branco[TAMANHO1], char* preto[TAMANHO1], Tabuleiro* t, Jogador* vezJog) 
{
    char j1[TAMANHO1], j2[TAMANHO1];
    *t = Novo_tabuleiro();
    printf("Jogador 1,insira seu nickname:\n");
    scanf(" %s%*c", j1);

    printf("Jogador 2, insira seu nickname:\n");
    scanf(" %s%*c", j2);

    if (randomPlayer() == 1)
    {
        printf("\nO %s ira controlar as pecas com letras Maiusculas, ou seja, as brancas\n", j1);
        printf("O %s ira controlar as pecas com letras minusculas, ou seja, as pretas. \n", j2);
        strcpy(branco, j1);
        strcpy(preto, j2);
    }
    else
    {
        printf("\nO %s ira controlar as pecas com letras Maiusculas, ou seja, as brancas\n", j2);
        printf("O %s ira controlar as pecas com letras minusculas, ou seja, as pretas. \n", j1);
        strcpy(preto, j1);
        strcpy(branco, j2);
    }
}

void InicializaJogoSalvo(char* branco[TAMANHO1], char* preto[TAMANHO1], Tabuleiro* t, Jogador* vezJog) {
    printf("Qual o nome do ficheiro?");
    char filename[TAMANHO1];
    scanf("%s%*c", &filename);
    LoadGame(filename, t, branco, preto);
    if (t->nJogadas % 2 == 0) {
        *vezJog = Preto;
    }
    else *vezJog = Branco;
}

void Inicializacao(char* branco[TAMANHO1], char* preto[TAMANHO1], Tabuleiro* t, Jogador *vezJog)
{
    char escolha = 0;
    while (!(escolha == 'n' || escolha == 'g')) {
        printf("Escolha se pretende iniciar [n]ovo jogo, ou continuar um jogo [g]ravado \n");
        scanf("%c%*c", &escolha);
    }
    if (escolha == 'n') {
        
        InicializacaoNovoJogo(branco, preto, t, &vezJog);
    }
    else {
        InicializaJogoSalvo(branco, preto, t, &vezJog);
    }
}


//Aqui fica o ciclo onde iremos rodar todo o jogo.
void interpretador()
{
    Tabuleiro t = Novo_tabuleiro();
    char branco[TAMANHO1], preto[TAMANHO1];
    Jogador vezJog;

    Inicializacao(&branco, &preto, &t, &vezJog);
    do  {
        
        //Troca dos jogadores
        if (t.nJogadas % 2 == 0) vezJog = Preto;
        else vezJog = Branco;

        tabuleiroPrint(t);
        int movimentou = 0;
        int selecionar = 0;
        Posicao mover;

            while (movimentou == 0)
            {
                //Mostrar de quem e a vez
                if (vezJog == Branco) printf("\n\n|Vez das brancas|  Jogador: %s", &branco);
                else printf("\n\n|Vez das pretas|  Jogador: %s", &preto);


                //Para selecionar a peca ou Salvar jogo
                char escolha = 0;
                while (!(escolha == 'j' || escolha == 's')) {
                    printf("\n[j]ogar ou [s]alvar?\n");
                    scanf("%c%*c", &escolha);
                } 
                if (escolha == 's') {
                    printf("Qual o nome do ficheiro?");
                    char filename[TAMANHO];
                    scanf("%s%*c", &filename);
                    SalvarJogo(filename, t, branco, preto);
                }


                Posicao check = GetPosicao();
                mover = check;
                if (RetornarPeca(t, check) == 0) {
                    printf("Nao ha nenhuma peca nessa posicao!\n");
                    continue;
                }
                PECA peca = RetornarPeca(t, check);
                //Nao deixar um jogador selecionar a peca de outro jogador.
                if (vezJog == Branco) {
                    if (peca < 0) {
                        printf("\nNao pode selecionar a peca do coleguinha!\n");
                        continue;
                    }
                }
                else {
                    if (peca > 0) {
                        printf("\nNao pode selecionar a peca do coleguinha!\n");
                        continue;
                    }
                }
                ListaPosicao lp = ListaVazia();
                //Mostrar a lista de jogadas
                switch (abs(peca)) {
                case PEAO:
                {
                    lp = MovimentoPeao(t, check);
                    break;
                }
                case CAVALO:
                {
                    lp = MovimentoCavalo(t, check);
                    break;
                }
                case BISPO:
                {
                    lp = MovimentoBispo(t, check);
                    break;
                }
                case TORRE:
                {
                    lp = MovimentoTorre(t, check);
                    break; 
                }
                case RAINHA:
                {
                    lp = MovimentoRainha(t, check);
                    break;
                }
                case REI:
                {
                    lp = MovimentoRei(t, check);
                    AddRoque(t, check, &lp);
                    break; 
                }
                case 0:
                {
                    printf("\nNao selecionou qualquer peca!\n");
                    continue;
                }
                }
                //Retira-se da lista qualquer movimento invalido!
                RetirarPosInvalidas(t, &lp, check);

                //Se a lista estiver vazia, nos notificamos o jogador dessa informacao dramatica, e o mesmo pode voltar a escolher uma peca.
                if (lp.usados == 0) {
                    printf("\nA peca nao tem movimentos validos!\n");
                    continue;
                }
                else 
                {
                    printf("Possiveis Movimentos: \n");
                    PrintarLista(&lp);
                }
                printf("\n");
                //Caso o jogador queira selecionar outra peca, ou mover a que ja selecionou
                printf("Digite 0 para selecionar outra peca, ou 1 para passar a mover a peca selecionada\n");
                scanf("%d%*c", &selecionar);
                if (selecionar == 0) continue;


                if (selecionar == 1) {
                    Posicao mover = GetPosicao();
                    selecionar == 0;
                    while (selecionar == 0) {
                        if ((mover.x >= 0 || mover.x < 8) && (mover.y >= 0 || mover.y < 8)) selecionar = 1;
                        else printf("Selecionou uma coordenada inexistente");
                    }
                    //Mecanica de Roque!!
                    if (RetornarPeca(t, check) == abs(REI)) {
                        if ((abs(mover.y - check.y) == 2) || (abs(mover.y - check.y) == 3)) {
                            t = Roque(t, check, mover);
                            t = Movimentar(t, check, mover);
                            movimentou = 1; 
                        }
                    }
                    //Aqui nos confirmamos que o jogador nao esta mexendo a Peca para uma posicao que nao consta na lista. Era legal comer a rainha com um peao na primeira ronda, nao era?
                    else {
                        for (int i = 0; i < lp.usados; i++) {
                            if (PosEQ(mover, lp.pos[i])) {
                                t = Movimentar(t, check, mover);
                                movimentou = 1;
                            }
                        }
                    }

                    //Depois de um movimento, verificamos se o jogador actual continua em Xeque. Se sim, recomeca-se o turno dele.
                    if (Xeque(t, OutroJogador(vezJog))) {
                        printf("\nO jogador %s continua em xeque!\n", JogadortoString(vezJog));
                        //Xeque desfaz o movimento!
                        t = Movimentar(t, mover, check);
                        movimentou = 0;
                        continue;
                    }
                }
                //Se o jogador errar o comando
                else {
                    printf("Nao percebi o comando, selecione a peca novamente!\n");
                    continue;
                }

                //Se algum jogador entrou em xeque
                if (Xeque(t, vezJog))  printf("O jogador %s esta em Xeque!", JogadortoString(vezJog));
            } 
            //fim do turno
            if (movimentou == 1) t.nJogadas++;
    } while (!XequeMate(t, vezJog));


    if (vezJog == 1) 
    {
        if (vezJog == Branco) printf("\n\n\nXeque-mate!! Vitoria do jogador Branco!, Parabens! %s", branco);
        else if (vezJog == Preto) printf("\n\n\nXeque-mate!! Vitoria do jogador Preto!, Parabens! %s", preto);
    }
    else 
    {
        if (vezJog == Branco) printf("\n\n\nXeque-mate!! Vitoria do jogador Branco!, Parabens! %s", preto);
        else if (vezJog == Preto) printf("\n\n\nXeque-mate!! Vitoria do jogador Preto!, Parabens! %s", branco);
    }
}



