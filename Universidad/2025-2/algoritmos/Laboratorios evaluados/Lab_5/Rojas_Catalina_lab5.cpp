#include <iostream>
#include <fstream> //generar grafo
#include <cstring>
#include <sstream> //leer archivos
#include <iomanip>
#include <string>
using namespace std;

struct Node {
    string codigo_go;
    string nombre_funcion;
    double score; 
    int FE;
    Node* left; //predeterminado para nodo de la izquierda
    Node* right; //predeterminado para nodo derecha
};

Node* createNode(string codigo, string funcion, double puntaje, int FE) {
    Node* newNode = new Node; //crea nuevo nodo
    newNode->score = puntaje; //se le entrega el dato a score en este nuevo nodo
    newNode->codigo_go = codigo;
    newNode->nombre_funcion = funcion;
    newNode->FE = FE;
    newNode->left = nullptr; //se deja vacío izq y der
    newNode->right = nullptr;
    return newNode; //devolvemos el nodo nuevo con la score
}

void Restructura1(Node** nodocabeza, bool* BO) {
    Node *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    if (*BO) {
        switch (nodo->FE) {
            case -1: 
                nodo->FE = 0; //si es -1 es porque hay diferencia de 1 unidad.
                break;
            case 0:
                nodo->FE = 1; //si es cero, lo mismo.
                *BO = false;
                break;
            case 1: //si es 1, hay desbalance a derecha. Hay más en derecha que en izq.
                nodo1 = nodo->right;
                if (nodo1->FE >= 0) { // rotación DD
                    nodo->right = nodo1->left;
                    nodo1->left = nodo;
                    switch (nodo1->FE) {
                        case 0:
                            nodo->FE = 1;
                            nodo1->FE = -1;
                            *BO = false;
                            break;
                        case 1:
                            nodo->FE = 0;
                            nodo1->FE = 0;
                            *BO = false;
                            break;
                    }
                    nodo = nodo1;
                } else { // rotación DI
                    nodo2 = nodo1->left;
                    nodo->right = nodo2->left;
                    nodo2->left = nodo;
                    nodo1->left = nodo2->right;
                    nodo2->right = nodo1;
                    if (nodo2->FE == 1)
                        nodo->FE = -1;
                    else
                        nodo->FE = 0;
                    if (nodo2->FE == -1)
                        nodo1->FE = 1;
                    else
                        nodo1->FE = 0;
                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }
    *nodocabeza = nodo;
}

void Restructura2(Node** nodocabeza, bool* BO) {
    Node *nodo, *nodo1, *nodo2;
    nodo = *nodocabeza;
    if (*BO) {
        switch (nodo->FE) {
            case 1:
                nodo->FE = 0;
                break;
            case 0: 
                nodo->FE = -1;
                *BO = false;
                break;
            case -1:
                nodo1 = nodo->left;
                if (nodo1->FE <= 0) { // rotación II
                    nodo->left = nodo1->right;
                    nodo1->right = nodo;
                    switch (nodo1->FE) {
                        case 0:
                            nodo->FE = -1;
                            nodo1->FE = 1;
                            *BO = false;
                            break;
                        case -1:
                            nodo->FE = 0;
                            nodo1->FE = 0;
                            *BO = false;
                            break;
                    }
                    nodo = nodo1;
                } else { // rotación ID
                    nodo2 = nodo1->right;
                    nodo->left = nodo2->right;
                    nodo2->right = nodo;
                    nodo1->right = nodo2->left;
                    nodo2->left = nodo1;
                    if (nodo2->FE == -1)
                        nodo->FE = 1;
                    else
                        nodo->FE = 0;
                    if (nodo2->FE == 1)
                        nodo1->FE = -1;
                    else
                        nodo1->FE = 0;
                    nodo = nodo2;
                    nodo2->FE = 0;
                }
                break;
        }
    }
    *nodocabeza = nodo;
}

void InsercionBalanceado(Node** nodocabeza, bool* BO, string codigo, string funcion, double infor) {
    Node* nodo = *nodocabeza;

    if (nodo != nullptr) {
        if (infor < nodo->score) {
            InsercionBalanceado(&(nodo->left), BO, codigo, funcion, infor); 
            if (*BO) {
                switch (nodo->FE) {
                case 1:
                    nodo->FE = 0; 
                    *BO = false;
                    break;
                case 0:
                    nodo->FE = -1;
                    break;
                case -1:
                    Restructura2(nodocabeza, BO); //hay desbalance, rotación a izq
                    break;
                }
        } 
        } else if (infor > nodo->score) { //si score es mayor al nodo
            InsercionBalanceado(&(nodo->right), BO, codigo, funcion, infor); //se inserta a derecha
            if (*BO) { //si 
                switch (nodo->FE) {
                case -1:
                    nodo->FE = 0;
                    *BO = false;
                    break;
                case 0:
                    nodo->FE = 1;
                    break;
                case 1:
                    Restructura1(nodocabeza, BO); //desbalance, rotación a der
                    break;
                }
            }
        } else {
            cout << "El nodo ya se encuentra en el árbol\n";
        }
    } else {
        nodo = new Node();
        nodo->left = nullptr;
        nodo->right = nullptr;
        nodo->score = infor;
        nodo->nombre_funcion = funcion;
        nodo->codigo_go = codigo;
        nodo->FE = 0;
        *BO = true;
        *nodocabeza = nodo;
    }
}

void importar_desde_csv(Node*& root, const string& nombreArchivo) {
    ifstream infile(nombreArchivo);
    if (!infile.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << "\n";
        return;
    }

    string linea;
    getline(infile, linea); // saltar cabecera

    while (getline(infile, linea)) {
        if (linea.empty()) continue;

        char sep = (linea.find('\t') != string::npos) ? '\t' : ','; //separado por coma o tab

        string codigo, funcion, scoreStr;
        stringstream ss(linea);

        getline(ss, codigo, sep);
        getline(ss, funcion, sep);
        getline(ss, scoreStr, sep);

        if (!codigo.empty() && !funcion.empty() && !scoreStr.empty()) {
            double score = stod(scoreStr);
            bool inicio = false;
            InsercionBalanceado(&root, &inicio, codigo, funcion, score);
        }
    }

    infile.close();
    cout << "=== Árbol importado desde " << nombreArchivo << " ===\n";
}

bool BusquedaPorCodigo(Node* nodo, const string& codigo) {
    if (nodo == nullptr) {
        return false;
    }
     
    if (nodo->codigo_go == codigo) {
        return true;
    }

    return BusquedaPorCodigo(nodo->left, codigo) || BusquedaPorCodigo(nodo->right, codigo);
    }

void PreOrden(Node* a, ofstream& fp) {
    if (a != nullptr) {

         fp << "\"" << a->score << "\" [label=\""
           << "Función: " << a->nombre_funcion << "\\n"
           << "Score: " << a->score << "\\n"
           << "FE: " << a->FE
           << "\", style=filled, fillcolor=pink, shape=box];\n";

        if (a->left != nullptr) {
            fp << a->score << " -> " << a->left->score << ";\n"; //conecto el original con el izq
        } else {
            string nodo_falso_i = to_string(a->score) + "i"; //si está vacío, lo paso a string con i de izq
            fp << "\"" << nodo_falso_i << "\" [shape=point];\n"; //determino que nodo_falso_i será un punto
            fp << a->score << " -> \"" << nodo_falso_i << "\";\n"; //asocio el original con nodo falso izq
        }
        if (a->right != nullptr) { //lo mismo de arriba pero hacia la derecha
            fp << a->score << " -> " << a->right->score << ";\n";
        } else {
            string nodo_falso_d = to_string(a->score) + "d";
            fp << "\"" << nodo_falso_d << "\" [shape=point];\n"; 
            fp << a->score << " -> \"" << nodo_falso_d << "\";\n"; 
        }
        PreOrden(a->left, fp);
        PreOrden(a->right, fp);
    }
}

void GenerarGrafo(Node* root) {
    if (!root) return;
    ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=lightblue];\n";
    PreOrden(root, fp);
    fp << "}\n";
    fp.close();
    system("dot -Tpng grafo.txt -o grafo.png");
    system("eog grafo.png &"); // para linux
}

void menu() {
    cout << "\n=== Menú creación árbol binario===\n";
    cout << "1. Insertar término GO\n";
    cout << "2. Buscar término GO\n";
    cout << "3. Generar el grafo\n";
    cout << "4. Salir\n";
}


int main(int argc, char** argv) {
    cout << fixed << setprecision(2);
    int opcion;
    Node* root = nullptr; //nodo raíz está vacío

    if (argc != 2) {
        cerr << "Usa: " << argv[0] << " nombre_archivo_CSV\n";
        return 1;
    }
    string nombre_archivo = argv[1];
    importar_desde_csv(root, argv[1]);
    
    do {
        menu();
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                { string valor;
                string funcion;
                double score;
                bool inicio = false;
                cout << "Ingrese código a insertar: ";
                cin >> valor;
                cout << "Ingrese función: ";
                cin >> funcion;
                cout << "Ingrese score: ";
                cin >> score;
                cin.ignore();
                InsercionBalanceado(&root, &inicio, valor, funcion, score);
                }
                break; 
            case 2:
                if (root == nullptr) {
                    cout << "Árbol vacío\n";
                } else {
                    string codigo;
                    cout << "Buscar código (escribir exacto): ";
                    cin >> codigo;
                    if (BusquedaPorCodigo(root, codigo)) {
                        cout << "Se ha encontrado\n";
                    } else {
                        cout << "No se ha encontrado\n";
                    }
                }
                break;
            case 3:
                if (root == nullptr) {
                    cout << "Árbol vacío.\n";
                } else {
                    GenerarGrafo(root);
                }
                break;
            }
        } while (opcion != 4);
    return 0;
}
