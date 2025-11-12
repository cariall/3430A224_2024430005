# Métodos de ordenamiento
Sistema que incluye tanto métodos de ordenamiento cuadráticos como logarítmicos, dentro de ellos se incluye BubbleSort, QuickSort, ShellSort, Inserción y Selección.

Descripción general: 
Métodos de Ordenamiento es un sistema automatizado que a partir de los argumentos entregados por el usuario, como el número de elementos a ordenar y si desea ver el orden final de cada método, se visualiza tanto el tiempo que demora cada uno en su desarrollo como el arreglo inicial y el resultado final.

El objetivo es comparar los tiempos de cada método de ordenamiento utilizando cantidades aleatorias de números y decidiendo si ver los arreglos finales o no.
---
#Arquitectura del proyecto
Rojas_Catalina_lab8.cpp #Código programado para linux
programa #Archivo ejecutable

#Consideraciones al ejecutar
Forma de ejecución: 
g++ Rojas_Catalina_lab8.cpp -o programa
./programa 10 s 
El primer argumento que se debe ingresar es un número entero positivo, que corresponde a la cantidad de elementos que desea en el vector, y el segundo es un caracter en minúscula o mayúscula. Si utiliza 's' o 'S' indica que desea ver los arreglos finales de cada método. Cualquier otra letra se interpretará como que no desea verlos, por ende sólo se mostrarán los tiempos de ejecución. Por favor, no ingresar ningún otro tipo de caracter que no haya sido especificado.
---
#Funciones principales
Se utilizó high_resolution_clock para todas las funciones que hacen referencia a un método de ordenamiento. Este se utilizó al inicio y al final de cada una para medir el tiempo que demoró su ejecución. Al fin de este archivo, se encuentra la referencia a aquello. En todas, también se utilizó el retorno double para visualizar los tiempos de forma más ordenada en la terminal.

double burbuja_menor(int A[], int N): Método de Burbuja o BubbleSort. De izquierda a derecha, se compara el primer elemento con el segundo y si el segundo es menor al primero, se intercambian. Así continúa hasta llegar a su posición. 

double insercion(int A[], int N): Método de Inserción. Se compara el segundo elemento con el de su izquierda, si este es menor a su vecino izquierdo, se intercambian y el elemento menor se sigue comparando hacia la izquierda hasta ubicarse en su lugar correcto.

double seleccion(int A[], int N): Método de Selección. Busca el elemento menor del arreglo y lo ubica en la primera posición. Al tener lista la primera posición, esta se bloquea y ahora la primera posición será la "segunda original", por ende se sigue buscando el elemento más pequeño para ubicarlo en dicho lugar y así.

double shellsort(int A[], int N): Método ShellSort. Utiliza intervalos, mediante saltos compara elementos distantes entre sí. Aquí se reduce el intervalo en sublistas. A partir de las sublistas, se ordena por método de inserción. Así reduce aún más el intervalo dividiéndolo en dos cada vez, hasta llegar a intervalo 1:1.

double quicksort(int A[], int N): Método QuickSort. Toma un elemento random del vector, en este caso se utilizó el primero y se ubica en una posición del arreglo donde todos los de su izquierda sean menores y los de su derecha, mayores. Se repite el mismo proceso para los datos a su izquierda como para los de su derecha hasta que estén todos en sus posiciones correctas.

void reduce(int A[], int ini, int fin, int &pos): Reduce es una función utilizada en QuickSort. Su objetivo es utilizar izq y der que se mueven desde los extremos para compararse con el pivote, si encuentra un elemento mayor al de su izquierda, los intercambia. Si encuentra uno menor a su derecha, lo intercambia y actualiza valor del pivote. Cuando quedan en sus posiciones respectivas, se cierra el ciclo con un band = false.

void imprimir_elementos(int A[], int N, char VER): Simplemente imprime los elementos de los vectores.

int main(int argc, char *argv[]): Necesita de argumentos para ejecutarse. Si no se ingresan 3 argumentos, no se ejecutará. Transformamos N a entero, que será el número de datos a incluir y VER, que es la indicación de querer ver el orden final de los elementos. Se reserva memoria para un arreglo[N] y se asigna un número aleatorio por cada posición. rand()%5000 es sólo para que los números no pasen del 5000 y facilitar la lectura del programa. Se imprime el arreglo inicial y se crean arreglos de [N] enteros para cada método igualándolos a A. Luego, se llama a las funciones, se imprimen sus tiempos y si el usuario ingresó 's' como argumento, se muestra también el orden final de los elementos para cada método. Al finalizar, se libera memoria por cada copia del arreglo inicial.
---
#Instalación
Requisitos mínimos:
-C++
-Librerías necesarias: iostream, cstdlib, chrono.
---
#Resultado esperado
Si no desea ver los arreglos finales (./Rojas_Catalina_lab8.cpp 3 n), se espera ver el arreglo aleatorio inicial y los tiempos de ejecución de cada método.
Si desea ver los arreglos finales (./Rojas_Catalina_lab8.cpp 3 s), se espera todo lo anterior más los arreglos especificados por cada método.
---
#Autoría
**Catalina Rojas Sepúlveda**
Estudiante de Ingeniería Civil en Bioinformática
**Universidad de Talca - Facultad de Ingeniería**
---
#Referencias
https://cplusplus.com/reference/chrono/high_resolution_clock/now/ 