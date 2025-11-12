#include <iostream>
#include <cstdlib> //para rand(). Generar elementos aleatorios del vector
#include <chrono> //para milisegundos. 
using namespace std;
using namespace std::chrono;

double burbuja_menor(int A[], int N) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //referencia en readme
    for (int i=1; i<N; i++) { //de izq a derecha -- {3,2,4,1} -> 3,DOS,4,1 -> sumo 1
        for (int j=N-1; j>=i; j--) { //de derecha a izq -- {3,2,4,1} -> {3,2,CUATRO,1} -> resto 1
            if (A[j-1] > A[j]) { //si el de la izq es mayor al de la derecha -- Si [j-1] (CUATRO) > [j] (UNO)
                int aux = A[j-1]; //AUX va a ser el mayor -- guardo [j-1] (CUATRO) en aux
                A[j-1] = A[j]; //el menor pasa a posición de mayor -- [j-1] (CUATRO) va a estar en posición de [j] (UNO)
                A[j] = aux; //y este nuevo -- y en la posición de [j] (UNO) va a estar la información del CUATRO 
            }
        }
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now(); //devuelve un objeto tipo DURATION
    duration<double, milli> duracion = duration_cast<duration<double>>(t2-t1); //milli por milisegundos
    return duracion.count();
}

double insercion(int A[], int N) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //referencia en readme
    for (int i=1; i<N; i++) { //desde 2 a n, sumo -- {3,2,4,1} -> {3,DOS,4,1}
        int aux = A[i]; // valor actual se guarda en aux -- {3,2,4,1} -> {3,DOS,4,1} -> aux = DOS
        int k = i-1; // k posición de la izquierda -- {3,2,4,1} -> {TRES,2,4,1} 
        while ((k >= 0) && (aux < A[k])) { //mientras k sea mayor o igual a 0 y aux (DOS) sea menor al de su izquierda
            A[k+1] = A[k]; // -- {3,DOS,4,1} [k+1] (DOS) se cambia a posición del 3 [k] -> {DOS,3,4,1}
            k = k-1; // y ahora a k se le resta uno para consultar de nuevo hacia su izquierda y cambiar si es necesario
        }
        A[k+1] = aux; // [k+1] es {DOS,3,4,1}
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now(); //devuelve un objeto tipo DURATION
    duration<double, milli> duracion = duration_cast<duration<double>>(t2-t1); //milli por milisegundos
    return duracion.count();
}

double seleccion(int A[], int N) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //referencia en readme

    for (int i=0; i<N-1; i++) { //de posición 0 a n-1
        int menor = A[i]; //menor será el valor actual
        int k = i; //k guarda la posición del actual
        for (int j=i+1; j<N; j++) { //para j desde la posición sgte a la actual hasta n
            if (A[j] < menor) { //si el de la derecha es menor al actual
                menor = A[j]; //la posición actual guardará valor del de la derecha
                k = j; //y en k se guardará la posición del de la derecha
            }
        }
        A[k] = A[i]; //el de la derecha guardará el valor del actual
        A[i] = menor; //y el actual guardará el valor del menor 
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now(); //devuelve un objeto tipo DURATION
    duration<double, milli> duracion = duration_cast<duration<double>>(t2-t1); //milli por milisegundos
    return duracion.count();
}

double shellsort(int A[], int N) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //referencia en readme

    int entero = N+1; //salto entre elementos
    bool band = false; //indica intercambio o no
    while (entero > 1) { //mientras el salto sea mayor a 1, ordenamos
        //cout << "entero antes: " << entero << endl;
        entero = entero/2; //reducimos el salto a la mitad
        //cout << "entero después: " << entero << endl;
        band = true; //hay que seguir comparando
        while (band == true) { //si se intercambió, seguimos comparando
            band = false; 
            int i = 0; 
            while ((i+entero) < N) { //si entero=3, compara A[1] con A[4], A[2] con A[5]
                if (A[i] > A[i+entero]) { //si el primero es mayor
                    //cout << "A[i]: " << A[i] << "A[i+entero]: "<< A[i+entero]<<endl;
                    int aux = A[i]; //guardamos la info en aux
                    //cout << "aux: " << A[i] << endl;
                    A[i] = A[i+entero]; //y A[1] tendrá la info de A[4]
                    A[i+entero] = aux; //y A[4] guaradará la info de aux
                    band = true; //true para que se siga comparando
                }
            i = i+1;
            }
        }
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now(); //devuelve un objeto tipo DURATION
    duration<double, milli> duracion = duration_cast<duration<double>>(t2-t1); //milli por milisegundos
    return duracion.count();

}

