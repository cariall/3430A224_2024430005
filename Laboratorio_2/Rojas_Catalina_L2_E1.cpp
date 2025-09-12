#include <iostream>
using namespace std;

class Pila {
public: //sacado de c++ classes and objects
    int max;
    int tope;
    int *datos; //memoria donde estarán los datos
    bool band;

    Pila(int tamaño) {
        max = tamaño; 
        tope = -1; //está vacía
        datos = new int[max]; //new asigna memoria que devuelve un puntero al objeto
    }

    bool pila_llena() {
        return tope == max-1; //devuelve un booleano. Si es true, está lleno
    }

    bool pila_vacía() {
        return tope == -1; //esto devuelve un false o true. Si es true, está vacía
    }

    void push(int valor) {
    if (!pila_llena()) { 
        tope++; //sumamos 1 al tope anterior
        datos[tope] = valor; //en la posición de tope, le asignamos el valor
        cout << "Número " << valor << " agregado\n";
    } else {
        cout << "Pila llena\n";
    }
    }

    void ver_pila() {
        if (pila_vacía()) {
            cout << "Pila vacía\n";
        } else {
            cout <<"\n";
            cout << "+------Pila:------+\n"; 
            for (int i = tope; i >= 0; i--) { //desde el tope hacia abajo
                cout << datos[i] << endl; //se imprime el dato
            }
        }
    }

    int pop() {
    if (!pila_vacía()) {
        int valor = datos[tope]; //valor recibe último dato
        tope--; //se reduce el tope en uno
        return valor; //devuelve el valor del último dato para imprimirlo en main
    } else {
        cout << "Pila vacía\n";
        return 0;
    }
}
};

void menu() {
    cout<<"+-----------------+\n";
    cout<<"[1] Agregar/push\n";
    cout<<"[2] Remover/pop\n";
    cout<<"[3] Ver pila\n";
    cout<<"[0] Salir\n";
    cout<<"+-----------------+\n";
}

int main() {
    int tamaño;
    cout << "Ingrese el tamaño máximo de la pila: ";
    cin >> tamaño;
    Pila pila(tamaño); //creo objeto pila de clase Pila y le entrego el tamaño

    int valor;
    int opcion;

    do {
        menu();
        cin>>opcion;

        if (opcion == 1) {
            cout<<"Ingrese valor: \n";
            cin>>valor;
            pila.push(valor);
            }

        if (opcion == 2) {
            int valor_pop = pila.pop();
            if (valor_pop != 0) {
                cout << "Se removió "<< valor_pop <<"\n";
            }
        }

        if (opcion == 3) {
            pila.ver_pila();
        }
        } while (opcion != 0);
    return 0;
}

