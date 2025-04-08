/*
 * DES Implementation in C - FIPS PUB 46 compliant
 * Author: Luis Eduardo Ríos Nava
 * Description:
 *   - Cifra y decifra datos binarios con DES
 *   - Visualiza todas las 16 rondas con Ln, Rn y Kn
 *   - Incluye tablas de permutación, cajas S, y generación de claves
 *   - Usa cadenas binarias de 64 bits
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 // --------------------- TABLAS DE PERMUTACION ------------------------ //
 
 int IP[64] = {
     58,50,42,34,26,18,10,2,
     60,52,44,36,28,20,12,4,
     62,54,46,38,30,22,14,6,
     64,56,48,40,32,24,16,8,
     57,49,41,33,25,17,9,1,
     59,51,43,35,27,19,11,3,
     61,53,45,37,29,21,13,5,
     63,55,47,39,31,23,15,7
 };
 
 int IP_INV[64] = {
     40,8,48,16,56,24,64,32,
     39,7,47,15,55,23,63,31,
     38,6,46,14,54,22,62,30,
     37,5,45,13,53,21,61,29,
     36,4,44,12,52,20,60,28,
     35,3,43,11,51,19,59,27,
     34,2,42,10,50,18,58,26,
     33,1,41,9,49,17,57,25
 };
 
 int E[48] = {
     32,1,2,3,4,5,
     4,5,6,7,8,9,
     8,9,10,11,12,13,
     12,13,14,15,16,17,
     16,17,18,19,20,21,
     20,21,22,23,24,25,
     24,25,26,27,28,29,
     28,29,30,31,32,1
 };
 
 int P[32] = {
     16,7,20,21,29,12,28,17,
     1,15,23,26,5,18,31,10,
     2,8,24,14,32,27,3,9,
     19,13,30,6,22,11,4,25
 };
 
 int PC1[56] = {
     57,49,41,33,25,17,9,
     1,58,50,42,34,26,18,
     10,2,59,51,43,35,27,
     19,11,3,60,52,44,36,
     63,55,47,39,31,23,15,
     7,62,54,46,38,30,22,
     14,6,61,53,45,37,29,
     21,13,5,28,20,12,4
 };
 
 int PC2[48] = {
     14,17,11,24,1,5,3,28,
     15,6,21,10,23,19,12,4,
     26,8,16,7,27,20,13,2,
     41,52,31,37,47,55,30,40,
     51,45,33,48,44,49,39,56,
     34,53,46,42,50,36,29,32
 };
 
 int SHIFTS[16] = {
     1, 1, 2, 2, 2, 2, 2, 2,
     1, 2, 2, 2, 2, 2, 2, 1
 };
 
 // --------------------- CAJAS S (S-BOXES) ----------------------------- //

 int S_BOX[8][4][16] = {
    // S1
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    // S2
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    // S3
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    // S4
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    // S5
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    // S6
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    // S7
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    // S8
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// -------------------- FUNCIONES AUXILIARES -------------------------- //

// Verifica si la cadena es binaria y de longitud exacta
int es_binario_64(const char *str) {
    if (strlen(str) != 64) return 0;
    for (int i = 0; i < 64; i++) {
        if (str[i] != '0' && str[i] != '1') return 0;
    }
    return 1;
}

// Aplica una permutación a una cadena binaria
void permutar(const char *in, char *out, int *tabla, int n) {
    for (int i = 0; i < n; i++) {
        out[i] = in[tabla[i] - 1];
    }
    out[n] = '\0';
}

// Realiza XOR entre dos cadenas binarias
void xor(const char *a, const char *b, char *res, int n) {
    for (int i = 0; i < n; i++) {
        res[i] = (a[i] == b[i]) ? '0' : '1';
    }
    res[n] = '\0';
}

// Rota a la izquierda una cadena de n bits
void rotar_izquierda(char *in, int n, int veces) {
    char temp[32];
    strncpy(temp, in, veces);
    memmove(in, in + veces, n - veces);
    memcpy(in + n - veces, temp, veces);
}

// Convierte 6 bits a entero para S-box
int binario_a_entero(const char *b, int pos) {
    int row = (b[pos] - '0') * 2 + (b[pos + 5] - '0');
    int col = 0;
    for (int i = 1; i <= 4; i++) {
        col = col * 2 + (b[pos + i] - '0');
    }
    return S_BOX[pos / 6][row][col];
}

// Convierte entero (0-15) a 4 bits binarios
void entero_a_binario4(int val, char *res) {
    for (int i = 3; i >= 0; i--) {
        res[3 - i] = ((val >> i) & 1) + '0';
    }
    res[4] = '\0';
}


// ---------------------- FUNCION f(R, K) ------------------------------ //

void funcion_f(const char *R, const char *K, char *out) {
    char expandido[49], mezclado[49];
    char bloque[7], sustitucion[33], temp4[5];

    permutar(R, expandido, E, 48);
    xor(expandido, K, mezclado, 48);

    sustitucion[0] = '\0';
    for (int i = 0; i < 48; i += 6) {
        int val = binario_a_entero(mezclado, i);
        entero_a_binario4(val, temp4);
        strncat(sustitucion, temp4, 4);
    }
    permutar(sustitucion, out, P, 32);
}

// -------------------- GENERACION DE SUBCLAVES ------------------------ //

void generar_subclaves(const char *clave64, char subclaves[16][49]) {
    char clave56[57], C[29], D[29], CD[57];

    permutar(clave64, clave56, PC1, 56);
    strncpy(C, clave56, 28); C[28] = '\0';
    strncpy(D, clave56 + 28, 28); D[28] = '\0';

    for (int i = 0; i < 16; i++) {
        rotar_izquierda(C, 28, SHIFTS[i]);
        rotar_izquierda(D, 28, SHIFTS[i]);

        strncpy(CD, C, 28);
        strncpy(CD + 28, D, 28);
        CD[56] = '\0';

        permutar(CD, subclaves[i], PC2, 48);
    }
}

// -------------------- FUNCIONES DE CIFRADO Y DESCIFRADO ------------ //

void cifrar_DES(const char *texto, char subclaves[16][49], char *resultado) {
    char IP_texto[65], L[33], R[33], Ln[33], Rn[33], f_out[33], temp[33];

    permutar(texto, IP_texto, IP, 64);
    strncpy(L, IP_texto, 32); L[32] = '\0';
    strncpy(R, IP_texto + 32, 32); R[32] = '\0';

    for (int i = 0; i < 16; i++) {
        strcpy(Ln, R);
        funcion_f(R, subclaves[i], f_out);
        xor(L, f_out, Rn, 32);
        strcpy(L, Ln);
        strcpy(R, Rn);

        printf("\n========== Ronda %2d ==========\n", i + 1);
        printf("Kn: %s\n", subclaves[i]);
        printf("Ln: %s\n", L);
        printf("Rn: %s\n", R);
        printf("==============================\n");
    }

    char pre_salida[65];
    strncpy(pre_salida, R, 32);
    strncpy(pre_salida + 32, L, 32);
    pre_salida[64] = '\0';
    permutar(pre_salida, resultado, IP_INV, 64);
}

void descifrar_DES(const char *texto, char subclaves[16][49], char *resultado) {
    char IP_texto[65], L[33], R[33], Ln[33], Rn[33], f_out[33], temp[33];

    permutar(texto, IP_texto, IP, 64);
    strncpy(L, IP_texto, 32); L[32] = '\0';
    strncpy(R, IP_texto + 32, 32); R[32] = '\0';

    for (int i = 15; i >= 0; i--) {
        strcpy(Ln, R);
        funcion_f(R, subclaves[i], f_out);
        xor(L, f_out, Rn, 32);
        strcpy(L, Ln);
        strcpy(R, Rn);

        printf("\n====== Ronda %2d (Descifrado) ======\n", 16 - i);
        printf("Kn: %s\n", subclaves[i]);
        printf("Ln: %s\n", L);
        printf("Rn: %s\n", R);
        printf("===================================\n");
    }

    char pre_salida[65];
    strncpy(pre_salida, R, 32);
    strncpy(pre_salida + 32, L, 32);
    pre_salida[64] = '\0';
    permutar(pre_salida, resultado, IP_INV, 64);
}

// ---------------------------- MAIN ---------------------------------- //

int main() {
    char texto[65], clave[65], resultado[65];
    char subclaves[16][49];
    int opcion;

    printf("\n==========================\n");
    printf("   Cifrado DES en Binario\n");
    printf("==========================\n");

    printf("Ingrese texto (64 bits en binario): ");
    scanf("%64s", texto);

    if (!es_binario_64(texto)) {
        printf("Error: El texto debe ser binario y de 64 bits.\n");
        return 1;
    }

    printf("Ingrese clave  (64 bits en binario): ");
    scanf("%64s", clave);

    if (!es_binario_64(clave)) {
        printf("Error: La clave debe ser binaria y de 64 bits.\n");
        return 1;
    }

    printf("\nSeleccione una opci\xA2n:\n");
    printf("1. Cifrar\n");
    printf("2. Descifrar\n");
    printf("Opci\xA2n: ");
    scanf("%d", &opcion);

    generar_subclaves(clave, subclaves);

    if (opcion == 1) {
        cifrar_DES(texto, subclaves, resultado);
        printf("\nTexto cifrado: %s\n", resultado);
    } else if (opcion == 2) {
        descifrar_DES(texto, subclaves, resultado);
        printf("\nTexto descifrado: %s\n", resultado);
    } else {
        printf("Opci\xA2n inv\xA1lida.\n");
        return 1;
    }

    return 0;
}
