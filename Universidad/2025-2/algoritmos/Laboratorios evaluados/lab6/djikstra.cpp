#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
using namespace std;

#define INF -1

void inicializar_vector_caracter(char *vector, int n);
void inicializar_vector_entero(int *vector, int n);
void inicializar_matriz(int **matriz, int n);
void imprimir_matriz(int **matriz, int n);
void imprimir_vector_entero(int *vector, int n);
void imprimir_vector_caracter(char *vector, int n, const string &nombre);
int buscar_indice_caracter(char *V, int n, char c);
void aplicar_dijkstra(int **M, char *V, int n, int origen);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_grafo(int **matriz, char *vector, int n);

int main(int argc, char **argv) {
    if (argc < 2) { //si no tiene argumentos
        cout << "Uso: ./dijkstra n_nodos" << endl;
        return -1;
    }

    int N = atoi(argv[1]); //transformamos lo que ingresó el usuario en número
    if (N <= 2) { //si es dos o menor, error
        cout << "Error: N debe ser mayor que 2." << endl;
        return -1;
    }

    int **M = new int*[N]; //creamos un entero con [N] punteros a int. M -> [*] [*] [*] N punteros
    for (int i = 0; i < N; i++) //desde 0 al número de nodos, se aumenta i
        M[i] = new int[N]; //y a cada posición de M le reservamos para n enteros

    char *V = new char[N]; //creo un vector con n posiciones
    inicializar_vector_caracter(V, N);
    inicializar_matriz(M, N);

    cout << "Ingrese la matriz de distancias (" << N << "x" << N << "):\n";
    cout << "(Use -1 si no hay conexión entre nodos)\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> M[i][j]; //ahora en cada posición de la matriz, agregamos lo que ingresen
        }
    }

    cout << "\nMatriz ingresada:\n";
    imprimir_matriz(M, N); 

    cout << "\nIngrese el vértice origen (a-" << char('a' + N - 1) << "): ";
    char origen;
    cin >> origen;

    aplicar_dijkstra(M, V, N, buscar_indice_caracter(V, N, origen));

    imprimir_grafo(M, V, N);

    for (int i = 0; i < N; i++) delete[] M[i]; //libera memoria
    delete[] M;
    delete[] V;

    return 0;
}

void inicializar_vector_caracter(char *vector, int n) {
    for (int i = 0; i < n; i++)
        vector[i] = 'a' + i; 
}

void inicializar_vector_entero(int *vector, int n) {
    for (int i = 0; i < n; i++)
        vector[i] = INF;
}

void inicializar_matriz(int **matriz, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz[i][j] = INF; //toda la matriz tendrá -1
}

void imprimir_matriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << "\t"; //se imprime toda la matriz
        }
        cout << endl;
    }
}

void imprimir_vector_entero(int *vector, int n) {
    for (int i = 0; i < n; i++) //se imprime vector como D[0]=1 (ejemplo)
        cout << "D[" << i << "]=" << vector[i] << " ";
    cout << endl;
}

void imprimir_vector_caracter(char *vector, int n, const string &nombre) {
    for (int i = 0; i < n; i++)
        cout << nombre << "[" << i << "]=" << vector[i] << " ";
    cout << endl;
}

int buscar_indice_caracter(char *V, int n, char c) {
    for (int i = 0; i < n; i++)
        if (V[i] == c) //si el vector en posición i tiene el mismo de origen
            return i; //retornamos ese índice
    return -1;
}

int calcular_minimo(int dw, int dv, int mvw) {
    if (mvw == INF || dv == INF)
        return dw;
    if (dw == INF)
        return dv + mvw;
    return (dw <= dv + mvw) ? dw : dv + mvw;
}

void aplicar_dijkstra(int **M, char *V, int n, int origen) {
    int *D = new int[n]; //vector con n posiciones
    bool *S = new bool[n]; // visitados

    for (int i = 0; i < n; i++) { //va creando matriz de distancias
        D[i] = M[origen][i]; //D[0] = M[origen que encontramos][0] -> D[1] = M[origen][1] -> D[2] = M[origen][2]
        S[i] = false; //cada uno no ha sido visitado aún
    }

    D[origen] = 0; //distancia del nodo a sí mismo es 0
    S[origen] = true; //lo marca como visitado

    cout << "\n\n-------- Estado inicial --------" << endl;
    imprimir_vector_entero(D, n);
    cout << "--------------------------------\n";

    for (int k = 1; k < n; k++) { 
        int menor = INT_MAX; //máximo número posible. Es sólo para establecer un número.
        int v = -1; //guarda el índice del vértice con menor distancia sin visitar

        for (int i = 0; i < n; i++) { //busco vértice con menor distancia no visitado
            if (!S[i] && D[i] != INF && D[i] < menor) { //si el nodo no es visitado y D[i] tiene conexión y D[i] es menor a la distancia más pequeña encontrada
                menor = D[i]; //ahora la distancia menor va a ser D[i]
                v = i; //y v guarda el índice de menor distancia
            }
        }

        if (v == -1) //si no hay vértices alcanzables
            break;

        S[v] = true; //lo marcamos como visitado

        for (int w = 0; w < n; w++) { //recorre de 0 a n
            if (!S[w] && M[v][w] != INF) //si nodo no ha sido visitado y hay conexión de v a w
                D[w] = calcular_minimo(D[w], D[v], M[v][w]); //D[w] queda con el mínimo
        }

        cout << "\nIteración " << k << " (añadido " << V[v] << "): "; //imprime iteración y vértice agregado
        imprimir_vector_entero(D, n);
    }

    cout << "\nDistancias mínimas desde " << V[origen] << ":\n";
    for (int i = 0; i < n; i++) {
        cout << V[origen] << " -> " << V[i] << " = " << D[i] << endl;
    }

    delete[] D; //libera memoria
    delete[] S;
}


void imprimir_grafo(int **matriz, char *vector, int n) {
    ofstream fp("grafo.txt"); //lo crea
    fp << "digraph G {\n"; //encabezado
    fp << "graph [rankdir=LR];\n"; //grafo de left a right
    fp << "node [style=filled, fillcolor=lightblue];\n"; //estilos

    for (int i = 0; i < n; i++) { //recorre matriz de adyacencia
        for (int j = 0; j < n; j++) {
            if (i != j && matriz[i][j] > 0) //si ambos son != y tienen conexión
                fp << vector[i] << " -> " << vector[j] //se escriben
                   << " [label=" << matriz[i][j] << "];\n"; //label para que dibuje una flecha con etiqueta de dicha posición en matriz
        }
    }

    fp << "}\n";
    fp.close();

    cout << "\nGenerando grafo con Graphviz...\n";
    system("dot -Tpng grafo.txt -o grafo.png");
    system("eog grafo.png &");
}
