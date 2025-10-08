Consideraciones:
* No ingresar carácteres diferentes a números enteros durante la ejecución
de todo el programa.
* En caso de ingresar el mismo número dos veces, el árbol sólo creará un nodo con ese contenido.
Sin embargo, no le proporcionará otra oportunidad de ingreso, por lo que se recomienda utilizar
la opción 1 del menú (Insertar un número) si desea seguir creando nodos.
* Este programa se creó para ejecutarse en Linux. Si cuenta con otro sistema
operativo, por favor modificar la línea de visualización "eog" en visualizar().
* Luego de visualizar el grafo, cierre la ventana emergente antes de continuar
con la ejecución del programa.

-Node* createNode(int data): Se crea un nuevo nodo con la información entregada a la 
función, quedando el nodo izquierdo como derecho del mismo vacíos. Se retorna
el nuevo nodo.

-bool insercion_ABB(Node* &apnodo, int info): Si el nodo está vacío, se crea uno con
la información. Si no, se chequea si la información entregada
es menor a la del nodo en la que estamos. Si es así, se revisa si nodo izquierdo
está vacío y si lo está, creamos un nodo con la información entregada y lo ubicamos
a la izquierda del nodo. Lo mismo para la derecha si el valor es mayor. Si el valor
es igual al del nodo, se indica que ya existe y se retorna falso. 

-bool eliminacion_ABB(Node* &apnodo, int info): Permite eliminar un nodo. Si está vacío,
retornamos falso y si no lo está, chequeamos si el valor entregado es menor al del nodo
donde estamos, si así es, llamamos recursivamente a la función pero esta vez usando el nodo
izquierdo. En caso de que el valor sea mayor, se hará por derecha hasta encontrar el 
nodo con el valor correspondiente. Una vez encontrados, se crea un nodo auxiliar con la 
información del nodo y si a su derecha está vacío, el nodo original se convertirá en el de
la derecha. Inverso para el lado izquierdo. Si ninguno está vacío, se generan nodos progenitor
e hijo, siendo el nodo original y el de la izquierda, respectivamente. Mientras el hijo
tenga vacío a su derecha, su padre pasará al lugar del hijo y el hijo pasará a ser el nodo
derecho de la última ubicación de su padre. Así hasta que su lado derecho esté nulo y ahí
determinamos que la información del nodo será la del hijo. Si el progenitor está en el nodo
a eliminar, lo que está a su izquierda será lo que estaba a la izquierda de su hijo. Si el
progenitor no está directo a su hijo, su lado derecho tendrá la información izquierda de
su hijo. Así se elimina hijo y se devuelve true. En caso de que su lado izquierdo o derecho
estén vacíos, se elimina el nodo original y se devuelve true. Si ninguna condición se cumple,
se devuelve falso.

-buscaModifica_ABB(Node* &apnodo, int info): Permite buscar el nodo correcto y modificarlo
mediante la llamada a las funciones de eliminación e inserción. Si el valor entregado es menor
al nodo y su lado izquierdo es nulo, se retorna falso. Si no es nulo, se sigue buscando, esta
vez con el nodo izquierdo como principal. Lo mismo para el lado derecho si el valor es mayor al
del nodo. Si el valor es el mismo al del nodo, procedemos a eliminar. En este caso, se solicita
el valor nuevo y se llama a las funciones de eliminación e inserción, se devuelve true. Si 
no se cumplen las condiciones, devuelve falso.

-crea_arbol(Node* &apnodo, int valor): Crea árbol desde el inicio del programa. Si nodo está vacío,
se crea con el valor entregado y se retorna para que no continúe con el resto del código. Si no
existiera el return, el nodo se compararía consigo mismo indicando que se "repite". Si el nodo no 
está vacío, se verifica si el valor es menor al nodo, si lo es, se crea un nodo a la izquierda, si
es mayor a la derecha y si es igual, se indica que ya existe.

Todos los órdenes se detienen si el nodo se encuentra vacío.
-printPreOrder(Node* node): Si existe información en el nodo, se imprime esta primero y luego, se 
llama recursivamente para recorrer los nodos izquierdos y luego, los nodos derechos.

-printInOrder(Node* node): Si existe información en el nodo, se recorren los nodos izquierdos con
la llamada recursiva de la función, luego se imprima el nodo central y se recorren los nodos derechos
con la llamada recursiva.

-printPosOrder(Node* node): Si existe información en el nodo, gracias a la llamada recursiva 
se recorren todos los nodos izquierdos, luego los derechos y al final, se imprime la información
del nodo central.

-recorrerGraviphz(Node* node, ofstream& fp): Si el nodo no está vacío, se chequea que su lado izquierdo
contenga información y si así es, se escribe tanto la del nodo como la de su izquierda. Si no tiene
contenido, se crea un nodo "falso" en forma de punto que en el grafo se visualizará como una flecha
a un punto negro. Indica que no tiene contenido. Lo mismo para el lado derecho. Al final, se llama
recursivamente a la misma función para todos los nodos izquierdos y para todos los nodos derechos.

-visualizar(Node* root): Permite visualizar el grafo. Si no se logra abrir el archivo, muestra error.
Si se abre, se escribe la cabecera, se determina estilo y color de los nodos. Se recorre con la
función anterior y se cierra el archivo. Luego con system "dot -Tpng arbol.dot -o arbol.png" se 
genera el grafo y con "eog arbol.png" se visualiza. 

-menu(): Imprime todas las opciones para el usuario.

-int main(): Se determina un nodo raíz nulo, se crean las variables y se consulta cuántos números 
se ingresarán para las condiciones del for siguiente. Se piden los números y por cada valor se llama
a crea_arbol. Luego, con el árbol ya creado, se muestran las opciones del menú y se pide que se
seleccione una opción. Para todos los casos si la raíz es nula, se indica árbol vacío y se agrega
un break al final. Sin dicho break, el programa pasa al siguiente caso sin preguntarle al usuario.
Para el caso 1, se pide el valor a insertar y se llama a insercion_ABB, si se agrega de manera exitosa,
retorna true. Para el caso 2, se solicita el número a eliminar y se llama a eliminacion_ABB, si se 
logra exitosamente, retorna true. Para el caso 3, se pide el número a buscar y se llama a buscaModifica_ABB.
Para el caso 4, se imprimen los recorridos en pre-in-pos orden llamando a sus funciones correspondientes.
Para el caso 5, se llama a visualizar(). Mientras la opción sea diferente a 6, se repite el do{}.
