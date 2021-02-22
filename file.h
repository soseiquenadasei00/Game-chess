#include <stdio.h>
#include "logica.h"
#include "camadaDeDados.h"
#include "chess.h"
#include <string.h>


void SalvarJogo(char* filename, Tabuleiro t, char branco[TAMANHO], char preto[TAMANHO]);
void LoadGame(char* filename, Tabuleiro* t, char* branco[TAMANHO], char* preto[TAMANHO]);