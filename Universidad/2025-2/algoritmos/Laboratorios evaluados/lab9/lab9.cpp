#include <iostream>
using namespace std;

const int N = 20; //20 elementos en arreglo

struct Nodo {
    int valor;
    Nodo* next;
};

int tabla[N];       // guardamos elemento por posición
Nodo* lista[N];     // lista con kos que colisionan

int funcion_hash(int x) { 
    int pos = x % N; //divido en 20
    if (pos < 0) { //si eso da menos que 0
        pos += N; //le sumo N
    }
    return pos;
}

int funcion_hash_dos(int x) {
    int pos = 7-(x%7); 
    if (pos < 0) { //si da negativo, se le suma 7. 
        pos += 7;
    }
    return pos;
}

void inicializar() { //crea tabla con espacios y lista enlazada con vacíos
    for (int i = 0; i < N; ++i) {
        tabla[i] = -1;   // tomamos -1 como vacío
        lista[i] = nullptr;
    }
}

void imprimirTabla() {
    cout << "\nTabla\n";
    for (int i = 0; i < N; ++i) {
        if (tabla[i] == -1)  //si posición i en arreglo está vacío
        cout << "[" << i << "]: -\n"; //imprime un guión
        else //si no está vacío, imprime valor
        cout << "[" << i << "]: " << tabla[i] << "\n";
    }
}

void imprimirListas() {
    cout << "\nColisiones:\n"; //lista enlazada
    bool alguna = false; //determinamos falso
    for (int i = 0; i < N; ++i) { //por toda la lista 
        if (lista[i] != nullptr) { //si no está vacía
            alguna = true; //definimos true
            cout << "Posición " << i << ": ";
            Nodo* p = lista[i]; //p guardará el valor de lista[i]
            while (p != nullptr) { //si no está vacío
                cout << p->valor; //imprimo el valor
                if (p->next != nullptr) //si el siguiente no está vacío
                cout << " -> ";
                p = p->next; //p ahora será el siguiente y sigue el ciclo
            }
            cout << "\n";
        }
    }
    if (!alguna) cout << "ninguna\n";
}

void pruebaLineal(int tabla[], int N, int valor) {
    int D = funcion_hash(valor);

    if (tabla[D] == -1) { //si está vacío,
        tabla[D] = valor; //agrego valor
        cout << "Insertado el número " << valor << " en posición [" << D << "]\n";
        return;
    } else { //si no está vacío, hay colisión

    cout << "Colisión en tabla["<<D<<"]\n";
    int Dx=(D+1)%N; 
     //si es menor a N, no está vacío, no es el valor, ni es igual al anterior
    while ((tabla[Dx] != -1) && (Dx != D)) {
            Dx = (Dx+1)%N; 
    }

    if (tabla[Dx] == -1) { //si está vacío o es igual al sgte
        tabla[Dx] = valor; 
        cout << "Reasignado "<<valor<<" en posición["<<Dx<<"]\n";
    } else { //si no está vacío, se informa
        cout << "Tabla llena, no se insertó" << "\n";
    }
    }
}

void pruebaCuadratica(int tabla[], int N, int valor) {
    int D = funcion_hash(valor);

    if (tabla[D] == -1) { //si está vacío,
        tabla[D] = valor; //agrego valor
        cout << "Insertado el número " << valor << " en posición [" << D << "]\n";
        return;
    } else {
        cout << "Colisión en tabla [" << D << "]\n";

        int I = 1; //parto en uno
        int Dx = (D+(I*I)) % N; //nueva posición

        while ((tabla[Dx] != -1) && (Dx!=D)) { //mientras tenga algo y sea diferente a la posición anterior
            I = I +1; //va aumentando 
            Dx = (D+(I*I)) % N; //Si posición es 2, pasa a ser 2+(0*0), luego 2+(1*1). %N para que no se salga del arreglo
        }
        if (tabla[Dx] == -1) {
            tabla[Dx] = valor;  //se reasigna en nueva posición
            cout << "Reasignado "<<valor<<" en posición["<<Dx<<"]\n";
        } else { //si no está vacío, se informa
            cout << "Tabla llena, no se insertó" << "\n";
        }
    }
}

void dobleDireccion(int tabla[], int N, int valor) {
    int D = funcion_hash(valor);

    if (tabla[D] == -1) { //si está vacío,
        tabla[D] = valor; //agrego valor
        cout << "Insertado el número " << valor << " en posición [" << D << "]\n";
        return;
    } else {
        cout << "Colisión en tabla [" << D << "]\n";
        int hash_dos = funcion_hash_dos(valor); //nueva fórmula. Colisión en 3, hash2=6.5, bueno, 6 || hash2=7
        int I = 1; 
        // nueva posición = (3+1*6)= 9 || (3+1*7)=10 posición
        int Dx = (D+I*hash_dos)%N; //A la colisión se le suma 1 y se multiplica por nueva fórmula

        while ((tabla[Dx] != -1) && I<N) { //si tiene contenido
            I++; //sumo a i
            Dx = (D+I*hash_dos)%N; //nueva posición sigue la fórmula
        }

        if ((tabla[Dx] == -1)) {
            tabla[Dx] = valor;  //se reasigna en nueva posición
            cout << "Reasignado "<<valor<<" en posición["<<Dx<<"]\n";
        } else { //si no está vacío, se informa
            cout << "Tabla llena, no se insertó" << "\n";
        }
    }
}

void encadenamiento(int tabla[], int N, int valor) {
    int D = funcion_hash(valor);
    
    if (tabla[D] == -1) {
        tabla[D] = valor;
        cout << "Insertado "<<valor<<" en tabla["<<D<<"]\n";
        return;
    } else {
        cout << "La información está en la posición "<<D<<"\n";
    }

    cout << "Colisión para " << valor << " en índice " << D << ".\n";

    Nodo* nodo = new Nodo{valor, nullptr};

    if (lista[D] == nullptr) { //si está disponible
        lista[D] = nodo; //se guarda info
    } else {
        Nodo* p = lista[D]; //si no, se guarda info en p 
        while (p->next != nullptr) { //y si el sgte no está vacío
            p = p->next; //se vuelve p 
        }
        p->next=nodo; //y así el siguiente guardará la info del nodo
    }

    Nodo* Q= lista[D];

    while ((Q!=nullptr) && (Q->valor != valor)) {
        Q = Q->next;
    }

    if (Q==nullptr) {
        cout <<"La información no se encuentra en la lista\n";
    } else {
        cout << "La información se encuentra en la lista\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: ./hash L\n";
        return 1;
    }

    char modo = argv[1][0]; //ponen la letra 

    inicializar(); //crea espacios
    
    cout << "Ingrese 20 números: \n";
    for (int i = 0; i < N; ++i) {
        int numero;
        cout << "Número " << i+1 << ": ";
        cin >> numero;
        cin.ignore();

        int pos = funcion_hash(numero);

        if (modo == 'L' || modo == 'l') {
            pruebaLineal(tabla, N, numero); //agrega si está vacío y si no, reasigna
        } else if (modo == 'C' || modo == 'c') {
            pruebaCuadratica(tabla, N, numero);
        } else if (modo == 'D' || modo == 'd') {
            dobleDireccion(tabla, N, numero);
        } else if (modo == 'E' || modo == 'e') {
            encadenamiento(tabla, N, numero);
            imprimirListas();
        }
        imprimirTabla();
    }

    return 0;
}
