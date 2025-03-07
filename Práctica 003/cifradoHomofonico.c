#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// Estructura para almacenar el inicio y la cantidad de sustitutos por letra
typedef struct {
    int start;
    int count;
} LetterInfo;

// Arreglo con todos los sustitutos binarios
const char* all_substitutes[44] = {
    "000000", "000001", "000010", // A
    "000011",                     // B
    "000100",                     // C
    "000101", "000110",           // D
    "000111", "001000", "001001", "001010", "001011", // E
    "001100",                     // F
    "001101",                     // G
    "001110", "001111",           // H
    "010000", "010001",           // I
    "010010",                     // J
    "010011",                     // K
    "010100", "010101",           // L
    "010110",                     // M
    "010111", "011000",           // N
    "011001", "011010",           // O
    "011011",                     // P
    "011100",                     // Q
    "011101", "011110",           // R
    "011111", "100000",           // S
    "100001", "100010", "100011", // T
    "100100", "100101",           // U
    "100110",                     // V
    "100111",                     // W
    "101000",                     // X
    "101001", "101010",           // Y
    "101011"                      // Z
};

// Información de inicio y cantidad de sustitutos por letra (A=0, B=1, ..., Z=25)
LetterInfo letter_info[26] = {
    {0, 3}, {3, 1}, {4, 1}, {5, 2}, {7, 5}, {12, 1}, {13, 1}, {14, 2},
    {16, 2}, {18, 1}, {19, 1}, {20, 2}, {22, 1}, {23, 2}, {25, 2}, {27, 1},
    {28, 1}, {29, 2}, {31, 2}, {33, 3}, {36, 2}, {38, 1}, {39, 1}, {40, 1},
    {41, 2}, {43, 1}
};

// Función para obtener un sustituto aleatorio para una letra
const char* get_random_substitute(char letter) {
    if (!isalpha(letter)) return NULL;
    letter = toupper(letter);
    int index = letter - 'A';
    int start = letter_info[index].start;
    int count = letter_info[index].count;
    int random_index = start + rand() % count;
    return all_substitutes[random_index];
}

// Función para descifrar una cadena binaria de 6 bits
char decrypt_substitute(const char* binary) {
    for (int i = 0; i < 44; i++) {
        if (strcmp(binary, all_substitutes[i]) == 0) {
            for (int j = 0; j < 26; j++) {
                int start = letter_info[j].start;
                int end = start + letter_info[j].count;
                if (i >= start && i < end) {
                    return 'A' + j;
                }
            }
        }
    }
    return '?'; // Sustituto no válido
}

int main() {
    srand(time(NULL)); // Semilla para aleatoriedad
    char option;
    printf("%cDesea cifrar (C) o descifrar (D)? ",168);
    scanf(" %c", &option);
    option = toupper(option);
    getchar(); // Consume el salto de línea

    if (option == 'C') {
        // Cifrado
        char input[1001];
        printf("Ingrese la cadena a cifrar: ");
        fgets(input, 1000, stdin);
        input[strcspn(input, "\n")] = 0;

        char cipher_text[6001] = {0};
        char* ptr = cipher_text;

        for (char* p = input; *p; p++) {
            if (isalpha(*p)) {
                const char* substitute = get_random_substitute(*p);
                if (substitute) {
                    strcpy(ptr, substitute);
                    ptr += 6;
                }
            }
        }
        printf("Texto cifrado: %s\n", cipher_text);
    } else if (option == 'D') {
        // Descifrado
        char input[6001];
        printf("Ingrese la cadena cifrada: ");
        fgets(input, 6000, stdin);
        input[strcspn(input, "\n")] = 0;

        int len = strlen(input);
        if (len % 6 != 0) {
            printf("Error: La longitud debe ser múltiplo de 6.\n");
            return 1;
        }

        char plain_text[1001] = {0};
        char* ptr = plain_text;

        for (int i = 0; i < len; i += 6) {
            char binary[7];
            strncpy(binary, input + i, 6);
            binary[6] = '\0';
            char letter = decrypt_substitute(binary);
            if (letter == '?') {
                printf("Error: Cadena binaria inválida '%s'\n", binary);
                return 1;
            }
            *ptr++ = letter;
        }
        printf("Texto descifrado: %s\n", plain_text);
    } else {
        printf("Opción inválida. Use 'C' para cifrar o 'D' para descifrar.\n");
    }

    return 0;
}