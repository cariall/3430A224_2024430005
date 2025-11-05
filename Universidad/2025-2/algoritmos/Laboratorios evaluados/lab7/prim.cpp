#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
using namespace std;

#define INF -1

void inicializar_vector_caracter(char *vector, int n);
void inicializar_matriz(int **matriz, int n);
void imprimir_matriz(int **matriz, int n);
int buscar_indice_caracter(char *V, int n, char c);
void aplicar_prim(int **M, char *V, int n, int origen);
void imprimir_grafo(int **matriz, char *vector, int n, const string &nombre_archivo);
void imprimir_mst(int **aristas, int tam, int **M, char *V, const string &nombre_archivo);

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Uso: ./prim n_nodos\n" << endl;
        cout << "Ejemplo: ./prim 3 " << endl;
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
    int idx_origen = buscar_indice_caracter(V, N, origen);

    imprimir_grafo(M, V, N, "grafo_original.txt");
    cout << "\nGrafo original generado: grafo_original.png\n";

    aplicar_prim(M, V, N, idx_origen);

    for (int i = 0; i < N; i++) delete[] M[i];
    delete[] M;
    delete[] V;

    return 0;
}

void inicializar_vector_caracter(char *vector, int n) {
    for (int i = 0; i < n; i++)
        vector[i] = 'a' + i;
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

int buscar_indice_caracter(char *V, int n, char c) {
    for (int i = 0; i < n; i++)
        if (V[i] == c)
            return i;
    return -1;
}

void imprimir_grafo(int **matriz, char *vector, int n, const string &nombre_archivo) {
    ofstream fp(nombre_archivo);
    fp << "graph G {\n";
    fp << "node [style=filled, fillcolor=lightblue];\n";

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matriz[i][j] > 0)
                fp << vector[i] << " -- " << vector[j]
                   << " [label=" << matriz[i][j] << "];\n";
        }
    }
    fp << "}\n";
    fp.close();

    string base = nombre_archivo.substr(0, nombre_archivo.find('.'));
    string comando = "dot -Tpng " + nombre_archivo + " -o " + base + ".png";
    system(comando.c_str());

    string abrir = "eog " + base + ".png &";
    system(abrir.c_str()); // 2do plano
}

void imprimir_mst(int **aristas, int tam, int **M, char *V, const string &nombre_archivo) {
    ofstream fp(nombre_archivo);
    fp << "graph MST {\n";
    fp << "node [style=filled, fillcolor=lightgreen];\n";

    for (int i = 0; i < tam; i++) {
        int u = aristas[i][0];
        int v = aristas[i][1];
        fp << V[u] << " -- " << V[v] << " [label=" << M[u][v]
           << ", color=red, penwidth=2.0];\n";
    }

    fp << "}\n";
    fp.close();

    string base = nombre_archivo.substr(0, nombre_archivo.find('.'));
    string comando = "dot -Tpng " + nombre_archivo + " -o " + base + ".png";
    system(comando.c_str());

    string abrir = "eog " + base + ".png &";
    system(abrir.c_str());
}

void aplicar_prim(int **M, char *V, int n, int origen) {
    int *D = new int[n];
    bool *S = new bool[n];
    int *P = new int[n];
    char *conjunto_L = new char[n];
    int **aristas = new int*[n - 1];
    for (int i = 0; i < n - 1; i++)
        aristas[i] = new int[2];

    int tam_aristas = 0;
    int tam_L = 0;

    for (int i = 0; i < n; i++) {
        D[i] = INT_MAX;
        S[i] = false;
        P[i] = -1;
    }

    D[origen] = 0;

    cout << "\n\n-------- Algoritmo de Prim --------" << endl;

    for (int k = 0; k < n; k++) {
        int menor = INT_MAX;
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!S[i] && D[i] < menor) {
                menor = D[i];
                u = i;
            }
        }

        if (u == -1) break; // si no hay más vértices alcanzables, se corta

        S[u] = true;
        conjunto_L[tam_L++] = V[u];

        if (P[u] != -1 && M[P[u]][u] != INF) { //agrego el válido al mst
            aristas[tam_aristas][0] = P[u];
            aristas[tam_aristas][1] = u;
            tam_aristas++;
        }

        for (int v = 0; v < n; v++) { //actualiza vecinos
            if (M[u][v] != INF && !S[v] && M[u][v] < D[v]) {
                D[v] = M[u][v];
                P[v] = u;
            }
        }

        cout << "\nIteración " << k + 1 << ": L = { ";
        for (int i = 0; i < tam_L; i++) cout << conjunto_L[i] << " ";
        cout << "}\n";
    }

    cout << "\nÁrbol de costo mínimo (Prim):\n";
    int costo_total = 0;
    for (int i = 0; i < tam_aristas; i++) {
        int u = aristas[i][0];
        int v = aristas[i][1];
        cout << V[u] << " -- " << V[v] << " (peso " << M[u][v] << ")\n";
        costo_total += M[u][v];
    }
    cout << "Costo total: " << costo_total << endl;

    imprimir_mst(aristas, tam_aristas, M, V, "grafo_mst.txt");
    cout << "\nGrafo del MST generado: grafo_mst.png\n";

    delete[] D;
    delete[] S;
    delete[] P;
    delete[] conjunto_L;
    for (int i = 0; i < n - 1; i++)
        delete[] aristas[i];
    delete[] aristas;
}
