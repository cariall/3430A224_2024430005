*Descripción del funcionamiento*
Este código simula un puerto seco con un sistema de pilas de 
contenedores. La distribución inicial la determina el usuario, 
la cual puede ser tanto manual como automática.
En el caso de seleccionar manual, el usuario ingresará en qué
pilas desea ingresar contenedores. De ser automática, se asignarán
en orden de pilas vacías.
También se permite visualizar el estado actual de las pilas y 
retirar contenedores específicos que siguen el método LIFO, 
primero sacando aquellos que están al último hasta llegar al que
se solicitó.

*Requisitos*
Compilador de C++
Bibliotecas estándar (iostream, cstdlib)

*Uso del programa:*
Compilación: g++ Rojas_Catalina_L2_E2.cpp -o programa
Ejecución: ./programa n m
Siendo n y m enteros que determina el usuario, pues estos 
corresponden a la altura máxima de cada pila como al número de 
pilas totales, respectivamente.
Ejemplo de ejecución: ./programa 4 4

*Consideraciones especiales*
Asegurarse de ingresar números válidos, tanto al agregar contenedores
en pilas(0 al 3), como al ingresar los parámetros en comando(n>=0, m>=0)
y al retirar los contenedores(verificar en estado que sí existan o que 
sean menores al número de contenedores que agregó al inicio).
Contenedores a agregar no pueden exceder n*m.
Se crean pilas con new pero no se libera la memoria final,
pues se espera un uso corto del programa.