void reduce(int A[], int ini, int fin, int &pos) { //pasé pos por referencia para saber posición final del pivote
    int izq = ini; //primer elemento
    int der = fin; //último 
    pos = ini; //pivote, iniciamos por el primero
    bool band = true;
    while (band == true) {
        while ((A[pos] <= A[der]) && (pos != der)) { //si A[1] es menor al A[fin] y es != posición
            der = der-1; //vamos buscando hacia la izq 
        }
        if (pos == der) { //si encontramos la misma posición 
            band = false; // salgo del ciclo
        } else { //si no es la misma posición
            int aux = A[pos]; //guardamos A[1] en aux
            A[pos] = A[der]; //ahora A[1] tendrá la info del otro
            A[der] = aux; //guardo info del aux en el otro
            pos = der; //se mueve pivote a der
        }

        while ((A[pos] >= A[izq]) && (pos != izq)) { //si A[1] es mayor al final
            izq = izq+1; //vemos por derecha 
        }
        if (pos == izq) { //si es misma posición (ya encontró su posición final)
            band = false; //cerramos ciclo
        } else { 
            int aux = A[pos]; //guardamos A[1] en aux
            A[pos] = A[izq]; //A[1] tendrá la info del elemento 
            A[izq] = aux; //A[elemento] tendrá la info de aux
            pos = izq; //se mueve pivote a la izq
        }
        }
    }

double quicksort(int A[], int N) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //referencia en readme

    int MAX=1000; //tamaño máximo de las pilas 
    int tope = 0; //índice superior de la pila 
    int pos; //recibe posición final calculada por reduce()
    int pilamenor[MAX]; //debo establecer variables primero
    int pilamayor[MAX];

    pilamenor[tope] = 0; //pilamenor tiene el inicio 
    pilamayor[tope] = N-1; //pilamayor tiene el final
    tope++; //aumenta tope porque hay 1 intervalo por pila

    while (tope > 0) {
        tope--; 
        int ini = pilamenor[tope]; 
        int fin = pilamayor[tope];
        
        if (ini>= fin) continue; //si el inicio es mayor al final, salta a la sgte

        reduce(A, ini, fin, pos); //queda inicializado pos para usar en reduce()

        if (ini<(pos-1)) { //si la parte izq tiene mínimo 2 elementos
            pilamenor[tope] = ini;
            pilamayor[tope] = pos-1;
            tope = tope + 1; 
        }
        if (fin > (pos+1)) { //si la parte der tiene mínimo 2 elementos, apila el subintervalo der 
            pilamenor[tope] = pos+1;
            pilamayor[tope] = fin;
            tope = tope+1;
        }
        
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now(); //devuelve un objeto tipo DURATION
    duration<double, milli> duracion = duration_cast<duration<double>>(t2-t1); //milli por milisegundos
    return duracion.count();

}

void imprimir_elementos(int A[], int N, char VER) {
    for (int i=0; i<N; i++) {
        cout << "a["<<i<<"]="<<A[i]<<" ";
    }
    cout <<"\n";
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Uso: ./lab8 10 s" << endl; //s para sí y cualquier letra para no
        return -1; //error 
    }

    int N = atoi(argv[1]); //paso a entero el total de números a ordenar
    char VER = argv[2][0]; //se lee s o n 
    
    int *A = new int[N]; 
    for (int i = 0; i<N; i++) {
        A[i] = rand() % 5000; //para que no sean números mayores a 5000
    }

    for (int i=0; i<N; i++) { //arreglo antes de los métodos
        cout << " a[" << i << "]=" << A[i];    
    }
    cout << "\n";

    int *bur = new int[N]; //para poder imprimir al final y no después de cada tiempo sus elementos
    int *ins = new int[N]; 
    int *sel = new int[N];
    int *she = new int[N];
    int *qui = new int[N];

    cout << "+------------------------------------+"<< endl;
    cout << "Método                 Tiempo"<<endl;
    cout << "+------------------------------------+"<< endl;

    for (int i = 0; i < N; i++) {
    bur[i] = ins[i] = sel[i] = she[i] = qui[i] = A[i]; //creo copias 
}

    double tiempo_b = burbuja_menor(bur, N);
    cout << "Bubble sort     " << tiempo_b <<" milisegundos" << endl;

    double tiempo_i = insercion(ins, N);
    cout << "Inserción       " << tiempo_i <<" milisegundos" << endl;

    double tiempo_s = seleccion(sel, N);
    cout << "Selección       " << tiempo_s << " milisegundos" << endl;

    double tiempo_ss = shellsort(she, N);
    cout << "Shellsort       " << tiempo_ss <<" milisegundos" << endl;

    double tiempo_q = quicksort(qui, N);
    cout << "Quicksort       " << tiempo_q << " milisegundos" << endl;

    if (VER == 's' || VER == 'S') {
    cout << "+------------------------------------+"<<endl;
    cout << "Burbuja:       "; imprimir_elementos(bur, N, VER); 
    cout << "Inserción:     "; imprimir_elementos(ins, N, VER);
    cout << "Selección:     "; imprimir_elementos(sel, N, VER);
    cout << "Shellsort:     "; imprimir_elementos(she, N, VER);
    cout << "Quicksort:     "; imprimir_elementos(qui, N, VER);
    }

    delete[] A; //elimino por memoria
    delete[] bur;
    delete[] ins;
    delete[] sel;
    delete[] she;
    delete[] qui; 

    return 0;   
}