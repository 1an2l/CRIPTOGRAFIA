#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

int leer_entero(const char* mensaje, long long* valor) {
    char buffer[100];
    printf("\033[0;34m%s\033[0m", mensaje);
    fgets(buffer, sizeof(buffer), stdin);

    if (buffer[0] == 'x' || buffer[0] == 'X') {
        return 0;
    }

    if (sscanf(buffer, "%lld", valor) != 1 || *valor <= 0) {
        printf("\033[0;31mEntrada inválida. Intenta de nuevo.\033[0m\n");
        return leer_entero(mensaje, valor);
    }

    return 1;
}

int main() {
    long long p, g, a, b;

    printf("\033[1m=== Intercambio de claves Diffie-Hellman ===\033[0m\n");
    printf("Escribe 'X' en cualquier momento para salir.\n\n");

    while (1) {
        if (!leer_entero("Ingresa un número primo (p): ", &p))
            return 0;

        if (!leer_entero("Ingresa un generador (g) tal que 0 < g < p: ", &g))
            return 0;

        if (g <= 0 || g >= p) {
            printf("\033[0;33mEl generador debe cumplir 0 < g < p. Intenta de nuevo.\033[0m\n\n");
        } else {
            break;
        }
    }

    if (!leer_entero("Ingresa la clave privada (a): ", &a)) return 0;
    if (!leer_entero("Ingresa la clave privada (b): ", &b)) return 0;

    long long A = mod_exp(g, a, p);
    long long B = mod_exp(g, b, p);

    printf("\n\033[0;34mClave pública de Alice (A):\033[0m %lld\n", A);
    printf("\033[0;34mClave pública de Bob (B):  \033[0m %lld\n", B);

    long long claveAlice = mod_exp(B, a, p);
    long long claveBob   = mod_exp(A, b, p);

    printf("\n\033[0;32mClave compartida calculada por Alice:\033[0m %lld\n", claveAlice);
    printf("\033[0;32mClave compartida calculada por Bob:  \033[0m %lld\n", claveBob);

    if (claveAlice == claveBob) {
        printf("\n\033[1;32mAmbas partes tienen la misma clave secreta.\033[0m\n");
    } else {
        printf("\n\033[1;31mError: las claves no coinciden.\033[0m\n");
    }

    return 0;
}
