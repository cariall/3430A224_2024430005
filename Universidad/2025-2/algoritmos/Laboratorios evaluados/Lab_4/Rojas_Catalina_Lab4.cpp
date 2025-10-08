#include <iostream>
#include <fstream> //generar grafo
using namespace std;

struct Node {
    int info; 
    Node* left; //predeterminado para nodo de la izquierda
    Node* right; //predeterminado para nodo derecha
};

Node* createNode(int data) {
    Node* newNode = new Node; //crea nuevo nodo
    newNode->info = data; //se le entrega el dato a info en este nuevo nodo
    newNode->left = nullptr; //se deja vacío izq y der
    newNode->right = nullptr;
    return newNode; //devolvemos el nodo nuevo con la info
}

bool insercion_ABB(Node* &apnodo, int info) {
    if (apnodo == nullptr) {
        apnodo = createNode(info); //creo nodo si ya existe una raíz
        return true;
    }
    
    if (info < apnodo->info) { //si el n° es menor al del nodo
        if (apnodo->left == nullptr) { //y si a la izq está vacío
            Node * aux = createNode(info); //se crea el nodo con dicha info
            apnodo->left = aux; //lo ponemos a la izq 
        } else {
        insercion_ABB(apnodo->left, info); //si es mayor pgtamos por el sgte nodo izq
    }
    } else if (info > apnodo->info) {
        if (apnodo->right == nullptr) {
            Node* aux = createNode(info); //se crea el nodo con dicha info
            apnodo->right = aux; //lo ponemos a la izq 
        } else {
            insercion_ABB(apnodo->right, info);
        }
    } else {
        cout << "El nodo ya se encuentra en el árbol\n";
        return false; //así no se duplica el msj y sigue
    }
    return true;
}

bool busqueda_ABB(Node* &apnodo, int info) {
    if (apnodo == nullptr) {
        cout << "Número no se encuentra en el árbol\n";
        return false;
    }

    if (info < apnodo->info) {
        //cout << "info: " << info << " apnodo->info: " << apnodo->info << endl;
        if (apnodo->left == nullptr) {
            cout << "Número no se encuentra en el árbol\n";
            return false;
        } else {
            busqueda_ABB(apnodo->left, info);
        }
    } else if (info > apnodo->info) {
        //cout << "info: " << info << " apnodo->info: " << apnodo->info << endl;
        if (apnodo->right == nullptr) {
            cout << "Número no se encuentra en el árbol\n";
            return false;
        } else {
            busqueda_ABB(apnodo->right, info);
            return false;
        }
    } else if (info == apnodo->info) { 
        //cout << "info: "<< info << " nodo: " << apnodo->info << endl; 
        cout << "Número encontrado.\n"; 
        int nuevoValor;
        cout << "Ingrese nuevo valor: ";
        cin >> nuevoValor;
        apnodo->info = nuevoValor;
        cout << "Número modificado.\n";
        //cout << "final apnodo->info: " << apnodo->info;
        return true;
    }
    return false;
}

bool eliminacion_ABB(Node* &apnodo, int info) {
    if (apnodo == nullptr) { 
        cout << "El nodo no se encuentra en el árbol\n";
        return false;
    }

    if (info < apnodo->info) { //ver si info es menor
        return eliminacion_ABB(apnodo->left, info); //buscamos por izq

    } else if (info > apnodo->info) { //si es mayor
        return eliminacion_ABB(apnodo->right, info); //busco por der
    
    } else if (info == apnodo->info) { //si info == apnodo->info
        Node* aux = apnodo; //nodo queda en aux 

        if (aux->right == nullptr) { //si el de la derecha está vacío
            apnodo = aux->left; //vamos al izquierdo

        } else if (aux->left == nullptr) { //si izq está vacío
            apnodo = aux->right; //vamos a der

        } else { //si no están vacíos
            Node* progenitor = aux; //pongo aux en otro
            Node* hijo_izquierdo = aux->left; //y guardo el de su izq
            
            while (hijo_izquierdo->right != nullptr) {
                progenitor = hijo_izquierdo; //progenitor se vuelve su hijo para seguir búsqueda
                hijo_izquierdo = progenitor->right; //hijo va donde no está vacío
            } 
            
            apnodo->info = hijo_izquierdo->info; //ahora nodo tiene info 
            
            if (progenitor == aux) { //si progenitor es el original (está directo a su hijo)
                progenitor->left = hijo_izquierdo->left; //su hijo será el izq del hijo
            } else { //si hijo no está directamente abajo de progenitor
                progenitor->right = hijo_izquierdo->left; //su hijo derecho queda como el izq del hijo
            
            } 
            
            delete hijo_izquierdo;
            // cout << "Nodo eliminado correctamente\n";
            return true; 
            }

            delete aux;
            // cout << "Nodo eliminado correctamente\n";
            return true;
        }
        return false;
    }

