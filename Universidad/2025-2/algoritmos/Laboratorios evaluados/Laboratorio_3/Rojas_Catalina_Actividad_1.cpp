#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    string nombre;
    string carrera;
    float promedio;
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

void insertar_cola(Nodo*& cola, string nombre, string carrera, float promedio) {
    Nodo* nuevo = new Nodo(); 
    nuevo->nombre = nombre;
    nuevo->carrera = carrera;
    nuevo->promedio = promedio;
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
    cout << "Estudiante " << nombre << " agregado a la cola.\n";
}

bool eliminar_cola(Nodo*& cola, string& nombre, string& carrera, float& promedio) {
    if (cola_vacia(cola)) {
        cout << "La cola está vacía.\n";
        return false; //no hay nada que eliminar
    }
    
    Nodo* aux = cola; //si hay algo, se usa un auxiliar con la info
    nombre = aux->nombre;
    carrera = aux->carrera;
    promedio = aux->promedio;
    cola = aux->siguiente; //pasamos al siguiente espacio
    delete aux; //elimino el nodo
    return true; //indica éxito
}

void mostrar(Nodo* cola) {
    if (cola_vacia(cola)) {
        cout << "La cola está vacía.\n";
        return;
    }

    cout << "\nContenido actual de la cola:\n";
    int pos = 1;
    Nodo* actual = cola; //último estudiante
    while (actual != nullptr) {
        cout << pos << ". " << actual->nombre << " | "
             << actual->carrera << " | Promedio: "
             << actual->promedio << endl;
        actual = actual->siguiente;
        pos++;
    }
}

int main() {
    Nodo* cola = nullptr;
    int opcion;
    string nombre, carrera;
    float promedio;
    int pos;

    do {
        cout << "\n=== MENU COLA DE ESTUDIANTES ===\n";
        cout << "1. Insertar un nuevo estudiante\n";
        cout << "2. Eliminar estudiante al frente de la cola\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Carrera: ";
                getline(cin, carrera);
                cout << "Promedio: ";
                cin >> promedio;
                cin.ignore();
                insertar_cola(cola, nombre, carrera, promedio);
                break;
            case 2:
                if (eliminar_cola(cola, nombre, carrera, promedio)) {
                    cout << "Se desapiló a: "
                         << nombre << " | " << carrera
                         << " | Promedio: " << promedio << endl;
                }
                break;
            case 3:
                mostrar(cola);
                break;
            case 4:
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 4);

    return 0;
}