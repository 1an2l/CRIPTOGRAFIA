# DES en Binario - Implementación en Lenguaje C

Este proyecto implementa el algoritmo **Data Encryption Standard (DES)** en lenguaje C utilizando exclusivamente cadenas binarias de 64 bits. El código cumple con la especificación técnica del estándar **FIPS PUB 46**.

## Características 🛡️

- Cifrado y descifrado bit a bit (64 bits).
- Generación de subclaves (K1 a K16).
- Visualización completa de las 16 rondas (Ln, Rn, Kn).
- Tablas de permutación oficiales (`IP`, `IP^-1`, `E`, `P`, `PC-1`, `PC-2`).
- Soporte de las 8 cajas S (S-boxes).
- Menú interactivo para elegir cifrado o descifrado.

## Compilación 🧰

```bash
gcc -o des_binario des_binario.c
```

## Ejecución 🖥️

```bash
./des_binario
```

## Ejemplo de uso 

### Entradas:

```txt
Ingrese texto (64 bits en binario): 0000000100100011010001010110011110001001101010111100110111101111
Ingrese clave  (64 bits en binario): 0001001100110100010101110111100110011011101111001101111111110001
Seleccione una opción:
1. Cifrar
2. Descifrar
Opción: 1
```

### Salida esperada:

```txt
========== Ronda  1 ==========
Kn: 000110110000001011101111111111000111000001110010
Ln: 11100010011010101111001101111011
Rn: 01000011010000100010110011110111
...
Texto cifrado: 1000010111101000000100110101010000001111000010101011010000000101
```

## Descifrado 

Usa el texto cifrado anterior como entrada junto con la misma clave y selecciona la opción 2 (descifrar). El programa debe devolverte exactamente el texto original en binario.

```txt
Texto descifrado: 0000000100100011010001010110011110001001101010111100110111101111
```

## Requisitos 

- Compilador C (GCC u otro compatible).
- Terminal o entorno de desarrollo que permita entrada por consola.

