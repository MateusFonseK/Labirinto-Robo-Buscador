#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_LINHAS 50
#define MAX_COLUNAS 50

// Declarando variaveis globais
char labirinto[MAX_LINHAS][MAX_COLUNAS];
int linhas, colunas;

// Fun��o para imprimir o labirinto em um arquivo
void imprime_labirinto_arquivo(const char *nome_arquivo) {
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "w"); // Abre o arquivo para escrita

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("N�o foi poss�vel criar o arquivo.\n");
        exit(1);
    }

    int i, j; 
    // Percorrer o labirinto e escrever no arquivo
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            fprintf(arquivo, "%c ", labirinto[i][j]); 
        }
        fprintf(arquivo, "\n"); // Pula para a pr�xima linha do labirinto no arquivo
    }

    fclose(arquivo); 
    printf("Labirinto com o percurso do rob� foi salvo no arquivo 'saida.txt'.\n");
}

// Fun��o para encontrar o caminho no labirinto
int backtracking(int x, int y) {
	
	// Verifica se a posi��o atual � a sa�da
    if (labirinto[x][y] == 'S') 
        return 1;

	// Verifica se a posi��o atual � uma parede ou j� foi visitada
    if (labirinto[x][y] == '#' || labirinto[x][y] == 'o') 
        return 0;
	
	// Marca a posi��o atual como visitada
    labirinto[x][y] = 'o'; 


	// Verifica se � poss�vel mover para cima 
    if (x > 0 && backtracking(x - 1, y))
        return 1;

    // Verifica se � poss�vel mover para a direita 
    if (y < colunas - 1 && backtracking(x, y + 1))
        return 1;

    // Verifica se � poss�vel mover para baixo 
    if (x < linhas - 1 && backtracking(x + 1, y))
        return 1;

    // Verifica se � poss�vel mover para a esquerda 
    if (y > 0 && backtracking(x, y - 1))
        return 1;
	
	// Marca a posi��o atual como n�o visitada
    labirinto[x][y] = '.'; 
    return 0;
}

// ler arquivo
void ler_labirinto_arquivo(const char *nome_arquivo) {
    FILE *arquivo;
    
    // Abre o arquivo para leitura
    arquivo = fopen(nome_arquivo, "r"); 

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("N�o foi poss�vel abrir o arquivo.\n");
        exit(1);
    }

    // Definindo linha e coluna
    fscanf(arquivo, "%d %d", &linhas, &colunas);

    // Verifica se as dimens�es do labirinto n�o excedem o m�ximo suportado
    if (linhas > MAX_LINHAS || colunas > MAX_COLUNAS) {
        printf("As dimens�es do labirinto no arquivo excedem o m�ximo suportado.\n");
        fclose(arquivo); // Fecha o arquivo
        exit(1);
    }

    int i, j; 
    
    // Loop para ler os caracteres do labirinto do arquivo
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            fscanf(arquivo, " %c", &labirinto[i][j]); // L� o caractere do arquivo
        }
    }
	
	// Fecha o arquivo
    fclose(arquivo); 
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    ler_labirinto_arquivo("labirinto.txt"); 

    int i, j; 
    
    // Encontrando a posi��o inicial do rob� (E) no labirinto
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            if (labirinto[i][j] == 'E') { // Se encontrar a posi��o inicial do rob�
                if (backtracking(i, j)) { // Chama a fun��o de backtracking para tentar encontrar o caminho para a saida
                    printf("\nCaminho encontrado!\n");
                    imprime_labirinto_arquivo("saida.txt"); // Imprime o labirinto com o percurso do rob� no arquivo "saida.txt"
                    return 0;
                } else {
                    printf("\n\nLabirinto sem sa�da!\n");
                    return 0;
                }
            }
        }
    }

    printf("\n\nLabirinto sem entrada!\n");
    return 0;
}