void crea_arbol(Node* &apnodo) {
    if (apnodo == nullptr) { //si nodo está vacío
        int valor;
        cout << "Ingrese valor para el nodo: ";
        cin >> valor; //se le agrega valor
        apnodo = createNode(valor); //apnodo será nodo nuevo
    }

    char resp;

    cout << "¿Existe nodo por izquierda de " << apnodo->info << "? (s/n): ";
    cin >> resp;
    if (resp == 's' || resp == 'S') {
        apnodo->left = nullptr; // inicializar
        crea_arbol(apnodo->left); // llamada recursiva
    } else {
        apnodo->left = nullptr;
    }

    cout << "¿Existe nodo por derecha de " << apnodo->info << "? (s/n): ";
    cin >> resp;
    if (resp == 's' || resp == 'S') {
        apnodo->right = nullptr; //creamos espacio vacío para
        crea_arbol(apnodo->right); // ponerle la info
    } else {
        apnodo->right = nullptr; //si no, queda vacío
    }
}

void printPreOrder(Node* node) {
    if (node == nullptr) { //si nodo está vacío, no se imprime nada
        return;
    }
    cout << node->info << " ";   // imprimo nodo actual
    printPreOrder(node->left);   // recorro subárbol izq
    printPreOrder(node->right);  // recorro subárbol der
}

void printInOrder(Node* node) {
    if (node == nullptr) { //si nodo está vacío, no se imprime nada
        return;
    }
    printInOrder(node->left);
    cout << node->info << " ";
    printInOrder(node->right);
}

void printPosOrder(Node* node) {
    if (node == nullptr) { //si nodo está vacío, no se imprime nada
        return;
    }
    printPosOrder(node->left);
    printPosOrder(node->right);
    cout << node->info << " ";
}

void recorrerGraphviz(Node* node, ofstream& fp) {
    if (node != nullptr) {
        if (node->left != nullptr) { //si tiene hijo izq
            fp << node->info << "->" << node->left->info << ";" << endl;
        } else {
            string cadena = to_string(node->info) + "i"; //info nodo se pasa a string con i de izq (grafo muestra nodo falso)
            fp << "\"" << cadena << "\" [shape=point];" << endl; //crea nodo falso como un punto
            fp << node->info << "->\"" << cadena << "\";" << endl; //dibuja el nodo real con flecha al falso
        }

        if (node->right != nullptr) { //si tiene hijo der
            fp << node->info << "->" << node->right->info << ";" << endl;
        } else {
            string cadena = to_string(node->info) + "d";
            fp << "\"" << cadena << "\" [shape=point];" << endl;
            fp << node->info << "->\"" << cadena << "\";" << endl;
        }

        recorrerGraphviz(node->left, fp); //se hace para la izq
        recorrerGraphviz(node->right, fp); //y la derecha
    }
}

void visualizar(Node* root) {
    ofstream fp("arbol.dot");

    if (!fp.is_open()) {
        cerr << "Error al abrir el archivo arbol.dot" << endl;
        return;
    }

    fp << "digraph G {" << endl; //cabecera
    fp << "node [style=filled fillcolor=yellow];" << endl; //estilo y color

    recorrerGraphviz(root, fp); //raíz y archivo

    fp << "}" << endl;
    fp.close(); //cierro archivo

    cout << "Archivo 'arbol.dot' generado correctamente.\n";

    system("dot -Tpng arbol.dot -o arbol.png"); //crea imagen png

    system("eog arbol.png"); //abre imagen. linux: eog
}

void menu() {
    cout << "\n=== Menú creación árbol binario===\n";
    cout << "1. Insertar número\n";
    cout << "2. Eliminar número buscado\n";
    cout << "3. Modificar un elemento buscado\n";
    cout << "4. Mostrar contenido en pre/in/pos orden\n";
    cout << "5. Generar el grafo\n";
    cout << "6. Salir\n";
}

int main() {
    Node* root = nullptr; //nodo raíz está vacío
    int opcion;

    cout << "\nConstrucción del árbol binario:\n";
    crea_arbol(root); //ahora

    do {
        menu();
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                if (root == nullptr) {
                    cout << "Árbol vacío\n";
                } else {
                    int valor;
                    cout << "Ingrese número a insertar: ";
                    cin >> valor;
                    cin.ignore();
                    if (insercion_ABB(root, valor)) {
                        cout << "Número agregado.\n";
                    }
                }
                break;
            case 2:
                if (root == nullptr) {
                    cout << "Árbol está vacío.\n";
                } else {
                    int eliminar;
                    cout << "Ingrese número a eliminar: ";
                    cin >> eliminar;
                    cin.ignore();  
                    if (eliminacion_ABB(root, eliminar)) {
                        cout << "Nodo eliminado.\n";
                    }
                    } 
                break;
            case 3:
                int aBuscar;
                if (root == nullptr) {
                    cout << "Árbol vacío\n";
                } else {
                    cout << "Ingrese número a buscar: ";
                    cin >> aBuscar;
                    cin.ignore();
                    busqueda_ABB(root, aBuscar);
                }
                break;
            case 4:
                cout << "\nRecorrido en preorden: ";
                printPreOrder(root);
                cout << "\nRecorrido en inorden: ";
                printInOrder(root);
                cout << "\nRecorrido en posorden: ";
                printPosOrder(root);
                cout << endl;
                break;
            case 5:
                if (root == nullptr) {
                    cout << "Árbol vacío.\n";
                } else {
                    visualizar(root);
                }
            default:
                break;
            }
        } while (opcion != 6);
    return 0;
}
