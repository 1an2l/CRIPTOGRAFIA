# Intercambio de Claves Diffie-Hellman en C  

Este programa implementa el **intercambio de claves Diffie-Hellman** en C, permitiendo a dos partes generar una clave secreta compartida utilizando exponentiación modular.

## Requisitos  

- **Compilador de C** (GCC recomendado).  
- **Sistema operativo** con soporte para compilación en C (Windows, Linux o macOS).  

## Compilación y Ejecución  

### Compilar el código  

Para compilar el código fuente, usa el siguiente comando en la terminal:  

```sh
gcc Deffie_Helman.c -o deffie_helman
```

### Ejecutar el programa  

Para ejecutar el programa, usa el siguiente comando:  

```sh
./deffie_helman
```

## Cómo usar el programa  

Al ejecutar el programa, se solicitará ingresar los siguientes valores:

1. **Número primo (p):**  
   - Debe ser un valor mayor que 0.
2. **Generador (g):**  
   - Debe cumplir que `0 < g < p`.
3. **Clave privada de Alice (a)** y **clave privada de Bob (b):**  
   - Valores enteros positivos introducidos por el usuario.

### Proceso  

- El programa calculará las claves públicas `A = g^a mod p` y `B = g^b mod p`.
- Luego, cada parte calculará la clave compartida usando la clave pública del otro:
  - Alice calcula `clave = B^a mod p`
  - Bob calcula `clave = A^b mod p`
- Ambas claves compartidas deben coincidir si el proceso es correcto.

### **Ejemplo de ejecución**  

1. Ejecutar el programa `./deffie_helman`.  
2. Ingresar los siguientes valores cuando se soliciten:

   ```
   Ingresa un número primo (p): 23
   Ingresa un generador (g) tal que 0 < g < p: 5
   Ingresa la clave privada (a): 6
   Ingresa la clave privada (b): 15
   ```

3. Resultado esperado:

   ```
   Clave pública de Alice (A): 8
   Clave pública de Bob (B):   2

   Clave compartida calculada por Alice: 13
   Clave compartida calculada por Bob:   13

   Ambas partes tienen la misma clave secreta.
   ```

## Notas  

- Puedes escribir `X` en cualquier momento para salir del programa.
- El programa incluye validación de entrada para garantizar que los valores sean positivos y correctos.
- La operación de exponenciación modular se realiza mediante un algoritmo eficiente para grandes exponentes.

