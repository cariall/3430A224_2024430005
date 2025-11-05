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
    if (argc < 2) {
        cout << "Uso: ./dijkstra n_nodos" << endl;
        return -1;
    }

    int N = atoi(argv[1]);
    if (N <= 2) {
        cout << "Error: N debe ser mayor que 2." << endl;
        return -1;
    }

    int **M = new int*[N];
    for (int i = 0; i < N; i++)
        M[i] = new int[N];

    char *V = new char[N];
    inicializar_vector_caracter(V, N);
    inicializar_matriz(M, N);

    cout << "Ingrese la matriz de distancias (" << N << "x" << N << "):\n";
    cout << "(Use -1 si no hay conexión entre nodos)\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> M[i][j];
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
            matriz[i][j] = INF;
}

void imprimir_matriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

void imprimir_vector_entero(int *vector, int n) {
    for (int i = 0; i < n; i++)
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
        if (V[i] == c)
            return i;
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
    int *D = new int[n];
    bool *S = new bool[n]; // visitados

    for (int i = 0; i < n; i++) {
        D[i] = M[origen][i];
        S[i] = false;
    }

    D[origen] = 0;
    S[origen] = true;

    cout << "\n\n-------- Estado inicial --------" << endl;
    imprimir_vector_entero(D, n);
    cout << "--------------------------------\n";

    for (int k = 1; k < n; k++) {
        int menor = INT_MAX;
        int v = -1; 

        for (int i = 0; i < n; i++) { //busco vértice con menor distancia no visitado
            if (!S[i] && D[i] != INF && D[i] < menor) {
                menor = D[i];
                v = i;
            }
        }

        if (v == -1)
            break;

        S[v] = true;

        for (int w = 0; w < n; w++) {
            if (!S[w] && M[v][w] != INF)
                D[w] = calcular_minimo(D[w], D[v], M[v][w]);
        }

        cout << "\nIteración " << k << " (añadido " << V[v] << "): ";
        imprimir_vector_entero(D, n);
    }

    cout << "\nDistancias mínimas desde " << V[origen] << ":\n";
    for (int i = 0; i < n; i++) {
        cout << V[origen] << " -> " << V[i] << " = " << D[i] << endl;
    }

    delete[] D;
    delete[] S;
}


void imprimir_grafo(int **matriz, char *vector, int n) {
    ofstream fp("grafo.txt");
    fp << "digraph G {\n";
    fp << "graph [rankdir=LR];\n";
    fp << "node [style=filled, fillcolor=lightblue];\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matriz[i][j] > 0)
                fp << vector[i] << " -> " << vector[j]
                   << " [label=" << matriz[i][j] << "];\n";
        }
    }

    fp << "}\n";
    fp.close();

    cout << "\nGenerando grafo con Graphviz...\n";
    system("dot -Tpng grafo.txt -o grafo.png");
    system("eog grafo.png &");
}
