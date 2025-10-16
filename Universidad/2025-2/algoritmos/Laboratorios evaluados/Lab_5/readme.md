Ejecución del programa:
g++ Rojas_Catalina_Lab5.cpp -o programa
./programa funciones_GO_minimal.csv 

*funciones_GO_minimal.csv representa el nombre del archivo csv que desea importar. En caso de ser
un nombre diferente al mencionado, por favor escribir en consola el que se encuentra en su computador.

Consideraciones:
------
Al ingresar un nuevo nodo:
*No ingresar caracteres diferentes a decimales para el score. El decimal se hace con un punto ".", no una coma ",".
*No hacer espacios al escribir la función de un nuevo nodo.
*Para el código, se suele iniciar con GO:00000 (0000 representa cualquier número entero que desee)
------
*Este programa se creó para ejecutarse en Linux. Si cuenta con otro sistema
operativo, por favor modificar la línea de visualización "eog" en GenerarGrafo().

El funcionamiento del código se da por nodos. Se crean nodos con un código, función, puntaje y factor de equilibrio, además con su nodo izquierdo y derecho vacío. A medida que importa los datos
de un archivo CSV, el árbol balanceado se va creando, dependiendo del valor del score, el nodo se
ubicará a la izquierda de la raíz si es menor o a la derecha si es mayor. Cuando se crea un nuevo nodo, se analiza su factor de equilibrio. Si el nodo viene con un FE=0 y se agrega otro a su izquierda, pasará a ser -1 porque se diferenciará en una unidad la altura de ambos lados. Si es FE=-1, reestructuraremos con rotación a izquierda (II o ID). Lo mismo para el lado derecho pero esta vez, si FE=1, rotamos a derecha (DD o DI).
Para buscar un término, se busca mediante el código como se propuso en la guía y si el nodo en el que estamos coincide con el código que escribimos, se informará que existe y viceversa.
Ya para generar el grafo, debemos definir estilo y color y llamar a la función PreOrden que nos informa si el nodo no está vacío y si su izquierdo tampoco está vacío, lo conectamos. Si lo está, crearemos un nodo falso con string para que se vea como un punto y lo asocio al original. Lo mismo para la derecha. Se recorre todo el subárbol izquierdo y luego el derecho.

