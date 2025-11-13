#include <stdio.h>
#include <stdlib.h> // 

// Definições de constantes para o tabuleiro
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5 // Novo valor para área de efeito

// Definições de constantes para as matrizes de habilidade
#define TAMANHO_HABILIDADE 5 // Tamanho fixo da matriz de habilidade (ex: 5x5)
#define VALOR_AFETADO 1
#define VALOR_NAO_AFETADO 0


// Protótipos de Funções
int posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int direcao);
void criar_habilidade_cone(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_habilidade_cruz(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_habilidade_octaedro(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha_origem, int coluna_origem);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);


int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // 1. Inicializar Tabuleiro com Água (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // 2. Posicionar Navios
    // Direções: 0=H, 1=V, 2=Diag P, 3=Diag S
    posicionar_navio(tabuleiro, 2, 1, 0); // Horizontal
    posicionar_navio(tabuleiro, 6, 8, 1); // Vertical
    posicionar_navio(tabuleiro, 1, 5, 2); // Diagonal Principal
    posicionar_navio(tabuleiro, 7, 3, 3); // Diagonal Secundária

    // 3. Integrar Habilidades Especiais
    printf("--- Integrando Habilidades Especiais ---\n");

    // Habilidade 1: Cone (Origem: Linha 0, Coluna 0)
    criar_habilidade_cone(matriz_habilidade);
    sobrepor_habilidade(tabuleiro, matriz_habilidade, 0, 0);
    printf("- Habilidade Cone (Origem: 0, 0) integrada.\n");

    // Habilidade 2: Cruz (Origem: Linha 9, Coluna 5)
    criar_habilidade_cruz(matriz_habilidade);
    sobrepor_habilidade(tabuleiro, matriz_habilidade, 9, 5);
    printf("- Habilidade Cruz (Origem: 9, 5) integrada.\n");

    // Habilidade 3: Octaedro (Losango) (Origem: Linha 4, Coluna 5)
    criar_habilidade_octaedro(matriz_habilidade);
    sobrepor_habilidade(tabuleiro, matriz_habilidade, 4, 5);
    printf("- Habilidade Octaedro (Origem: 4, 5) integrada.\n");


    // 4. Exibir o Tabuleiro Final
    printf("\n--- Tabuleiro Final Nível Mestre ---\n");
    printf("Legenda: '0'=Água, '3'=Navio, '5'=Área de Habilidade\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}


int posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int direcao) {
    int dl, dc;
    switch (direcao) {
        case 0: dl = 0; dc = 1; break;
        case 1: dl = 1; dc = 0; break;
        case 2: dl = 1; dc = 1; break;
        case 3: dl = 1; dc = -1; break;
        default: return 0;
    }
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int i = linha_inicial + k * dl;
        int j = coluna_inicial + k * dc;
        if (i < 0 || i >= TAMANHO_TABULEIRO || j < 0 || j >= TAMANHO_TABULEIRO || tabuleiro[i][j] == VALOR_NAVIO) {
            return 0;
        }
    }
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        tabuleiro[linha_inicial + k * dl][coluna_inicial + k * dc] = VALOR_NAVIO;
    }
    return 1;
}

/**
 * @brief Cria a matriz de habilidade em formato de Cone (apontando para baixo).
 */
void criar_habilidade_cone(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        int distancia_horizontal = i; // A base do cone cresce com a linha (i)
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int dist_abs = abs(j - centro);
            if (dist_abs <= distancia_horizontal && i < (TAMANHO_HABILIDADE/2) + 1) { 
                matriz_habilidade[i][j] = VALOR_AFETADO;
            } else {
                matriz_habilidade[i][j] = VALOR_NAO_AFETADO;
            }
        }
    }
}

/**
 * @brief Cria a matriz de habilidade em formato de Cruz, centrada.
 */
void criar_habilidade_cruz(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                matriz_habilidade[i][j] = VALOR_AFETADO;
            } else {
                matriz_habilidade[i][j] = VALOR_NAO_AFETADO;
            }
        }
    }
}

/**
 * @brief Cria a matriz de habilidade em formato de Octaedro (Losango), centrada.
 */
void criar_habilidade_octaedro(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    int max_dist = centro;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Distância de Manhattan: |i - centro| + |j - centro| <= raio
            int dist_manhattan = abs(i - centro) + abs(j - centro);
            if (dist_manhattan <= max_dist) {
                matriz_habilidade[i][j] = VALOR_AFETADO;
            } else {
                matriz_habilidade[i][j] = VALOR_NAO_AFETADO;
            }
        }
    }
}

/**
 * @brief Sobrepõe a matriz de habilidade no tabuleiro principal, centrada na origem.
 */
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha_origem, int coluna_origem) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha_tab = linha_origem + (i - centro);
            int coluna_tab = coluna_origem + (j - centro);

            // Validação de Limites
            if (linha_tab >= 0 && linha_tab < TAMANHO_TABULEIRO &&
                coluna_tab >= 0 && coluna_tab < TAMANHO_TABULEIRO) {

                // Se a posição da habilidade está ativa (1) e a posição no tabuleiro não é água (0), marca como 5
                // Simplificação: A habilidade marca sua área de efeito (5) sobre navios (3) ou água (0)
                if (matriz_habilidade[i][j] == VALOR_AFETADO) {
                    tabuleiro[linha_tab][coluna_tab] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

/**
 * @brief Exibe o tabuleiro no console.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n  -----------------------\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d |", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf(" |\n");
    }
    printf("  -----------------------\n");
}