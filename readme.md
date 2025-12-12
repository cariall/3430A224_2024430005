# Automatización de alineamiento de secuencias
Sistema que alinea secuencias de ADN de forma automática.

Descripción general: 
Automatización de alineamiento de secuencias es un sistema automatizado que a partir del método Needle-Wunsch busca el camino óptimo para alinear dos secuencias, que en general se encuentran en formato fasta. Como resultado final, se entrega el puntaje máximo y la secuencia alineada con los gaps correspondientes. Se puede modificar tanto el puntaje de penalidad como la matriz y las secuencias a analizar.

El objetivo es encontrar el camino óptimo para la mayor cantidad de coincidencias posibles entre ambas secuencias.
---

#Arquitectura del proyecto
Input:
programa.cpp #Código programado para linux
programa #Archivo ejecutable
matriz_u.txt #Matriz de sustitución
cadena1.txt #Primera secuencia corta, ejemplo1
cadena2.txt #Segunda secuencia corta, ejemplo1.
sequence.fasta #Primera secuencia larga, ejemplo2.
sequence1.fasta #Segunda secuencia larga, ejemplo2.

Output:
alineamiento.png #Imagen con alineamiento de secuencias

#Consideraciones al ejecutar
Forma de ejecución: 
g++ programa.cpp -o programa
./programa -C1 <archivo_secuencia1> -C2 <archivo_secuencia2> -U <matriz_u> -V <puntaje_penalidad>

ejemplo: ./programa -C1 sequence.fasta -C2 sequence1.fasta -U matriz_u.txt -V -2

Los argumentos a ingresar deben ser escritos exactamente como se muestra en el ejemplo y los archivos a utilizar deben encontrarse dentro de la carpeta donde se corre el programa. De no ser así, también se puede utilizar la ruta para acceder al archivo, ejemplo: ./programa -C1 ~/Descargas/sequence.fasta -C2 ~/Descargas/sequence1.fasta -U matriz_u.txt -V -2

El número a ingresar como puntaje de penalidad debe ser estrictamente un entero.
---
#Funciones principales

string leerCadena(): lee el archivo. En caso de encontrarse con ">" por formato convencional fasta, descarta el encabezado y se lee el resto del archivo.

void imprimirMatriz(): imprime la matriz.

void leerMatrizU(): lee la matriz U desde un archivo txt.

int traduccion(): traduce el caracter de la secuencia a un número, pues la matriz sólo permite enteros.

int obtenerPuntajeU(): devuelve puntaje de similitud entre ambas letras que se comparan según la matriz.

generarGraphviz(): crea un archivo dot y divide las filas en 50 caracteres, determina colores según las condiciones y crea una fila vacía para separar las secuencias.

reconstruirAlineamiento(): utiliza Needle-Wunsch para construir el alineamiento y según el mejor puntaje, se van creando los alineamientos. A su vez, se integraron las estadísticas de match, mismatch, gap e identidad para tener una idea final del análisis.

int main(): se encarga de recibir los argumentos y destinarle un nombre a cada uno. Lee las cadenas entregadas y crea la matriz con todas las condiciones iniciales de Needle-Wunsch, desde el final comienza la reconstrucción. Además, se integró liberación de memoria.
---
#Instalación
Requisitos mínimos:
-C++
-Librerías necesarias: iostream, fstream, string, stdexcept, cstdlib
---
#Resultado esperado
Se espera visualizar en la terminal la matriz con solo puntaje de penalidad y la matriz ya rellena con todos los números calculados. Luego, las estadísticas del alineamiento, tanto match, mismatch, gap, porcentaje de identidad y puntaje máximo, además de la imagen png que genera el dot con el alineamiento de ambas secuencias indicando match con verde, mismatch con rojo y gap con gris.
---
#Autoría
**Catalina Rojas Sepúlveda**
Estudiante de Ingeniería Civil en Bioinformática
**Universidad de Talca - Facultad de Ingeniería**
---
