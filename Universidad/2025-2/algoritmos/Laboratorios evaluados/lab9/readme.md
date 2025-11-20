# Métodos de búsqueda - Tablas Hash
Sistema que incluye métodos de búsqueda y reasignación. Se utilizaron funciones hash para el desarrollo del programa.

Descripción general: 
Métodos de búsqueda - Tablas Hash es un sistema automatizado que a partir de los números entregados por el usuario, se asignan según la fórmula hash dada. Si su índice está ocupado, se reasigna según doble dirección, lineal o cuadrático. A su vez, se implementó encadenamiento para demostrar las listas enlazadas.

El objetivo es destinar una posición a cada número ingresado y comparar las diferentes reasignaciones implementadas en el programa.
---
#Arquitectura del proyecto
lab9.cpp #Código programado para linux
programa #Archivo ejecutable

#Consideraciones al ejecutar
Forma de ejecución: 
lab9.cpp -o programa
./programa l (puede ser 'l','c','d','e')
El argumento a ingresar debe ser una de las letras mencionadas. Favor no ingresar otro tipo de caracter. 
Se puede utilizar 'l','c','d','e' tanto en minúscula como en mayúscula.
Para asignarle vacío a un espacio del arreglo, por favor ingresar "-1", ningún otro caracter será aceptado para ese fin. Sólo utilizar enteros, el uso de cualquier otro caracter romperá el programa. 
---
#Funciones principales

int funcion_hash(int x): Implementa la función Hash que destiné al programa. Devuelve la posición como un entero.

int funcion_hash_dos(int x): Implementa una función Hash diferente que se utiliza en reasignación de doble dirección. También devuelve un entero.

void inicializar(): Crea la tabla y la lista con espacios vacíos para rellenar.

void imprimirTabla(): Imprime los datos de la tabla.

void imprimirListas(): Imprime los datos de la lista enlazada. Sólo colisiones.

Para todas las reasignaciones, lo primero que realiza el programa es insertar el número en la posición que le asignó bash (si el espacio está vacío).

void pruebaLineal(int tabla[], int N, int valor): Si no, imprime colisión y busca el siguiente espacio disponible para reasignar el valor.

void pruebaCuadratica(int tabla[], int N, int valor): Si no, imprime colisión y utiliza la misma fórmula que lineal, sumándole un valor a la posición anterior pero esta vez está al cuadrado para reasignar el valor.

void dobleDireccion(int tabla[], int N, int valor): Si no, genera un entero con una función hash diferente, que es el cual se implementará en la fórmula para obtener la posición final. Si el cuadrático era D+(I*I), este será D+(I*valor_nuevo_hash). 

void encadenamiento(int tabla[], int N, int valor): Si no, se generará un nodo con el valor que colisiona y se guardará en la lista (si está vacío). En caso de no estar vacío, se guarda la información en un nodo p y mientras el que le sigue tenga algo, p guardará la info del siguiente y el siguiente guardará la info del nodo. 

int main(int argc, char* argv[]): Pide el ingreso de números uno por uno y determina el tipo de reasignación o encadenamiento según el primer argumento del usuario. A su vez, imprime las tablas y listas cuando corresponde.

---
#Instalación
Requisitos mínimos:
-C++
-Librerías necesarias: iostream
---
#Resultado esperado
Se espera ver el enunciado que solicita el ingreso de números. Luego de ingresar cada número, se indicará si se ingresó, colisionó o se reasignó y se mostrará el arreglo/tabla. 
---
#Autoría
**Catalina Rojas Sepúlveda**
Estudiante de Ingeniería Civil en Bioinformática
**Universidad de Talca - Facultad de Ingeniería**
---