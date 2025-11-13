#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Protótipos
int posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int direcao);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // 1. Inicializar Tabuleiro com Água (0)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // 2. Posicionar Navios (Direções: 0=Horizontal, 1=Vertical)

    // Navio 1: Horizontal (Início: 2, 1)
    if (posicionar_navio(tabuleiro, 2, 1, 0)) {
        printf("Navio Horizontal posicionado em (2, 1).\n");
    }

    // Navio 2: Vertical (Início: 6, 8)
    if (posicionar_navio(tabuleiro, 6, 8, 1)) {
        printf("Navio Vertical posicionado em (6, 8).\n");
    }

    // 3. Exibir o Tabuleiro
    printf("\n--- Tabuleiro Nível Novato ---\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Posiciona um navio no tabuleiro, validando limites.
 * @param direcao 0=Horizontal, 1=Vertical.
 * @return 1 se posicionado com sucesso, 0 caso contrário.
 */
int posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int direcao) {
    int dl = (direcao == 1); // Variação de Linha (1 para Vertical, 0 para Horizontal)
    int dc = (direcao == 0); // Variação de Coluna (1 para Horizontal, 0 para Vertical)

    // 1. Validação de Limites
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int i = linha_inicial + k * dl;
        int j = coluna_inicial + k * dc;

        if (i < 0 || i >= TAMANHO_TABULEIRO || j < 0 || j >= TAMANHO_TABULEIRO || tabuleiro[i][j] == VALOR_NAVIO) {
            // A validação de sobreposição (tabuleiro[i][j] == VALOR_NAVIO) é mantida para ser robusta.
            return 0; // Fora dos limites ou sobreposto
        }
    }

    // 2. Posicionamento
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        tabuleiro[linha_inicial + k * dl][coluna_inicial + k * dc] = VALOR_NAVIO;
    }
    return 1;
}

/**
 * @brief Exibe o tabuleiro no console.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Cabeçalho das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n  -----------------------\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Marcador da linha
        printf("%d |", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf(" |\n");
    }
    printf("  -----------------------\n");
}