# Algoritmo Djikstra
### Sistema de algoritmo Djikstra a partir de una matriz entregada por el usuario.

---

Descripción general:
AlgoritmoDjikstra es un sistema automatizado para proporcionar un grafo
que demuestre el funcionamiento del algoritmo Djikstra con una matriz que entrega el usuario.

El objetivo principal es demostrar el funcionamiento del algoritmo a través de consola
y de un grafo.

---
#Arquitectura del proyecto

djikstra.cpp #Código programado para linux
readme_lab6.md #Documentación general del proyecto
grafo.png #Grafo algoritmo
---
#Consideraciones al ejecutar
El programa se programó considerado para linux, por ende si desea ejecutar en otro
sistema operativo, debe modificar las líneas que contengan eog en el código.
Al ejecutar se debe ingresar la cantidad de nodos, por favor que éste sea un número
entero, no se aceptan otros caracteres. 
Cuando se solicita el vector origen, sólo ingresar un caracter char, no se aceptan otros.
Al solicitar la matriz, sólo ingresar números enteros positivos (como única excepción
se encuentra el -1 si no hay un camino definido) separados por un espacio. Para la
segunda fila de la matriz, sólo es necesario apretar "Enter" y se siguen las mismas
instrucciones que al inicio. Lo mismo hasta que se complete la matriz.

---

#Funciones principales
-void inicializar_vector_caracter: le asigna letras del abecedario a cada posición del vector.
-void inicializar_vector_entero: inicializa un vector de enteros con -1 (distancia desconocida).
-void inicializar_matriz: llena la matriz con -1.
-void imprimir_matriz: imprime la matriz mostrando los pesos de las aristas. Son los datos que entregó el usuario.
-int calcular_minimo: compara las distancias posibles y devuelve la menor. Si dw es menor que dv+mvw conserva su valor, si es mayor, se actualiza como dv+mvw.
-int buscar_indice_caracter: como el nombre lo indica, se busca el índice del caracter,
si se encuentra retornamos la posición de dicho caracter.
-void imprimir_grafo: se genera un archivo grafo.txt con aristas y pesos y luego, dot genera la imagen grafo.png y se abre con eog (en linux). 
éste recorre la matriz y mientras tenga contenido el espacio en el que estamos, se grafica.
-void aplicar_dijkstra: implementa el algoritmo de dijkstra para calcular las distancias mínimas desde un vértice origen a todos los demás. D[] son los vectores de distancia y S[] los visitados. En cada iteración, se elige el vértice no visitado con menor distancia y se marca como visitado, luego se actualizan las distancias de sus vecinos con calcular_minimo y se muestra el estado del vector D[] en cada paso. Además, se imprimen las distancias mínimas desde el vértice al resto.
-int main: aquí se valida el número de argumentos, pues deben ser mayor a 2 y se inicializa
matriz + vectores porque el usuario ingresará los datos a continuación. Desde ese momento,
se leen los datos, se solicita el vértice origen y se llama a las funciones anteriores
para aplicar prim y generar grafos. Finalmente, se libera memoria.
---

#Instalación

Requisitos mínimos:
-C++ 
-Librerías necesarias: iostream, fstream, cstdlib, climits
-Graviphz
---
#Resultado esperado
1 Grafo generado.
Procesamiento correcto de algoritmo Djikstra.
---
#Autoría
**Catalina Rojas Sepúlveda**
Estudiante de Ingeniería Civil en Bioinformática
**Universidad de Talca - Facultad de Ingeniería**
