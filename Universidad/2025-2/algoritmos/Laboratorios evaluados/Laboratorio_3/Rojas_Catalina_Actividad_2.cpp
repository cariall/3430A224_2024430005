#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

struct Nodo {
    string resn; //residue name
    string resid; //residue identifier (número u otro)
    Nodo* siguiente;
};

bool cola_vacia(Nodo* &cola) {
    if (cola == nullptr) {
        return true;
    }
    return false;
}

bool cola_llena(Nodo* &cola) {
    return false;
}

void insertar_cola(Nodo*& cola, string resn, string resid) {
    Nodo* nuevo = new Nodo(); 
    nuevo->resn = resn;
    nuevo->resid = resid;
    nuevo->siguiente = nullptr; //último nodo null, si apuntamos a otra cosa, no será el último nodo

    if (cola_llena(cola)) {
        cout << "La cola está llena.\n";
    }

    if (cola_vacia(cola)) { //si espacio está vacío
        cola = nuevo; //ahí se agrega el nuevo
    } else { //si no está vacío
        Nodo* aux = cola; //se crea nodo auxiliar con dicha info
        while (aux->siguiente != nullptr) { //y si el siguiente no está vacío
            aux = aux->siguiente; //seguiremos al siguiente
        }
        aux->siguiente = nuevo; //y cuando sea null, se pone lo nuevo
    }
    //cout << "Aminoácido " << resn << " agregado a la cola.\n";
}

void mostrar(Nodo* cola) {
    if (cola_vacia(cola)) {
        cout << "La cola está vacía.\n";
        return;
    }

    cout << "\nContenido actual de la cola:\n";
    int pos = 1;
    Nodo* actual = cola; 
    while (actual != nullptr) {
        cout << pos << ". " << actual->resn << " | "
             << actual->resid << endl;
        actual = actual->siguiente;
        pos++;
    }
}

bool borrar_posicion(Nodo*& cola, int posicion) {
    if ((cola_vacia(cola)) || posicion < 1) return false;

    Nodo* actual = cola;
    if (posicion == 1) {  
        cola = actual->siguiente;
        delete actual;
        return true;
    }

    Nodo* anterior = nullptr; //recorre hasta la posición anterior
    int contador = 1;
    while (actual != nullptr && contador < posicion) {
        anterior = actual;
        actual = actual->siguiente;
        contador++;
    }

    if (actual == nullptr) return false; 

    anterior->siguiente = actual->siguiente;
    delete actual;
    return true;
}

bool modificar_resn(Nodo* &cola, string resid, string mutar) {
    string nuevo_resn;
    Nodo* actual = cola;
    if (actual == nullptr) return false;

    while (mutar != actual->resid) {
        actual = actual->siguiente;
    }
    
    if (mutar == actual->resid) {
        cout << "ingrese nuevo resn: \n";
        cin >> nuevo_resn;
        actual->resn = nuevo_resn;
        return true;
    }
    return false;
}

void importar_desde_txt(Nodo*& cola, const string& nombreArchivo) {
    ifstream infile(nombreArchivo);
    if (!infile.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << "\n";
        return;
    }

    string resn, resid;
    while (infile >> resn >> resid) { // lee palabra + número separados por espacio
        insertar_cola(cola, resn, resid);
    }

    infile.close();
    cout << "=== Lista importada desde " << nombreArchivo << " ===\n";
}    

void exportar_dot(Nodo* cola, const string& nombreDot) {
    if (cola_vacia(cola)) {
        cout << "La cola está vacía, no se puede exportar.\n";
        return;
    }

    ofstream outfile(nombreDot);
    if (!outfile.is_open()) {
        cerr << "No se pudo crear el archivo " << nombreDot << "\n";
        return;
    }

    outfile << "digraph G {\n"; // encabezado de graphviz
    outfile << "rankdir=LR;\n";
    outfile << "node [style=filled, fillcolor=yellow];\n";

    Nodo* actual = cola;
    while (actual != nullptr && actual->siguiente != nullptr) {
        outfile << actual->resn << actual->resid
                << " -> "
                << actual->siguiente->resn << actual->siguiente->resid
                << ";\n";
        actual = actual->siguiente;
    }

    outfile << "}\n";
    outfile.close();
    cout << "+ Archivo Graphviz generado: " << nombreDot << "\n";
}

void generar_png(const string& nombreDot, const string& nombrePng) {
    string comando = "dot -Tpng " + nombreDot + " -o " + nombrePng;
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "+ Imagen generada: " << nombrePng << "\n";
    } else {
        cout << "Error.\n";
    }
}

int main() {
    Nodo* cola = nullptr;
    int opcion;
    string resn, resid;
    int pos;
    string mutar;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Importar archivo txt con resn, resid\n";
        cout << "2. Insertar un nuevo residuo\n";
        cout << "3. Modificar resn de un residuo\n";
        cout << "4. Eliminar un residuo en una posición específica\n";
        cout << "5. Mostrar cola\n";
        cout << "6. Exportar lista a archivo Graphviz (.dot)\n";
        cout << "7. Generar imagen en formato png\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                {
                    string archivo;
                    cout << "Ingrese nombre del archivo .txt: ";
                    cin >> archivo;
                    importar_desde_txt(cola, archivo);
                }
                break;
            case 2:
                cout << "resn: ";
                getline(cin, resn);
                cout << "resid: ";
                getline(cin, resid);
                insertar_cola(cola, resn, resid);
                break;
            case 3:
                cout << "Ingrese resid del resn a mutar: \n";
                cin >> mutar;
                if (modificar_resn(cola, resid, mutar)) {
                    cout << "Se modificó resn de resid: " << mutar << endl;
                }
                break;
            case 4:
                cout << "Ingrese la posición a borrar: ";
                cin >> pos;
                if (borrar_posicion(cola, pos))
                    cout << "Se borró el residuo en la posición " << pos << ".\n";
                else
                    cout << "Posición inválida.\n";
                break;
            case 5:
                mostrar(cola);
                break;
            case 6:
                exportar_dot(cola, "estructura.dot");
                break;
            case 7:
                generar_png("estructura.dot", "estructura.png");
                break;
            case 8:
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 8);

    return 0;
}