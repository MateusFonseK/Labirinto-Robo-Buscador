#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_LINHAS 50
#define MAX_COLUNAS 50

// Declarando variaveis globais
char labirinto[MAX_LINHAS][MAX_COLUNAS];
int linhas, colunas;

// Função para imprimir o labirinto em um arquivo
void imprime_labirinto_arquivo(const char *nome_arquivo) {
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "w"); // Abre o arquivo para escrita

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Não foi possível criar o arquivo.\n");
        exit(1);
    }

    int i, j; 
    // Percorrer o labirinto e escrever no arquivo
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            fprintf(arquivo, "%c ", labirinto[i][j]); 
        }
        fprintf(arquivo, "\n"); // Pula para a próxima linha do labirinto no arquivo
    }

    fclose(arquivo); 
    printf("Labirinto com o percurso do robô foi salvo no arquivo 'saida.txt'.\n");
}

// Função para encontrar o caminho no labirinto
int backtracking(int x, int y) {
	
	// Verifica se a posição atual é a saída
    if (labirinto[x][y] == 'S') 
        return 1;

	// Verifica se a posição atual é uma parede ou já foi visitada
    if (labirinto[x][y] == '#' || labirinto[x][y] == 'o') 
        return 0;
	
	// Marca a posição atual como visitada
    labirinto[x][y] = 'o'; 


	// Verifica se é possível mover para cima 
    if (x > 0 && backtracking(x - 1, y))
        return 1;

    // Verifica se é possível mover para a direita 
    if (y < colunas - 1 && backtracking(x, y + 1))
        return 1;

    // Verifica se é possível mover para baixo 
    if (x < linhas - 1 && backtracking(x + 1, y))
        return 1;

    // Verifica se é possível mover para a esquerda 
    if (y > 0 && backtracking(x, y - 1))
        return 1;
	
	// Marca a posição atual como não visitada
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
        printf("Não foi possível abrir o arquivo.\n");
        exit(1);
    }

    // Definindo linha e coluna
    fscanf(arquivo, "%d %d", &linhas, &colunas);

    // Verifica se as dimensões do labirinto não excedem o máximo suportado
    if (linhas > MAX_LINHAS || colunas > MAX_COLUNAS) {
        printf("As dimensões do labirinto no arquivo excedem o máximo suportado.\n");
        fclose(arquivo); // Fecha o arquivo
        exit(1);
    }

    int i, j; 
    
    // Loop para ler os caracteres do labirinto do arquivo
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            fscanf(arquivo, " %c", &labirinto[i][j]); // Lê o caractere do arquivo
        }
    }
	
	// Fecha o arquivo
    fclose(arquivo); 
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    ler_labirinto_arquivo("labirinto.txt"); 

    int i, j; 
    
    // Encontrando a posição inicial do robô (E) no labirinto
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            if (labirinto[i][j] == 'E') { // Se encontrar a posição inicial do robô
                if (backtracking(i, j)) { // Chama a função de backtracking para tentar encontrar o caminho para a saida
                    printf("\nCaminho encontrado!\n");
                    imprime_labirinto_arquivo("saida.txt"); // Imprime o labirinto com o percurso do robô no arquivo "saida.txt"
                    return 0;
                } else {
                    printf("\n\nLabirinto sem saída!\n");
                    return 0;
                }
            }
        }
    }

    printf("\n\nLabirinto sem entrada!\n");
    return 0;
}
