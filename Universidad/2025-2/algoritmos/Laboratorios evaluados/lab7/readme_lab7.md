# Algoritmo Prim
### Sistema de algoritmo prim a partir de una matriz entregada por el usuario.

---

Descripción general:
AlgoritmoPrim es un sistema automatizado para proporcionar dos grafos (uno original y uno post algoritmo)
que demuestran el funcionamiento del algoritmo Prim con una matriz que entrega el usuario.

El objetivo principal es demostrar el funcionamiento del algoritmo a través de consola
y de grafos.

---
#Arquitectura del proyecto

prim.cpp #Código programado para linux
readme_lab7.md #Documentación general del proyecto
grafo_original.png #Grafo pre aplicación algoritmo
grafo_mst.png #Grafo post aplicación algoritmo

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
-int buscar_indice_caracter: como el nombre lo indica, se busca el índice del caracter,
si se encuentra retornamos la posición de dicho caracter.
-void imprimir_grafo: se genera un grafo antes de la implementación del algoritmo,
éste recorre la matriz y mientras tenga contenido el espacio en el que estamos, se grafica.
-void imprimir_mst: genera un grafo post algortimo, en este caso se consideran las aristas
seleccionadas por el algoritmo.
-void aplicar_prim: busca encontrar el árbol de costo mínimo. En cada iteración, se selecciona
el vértice con menor distancia que no sea el MST, se marca y se agrega a los ya visitados,
se actualizan las distancias de sus vecinos por si hay una más corta y se guarda
la arista en una lista de resultados. Al final, se muestran las aristas que sí
lograron entrar al MST con su costo local y se grafica.
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
2 Grafos generados.
Procesamiento correcto de algoritmo Prim.
---
#Autoría
**Catalina Rojas Sepúlveda**
Estudiante de Ingeniería Civil en Bioinformática
**Universidad de Talca - Facultad de Ingeniería**


