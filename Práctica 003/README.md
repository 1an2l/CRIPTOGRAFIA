# Cifrado Homofónico en C  

Este programa implementa el **Cifrado Homofónico** en C, permitiendo el cifrado y descifrado de textos utilizando una sustitución aleatoria de letras por secuencias binarias de 6 bits.  

## Requisitos  

- **Compilador de C** (GCC recomendado).  
- **Sistema operativo** con soporte para compilación en C (Windows, Linux o macOS).  

## Compilación y Ejecución  

### Compilar el código  

Para compilar el código fuente, usa el siguiente comando en la terminal:  

```sh
gcc cifradoHomofonico.c -o cifradoHomofonico
```

### Ejecutar el programa  

Para ejecutar el programa, usa el siguiente comando:  

```sh
./cifradoHomofonico
```

## Cómo usar el programa  

Al ejecutar el programa, se solicitará elegir entre **cifrar o descifrar un mensaje**.  

1. **Elige una opción:**  
   - `C`: **Cifrar un mensaje**.  
   - `D`: **Descifrar un mensaje**.  
2. **Ingresa el texto:**  
   - Si elegiste cifrar (`C`), ingresa el texto que deseas cifrar.  
   - Si elegiste descifrar (`D`), ingresa la cadena binaria cifrada.  
3. **Resultado:**  
   - Si cifraste, el programa generará una secuencia binaria de 6 bits por cada letra.  
   - Si descifraste, el programa convertirá la secuencia binaria en texto claro.  

### **Ejemplo de cifrado**  

1. Ejecutar el programa `./cifradoHomofonico`.  
2. Seleccionar la opción `C` (**Cifrar**).  
3. Ingresar el texto: `HOLA`.  
4. Se mostrará el texto cifrado en formato binario, por ejemplo:  

   ```
   001110011001010100000000
   ```

### **Ejemplo de descifrado**  

1. Ejecutar el programa `./cifradoHomofonico`.  
2. Seleccionar la opción `D` (**Descifrar**).  
3. Ingresar la cadena cifrada:  

   ```
   001110011001010100000000
   ```

4. Se mostrará el texto descifrado:  

   ```
   HOLA
   ```

## Notas  

- **Solo se cifran letras alfabéticas** (`A-Z`), los demás caracteres se ignoran.  
- **El cifrado usa sustitución homofónica**, por lo que una misma letra puede tener diferentes representaciones.  
- **Cada secuencia cifrada tiene exactamente 6 bits**.  
- **El descifrado solo funciona si las secuencias binarias son correctas**.