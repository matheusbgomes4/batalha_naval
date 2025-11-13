#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

#define VALOR_HABILIDADE 5


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

    // 2. Posicionar Navios (4 navios, incluindo diagonais)
    // Direções: 0=Horizontal, 1=Vertical, 2=Diagonal Principal (L+C+), 3=Diagonal Secundária (L+C-)

    // Navio 1: Horizontal (Início: 2, 1) 
    if (posicionar_navio(tabuleiro, 2, 1, 0)) {
        printf("Navio 1 (Horizontal) posicionado em (2, 1).\n");
    }

    // Navio 2: Vertical (Início: 6, 8) 
    if (posicionar_navio(tabuleiro, 6, 8, 1)) {
        printf("Navio 2 (Vertical) posicionado em (6, 8).\n");
    }

    // Navio 3: Diagonal Principal (L+C+, Início: 1, 5) -
    if (posicionar_navio(tabuleiro, 1, 5, 2)) {
        printf("Navio 3 (Diagonal Principal) posicionado em (1, 5).\n");
    }

    // Navio 4: Diagonal Secundária (L+C-, Início: 7, 3) -
    if (posicionar_navio(tabuleiro, 7, 3, 3)) {
        printf("Navio 4 (Diagonal Secundária) posicionado em (7, 3).\n");
    }

    // 3. Exibir o Tabuleiro
    printf("\n--- Tabuleiro Nível Aventureiro ---\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Posiciona um navio no tabuleiro, validando limites e sobreposição.
 * @param direcao 0=Horizontal, 1=Vertical, 2=Diagonal Principal, 3=Diagonal Secundária.
 * @return 1 se posicionado com sucesso, 0 caso contrário.
 */
int posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int direcao) {
    int dl, dc; // Variações de linha e coluna

    // Determina a variação de linha e coluna com base na direção
    switch (direcao) {
        case 0: dl = 0; dc = 1; break; // Horizontal
        case 1: dl = 1; dc = 0; break; // Vertical
        case 2: dl = 1; dc = 1; break; // Diagonal Principal (L+C+)
        case 3: dl = 1; dc = -1; break; // Diagonal Secundária (L+C-)
        default: return 0;
    }

    // 1. Validação (Limites e Sobreposição)
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int i = linha_inicial + k * dl;
        int j = coluna_inicial + k * dc;

        if (i < 0 || i >= TAMANHO_TABULEIRO || j < 0 || j >= TAMANHO_TABULEIRO || tabuleiro[i][j] == VALOR_NAVIO) {
            return 0; // 
        }
    }

    // 2. Posicionamento
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        tabuleiro[linha_inicial + k * dl][coluna_inicial + k * dc] = VALOR_NAVIO;
    }
    return 1;
}

/**
 * @brief
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