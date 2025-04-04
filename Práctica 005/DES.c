
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// =================== TABLAS ===================

// Permutación inicial
int IP[64] = {
    58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
};

// Permutación final
int FP[64] = {
    40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
};

// Expansión
int E[48] = {
    32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,
    12,13,14,15,16,17,16,17,18,19,20,21,
    20,21,22,23,24,25,24,25,26,27,28,29,
    28,29,30,31,32,1
};

// Permutación P
int P[32] = {
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

// PC-1 y PC-2
int PC1[56] = {
    57,49,41,33,25,17,9,1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,21,13,5,28,20,12,4
};

int PC2[48] = {
    14,17,11,24,1,5,3,28,15,6,21,10,
    23,19,12,4,26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,51,45,33,48,
    44,49,39,56,34,53,46,42,50,36,29,32
};

int SHIFTS[16] = {1, 1, 2, 2, 2, 2, 2, 2,1, 2, 2, 2, 2, 2, 2, 1};

// S-Boxes (completas)
int S[8][4][16] = {
    { // S1
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    { // S2
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    { // S3
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    { // S4
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    { // S5
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    { // S6
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    { // S7
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    { // S8
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// =============== FUNCIONES AUXILIARES ===============

void permute(uint8_t in[64], uint8_t out[64], int table[64]) {
    for (int i = 0; i < 64; i++)
        out[i] = in[table[i] - 1];
}

void expansion(uint8_t in[32], uint8_t out[48]) {
    for (int i = 0; i < 48; i++)
        out[i] = in[E[i] - 1];
}

void xor48(uint8_t a[48], uint8_t b[48], uint8_t out[48]) {
    for (int i = 0; i < 48; i++)
        out[i] = a[i] ^ b[i];
}

void sbox(uint8_t in[48], uint8_t out[32]) {
    for (int i = 0; i < 8; i++) {
        int row = (in[i * 6] << 1) | in[i * 6 + 5];
        int col = (in[i * 6 + 1] << 3) | (in[i * 6 + 2] << 2) |
                  (in[i * 6 + 3] << 1) | in[i * 6 + 4];
        int val = S[i][row][col];
        for (int j = 0; j < 4; j++)
            out[i * 4 + j] = (val >> (3 - j)) & 1;
    }
}

void permuteP(uint8_t in[32], uint8_t out[32]) {
    for (int i = 0; i < 32; i++)
        out[i] = in[P[i] - 1];
}

void function_f(uint8_t R[32], uint8_t K[48], uint8_t out[32]) {
    uint8_t exp[48], xored[48], sbox_out[32];
    expansion(R, exp);
    xor48(exp, K, xored);
    sbox(xored, sbox_out);
    permuteP(sbox_out, out);
}

void generar_subclaves(uint8_t clave[64], uint8_t subclaves[16][48]) {
    uint8_t clave56[56];
    for (int i = 0; i < 56; i++)
        clave56[i] = clave[PC1[i] - 1];

    uint8_t C[28], D[28];
    memcpy(C, clave56, 28);
    memcpy(D, clave56 + 28, 28);

    for (int ronda = 0; ronda < 16; ronda++) {
        for (int r = 0; r < SHIFTS[ronda]; r++) {
            uint8_t tempC = C[0], tempD = D[0];
            for (int i = 0; i < 27; i++) {
                C[i] = C[i + 1];
                D[i] = D[i + 1];
            }
            C[27] = tempC;
            D[27] = tempD;
        }

        uint8_t CD[56];
        memcpy(CD, C, 28);
        memcpy(CD + 28, D, 28);

        for (int i = 0; i < 48; i++)
            subclaves[ronda][i] = CD[PC2[i] - 1];
    }
}

void hex_to_bits(char *hex, uint8_t *bits) {
    for (int i = 0; i < 16; i++) {
        uint8_t val = (hex[i] >= 'A') ? (hex[i] - 'A' + 10) : (hex[i] - '0');
        for (int j = 0; j < 4; j++) {
            bits[i * 4 + j] = (val >> (3 - j)) & 1;
        }
    }
}

void bits_to_hex(uint8_t *bits, char *hex) {
    for (int i = 0; i < 16; i++) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = (val << 1) | bits[i * 4 + j];
        }
        hex[i] = (val < 10) ? ('0' + val) : ('A' + val - 10);
    }
    hex[16] = '\0';
}

void mostrar_bits_hex(char *label, uint8_t *bits, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i += 4) {
        int val = (bits[i] << 3) | (bits[i + 1] << 2) | (bits[i + 2] << 1) | bits[i + 3];
        printf("%X", val);
    }
    printf("\n");
}

// =============== MAIN ===============

int main() {
    char mensaje_hex[17] = "0123456789ABCDEF";
    char clave_hex[17] = "133457799BBCDFF1";

    uint8_t mensaje_bits[64];
    uint8_t clave_bits[64];
    uint8_t subclaves[16][48];

    hex_to_bits(mensaje_hex, mensaje_bits);
    hex_to_bits(clave_hex, clave_bits);
    generar_subclaves(clave_bits, subclaves);

    uint8_t L[32], R[32], temp[32];
    uint8_t permutado[64];
    permute(mensaje_bits, permutado, IP);

    memcpy(L, permutado, 32);
    memcpy(R, permutado + 32, 32);

    printf("==== Cifrado ====\n");
    for (int i = 0; i < 16; i++) {
        function_f(R, subclaves[i], temp);
        uint8_t newR[32];
        for (int j = 0; j < 32; j++) newR[j] = L[j] ^ temp[j];
        memcpy(L, R, 32);
        memcpy(R, newR, 32);
        printf("Ronda %2d:\n", i + 1);
        mostrar_bits_hex("  L", L, 32);
        mostrar_bits_hex("  R", R, 32);
    }

    uint8_t preoutput[64];
    memcpy(preoutput, R, 32);
    memcpy(preoutput + 32, L, 32);

    uint8_t final[64];
    permute(preoutput, final, FP);

    char salida_hex[17];
    bits_to_hex(final, salida_hex);
    printf("Cifrado final: %s\n", salida_hex);

    printf("\n==== Descifrado ====\n");
    permute(final, permutado, IP);
    memcpy(L, permutado, 32);
    memcpy(R, permutado + 32, 32);

    for (int i = 15; i >= 0; i--) {
        function_f(R, subclaves[i], temp);
        uint8_t newR[32];
        for (int j = 0; j < 32; j++) newR[j] = L[j] ^ temp[j];
        memcpy(L, R, 32);
        memcpy(R, newR, 32);
        printf("Ronda %2d:\n", 16 - i);
        mostrar_bits_hex("  L", L, 32);
        mostrar_bits_hex("  R", R, 32);
    }

    memcpy(preoutput, R, 32);
    memcpy(preoutput + 32, L, 32);
    permute(preoutput, final, FP);
    bits_to_hex(final, salida_hex);
    printf("Descifrado final: %s\n", salida_hex);

    return 0;
}
