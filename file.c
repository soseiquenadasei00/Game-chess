#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "logica.h"
#include "camadaDeDados.h"
#include "chess.h"
#include <string.h>


void SalvarJogo(char* filename, Tabuleiro t, char branco[TAMANHO1], char preto[TAMANHO1]) {
	FILE* fd;

	fd = fopen(filename, "w");
	if (fd == NULL) {
		printf("Nao consegui abrir o ficheiro");
		return;
	}
	printf("Salvando em %s\n", filename);
	fwrite(&t, sizeof(Tabuleiro), 1, fd);
	fputs(branco, fd);
	fprintf(fd, "\n");
	fputs(preto, fd);

	fclose(fd);
}



void LoadGame(char* filename, Tabuleiro* t, char* branco[TAMANHO1], char* preto[TAMANHO1]) {
	FILE* fd;

	fd = fopen(filename, "r");
	if (fd == NULL) {
		printf("Nao consegui abrir o ficheiro");
		return;
	}
	fread(t, sizeof(Tabuleiro), 1, fd);
	fgets(branco, TAMANHO1, fd);
	fgets(preto,  TAMANHO1, fd);
	fclose(fd);
}