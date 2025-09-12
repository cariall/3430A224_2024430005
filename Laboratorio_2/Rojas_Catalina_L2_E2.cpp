#include <iostream>
#include <cstdlib>
using namespace std;

class Pila {
public:
    int max;
    int tope;
    int* datos;

    Pila(int tamaño) {
        max = tamaño;
        tope = -1;
        datos = new int[max];
    }

    bool pila_llena() { 
        return tope == max-1; 
    }

    bool pila_vacia() { 
        return tope == -1; 
    }

    void push(int valor) {
        if (!pila_llena()) {
            tope++;
            datos[tope] = valor;
        } else {
            cout << "Pila llena\n";
        }
    }

    int pop() {
        if (!pila_vacia()) {
            int valor = datos[tope];
            tope--;
            return valor;
        } else {
            cout << "Pila vacía\n";
            return -1;
        }
    }

    int cima() {
        if (!pila_vacia()) {
            return datos[tope];
        }else{
            return -1;
        }
    }

    int buscar(int valor) {
        for (int i = 0; i <= tope; i++) {
            if (datos[i] == valor) { //si dato en posición i == valor, devolvemos
                return i;
        }
    }
        return -1;
    }

    void ver_pila() {
        if (pila_vacia()) cout << "Pila vacía\n";
        else {
            cout << "Pila (de arriba hacia abajo):\n";
            for (int i = tope; i >= 0; i--) {
                cout << datos[i] << endl;
            }
        }
    }
};

void mostrarEstado(Pila** pilas, int m) {
    int altura_maxima = 0;
    for (int i = 0; i < m; i++) {
        if (pilas[i]->tope + 1 > altura_maxima) //se destina tope pila[0] como máximo hasta que haya otro mayor
            altura_maxima = pilas[i]->tope + 1;
    }

    cout << "\nEstado actual de las pilas\n";

    for (int i = 0; i < m; i++) {
        cout << " P" << i << " "; //nombre de las pilas
    }
    cout << "\n";

    for (int tope_mas_alto = altura_maxima - 1; tope_mas_alto >= 0; tope_mas_alto--) { //recorre columnas
        for (int i = 0; i < m; i++) {
            if (tope_mas_alto <= pilas[i]->tope) {//si tope de la pila es más grande que el tope más alto, se imprime (porque va de arriba hacia abajo)
                cout << " " << pilas[i]->datos[tope_mas_alto] << "  ";
            }else{
                cout << "    ";
        }
    } //si no, se espera hasta encontrar un número en la misma fila del tope más alto
        cout << "\n";
    }
}

void ingresarAutomatico(Pila** pilas, int m, int valor) {
    int pila_a_poner = -1; //número cualquiera
    int menos_contenedores = 1000; //cualquier número grande. Es sólo para iniciar

    for (int i = 0; i < m; i++) {
        if (!pilas[i]->pila_llena() && pilas[i]->tope+1 < menos_contenedores) {
            menos_contenedores = pilas[i]->tope+1; //tope menor (con menos contenedores)
            pila_a_poner = i; //número de pila 
        }
    }

    if (pila_a_poner != -1) { //si ninguna cumple condición, pila_a_poner queda en -1
        pilas[pila_a_poner]->push(valor); //si cumplen, se agrega
    } else {
        cout << "No hay espacio disponible\n";
    }
}

void retirarContenedor(Pila** pilas, int m, int valor) {
    int pilaIndex = -1, pos = -1;
    for (int i = 0; i < m; i++) {
        pos = pilas[i]->buscar(valor);
        if (pos != -1) { 
            pilaIndex = i; //si encontramos el número, definimos la pila donde está
            break; }
    }

    if (pilaIndex == -1) { 
        cout << "No se encontró el contenedor\n"; 
        return; 
    }

    cout << "\n+---Movimientos---+\n";

    Pila* p = pilas[pilaIndex];

    while (!p->pila_vacia() && p->cima() != valor) {
        int encima = p->pop();
        cout << "Moviendo contenedor " << encima << endl;

        bool colocado = false;
        for (int j = 0; j < m; j++) {
            if (j != pilaIndex && !pilas[j]->pila_llena()) { //si no está llena la pila y no es la misma donde estamos
                pilas[j]->push(encima); //lo agregamos
                cout << "hacia la pila " << j << endl;
                colocado = true;
                break;
            }
        }
        if (!colocado) {
            cout << "No hay espacio para recolocar " << encima << endl;
            break;
        }
    }

    if (!p->pila_vacia() && p->cima() == valor) { //si no está vacía y el valor es el tope
        p->pop();
        cout << "\n*Contenedor " << valor << " retirado*\n";
    } else {
        cout << "No se pudo retirar el contenedor\n";
    }
}

void menu() {
    cout << "\n+-----------------+\n[1] Retirar\n[2] Mostrar estado\n[0] Salir\n+-----------------+\nSeleccione un número: ";
}

int main(int argc, char* argv[]) { //argc lee cantidad de argumentos de entrada y argv los almacena en cadena de texto
    if (argc < 3) { //por si no se ingresa de forma correcta
        cout << "Cómo ejecutar: " << argv[0] << " n, m. (n=altura máxima de cada pila, m=número de pilas totales)\n"; //argv[0]: nombre del programa
        return 1; //hace que programa se termine sin violar segmento
    }

    int n = atoi(argv[1]); //pasamos los comandos a entero
    int m = atoi(argv[2]);

    if (n <=0 || m <=0) { //comprobación de datos
        cout << "n y m deben ser positivos\n"; 
        return 1; 
    }

    cout << "\nSe crearán: " << m << " pilas de " << n << " contenedores máximo cada una\n\n";

    Pila **pilas = new Pila*[m]; //Pila** pilas guarda dirección de todos los punteros a Pila.
    //new reserva memoria para un arreglo de m elementos que apuntan a Pila
    
    for (int i = 0; i < m; i++) {
        pilas[i] = new Pila(n); //se crean m espacios de memoria para pilas[0]=Pila0
    }

    int contenedores_a_agregar;
    int modo;

    cout << "¿Cuántos contenedores desea agregar?: ";
    cin >> contenedores_a_agregar;

    cout << "\n";
    cout << "¿Prefiere que la distribución sea manual o automática?:\n";
    cout << "[1] Manual\n";
    cout << "[2] Automático\n";
    cout << "Opción: ";
    cin >> modo;

    if (modo == 1) {
        for (int i = 1; i <= contenedores_a_agregar; i++) {
            int pila_destino;

            cout << "\nContenedor " << i << " -> Ingrese número de pila (0 a " << m-1 << "): ";
            cin >> pila_destino;

            if (pila_destino < 0 || pila_destino >= m) { //compruebo datos
                cout << "Pila inválida, intente nuevamente\n";
                i--; 
                continue; //para que no se detenga
            }

            pilas[pila_destino]->push(i);
        }
    } 
    else if (modo == 2) {
        for (int i = 1; i <= contenedores_a_agregar; i++) {
            ingresarAutomatico(pilas, m, i);
        }
    } 
    else {
        cout << "Opción inválida.\n";
    }

    int opcion, valor;
    do {
        menu();
        cin >> opcion;
        switch(opcion) {
            case 1:
                cout << "Número del contenedor a retirar: ";
                cin >> valor;
                retirarContenedor(pilas, m, valor);
                break;
            case 2:
                mostrarEstado(pilas, m);
                break;
            case 0:
                break;
            default:
                cout << "Opción inválida\n";
        }
    } while(opcion != 0);

    return 0;
}
