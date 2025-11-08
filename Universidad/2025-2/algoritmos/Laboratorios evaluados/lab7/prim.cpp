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
<<<<<<< HEAD
    if (argc < 2) {
=======
    if (argc < 2) { //si hay sólo 1, pedimos que reescriban
>>>>>>> a7a1b7f (Actualización código)
        cout << "Uso: ./prim n_nodos\n" << endl;
        cout << "Ejemplo: ./prim 3 " << endl;
        return -1;
    }

<<<<<<< HEAD
    int N = atoi(argv[1]);
    if (N <= 2) {
=======
    int N = atoi(argv[1]); //transformamos a entero el argumento
    if (N <= 2) { //si es igual o menor a 2, error
>>>>>>> a7a1b7f (Actualización código)
        cout << "Error: N debe ser mayor que 2." << endl;
        return -1;
    }

<<<<<<< HEAD
    int **M = new int*[N];
    for (int i = 0; i < N; i++)
        M[i] = new int[N];

    char *V = new char[N];
=======
    int **M = new int*[N]; //cremos un entero con [n] punteros a int. M->[*][*][*]
    for (int i = 0; i < N; i++) //de cero a número de nodos, se aumenta i
        M[i] = new int[N]; //a cada posición de M se le reserva para n enteros

    char *V = new char[N]; //creo un vector con n posiciones
>>>>>>> a7a1b7f (Actualización código)
    inicializar_vector_caracter(V, N);
    inicializar_matriz(M, N);

    cout << "Ingrese la matriz de distancias (" << N << "x" << N << "):\n";
    cout << "(Use -1 si no hay conexión entre nodos)\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
<<<<<<< HEAD
            cin >> M[i][j];
=======
            cin >> M[i][j]; //en cada lugar de la matriz agrego lo que se ingrese
>>>>>>> a7a1b7f (Actualización código)
        }
    }

    cout << "\nMatriz ingresada:\n";
    imprimir_matriz(M, N);

    cout << "\nIngrese el vértice origen (a-" << char('a' + N - 1) << "): ";
    char origen;
    cin >> origen;
    int idx_origen = buscar_indice_caracter(V, N, origen);

<<<<<<< HEAD
    imprimir_grafo(M, V, N, "grafo_original.txt");
=======
    imprimir_grafo(M, V, N, "grafo_original.txt"); //genero grafo antes de aplicar prim
>>>>>>> a7a1b7f (Actualización código)
    cout << "\nGrafo original generado: grafo_original.png\n";

    aplicar_prim(M, V, N, idx_origen);

<<<<<<< HEAD
    for (int i = 0; i < N; i++) delete[] M[i];
=======
    for (int i = 0; i < N; i++) delete[] M[i]; //libera memoria
>>>>>>> a7a1b7f (Actualización código)
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
<<<<<<< HEAD
            matriz[i][j] = INF;
=======
            matriz[i][j] = INF; //toda la matriz con -1 solo para inicializar
>>>>>>> a7a1b7f (Actualización código)
}

void imprimir_matriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
<<<<<<< HEAD
            cout << matriz[i][j] << "\t";
=======
            cout << matriz[i][j] << "\t"; //imprimo toda la matriz
>>>>>>> a7a1b7f (Actualización código)
        }
        cout << endl;
    }
}

int buscar_indice_caracter(char *V, int n, char c) {
    for (int i = 0; i < n; i++)
<<<<<<< HEAD
        if (V[i] == c)
            return i;
=======
        if (V[i] == c) //si vector en posición i coincide con origen
            return i; //retornamos posición
>>>>>>> a7a1b7f (Actualización código)
    return -1;
}

void imprimir_grafo(int **matriz, char *vector, int n, const string &nombre_archivo) {
<<<<<<< HEAD
    ofstream fp(nombre_archivo);
    fp << "graph G {\n";
    fp << "node [style=filled, fillcolor=lightblue];\n";

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matriz[i][j] > 0)
=======
    ofstream fp(nombre_archivo); //creamos
    fp << "graph G {\n";//encabezado
    fp << "node [style=filled, fillcolor=lightblue];\n"; //estilo

    for (int i = 0; i < n; i++) { //recorre matriz de adyacencia
        for (int j = i + 1; j < n; j++) {
            if (matriz[i][j] > 0) //si hay conexión, imprimo
>>>>>>> a7a1b7f (Actualización código)
                fp << vector[i] << " -- " << vector[j]
                   << " [label=" << matriz[i][j] << "];\n";
        }
    }
    fp << "}\n";
    fp.close();

<<<<<<< HEAD
    string base = nombre_archivo.substr(0, nombre_archivo.find('.'));
    string comando = "dot -Tpng " + nombre_archivo + " -o " + base + ".png";
    system(comando.c_str());

    string abrir = "eog " + base + ".png &";
=======
    string base = nombre_archivo.substr(0, nombre_archivo.find('.')); //nombre del archivo y busca hasta el primer punto
    string comando = "dot -Tpng " + nombre_archivo + " -o " + base + ".png";
    system(comando.c_str()); //ejecuta en terminal

    string abrir = "eog " + base + ".png &"; 
>>>>>>> a7a1b7f (Actualización código)
    system(abrir.c_str()); // 2do plano
}

void imprimir_mst(int **aristas, int tam, int **M, char *V, const string &nombre_archivo) {
<<<<<<< HEAD
    ofstream fp(nombre_archivo);
    fp << "graph MST {\n";
    fp << "node [style=filled, fillcolor=lightgreen];\n";

    for (int i = 0; i < tam; i++) {
=======
    ofstream fp(nombre_archivo); //crea
    fp << "graph MST {\n"; //encabezado
    fp << "node [style=filled, fillcolor=lightgreen];\n"; //estilos

    for (int i = 0; i < tam; i++) { 
>>>>>>> a7a1b7f (Actualización código)
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
<<<<<<< HEAD
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
=======
    int *D = new int[n]; //a todos estos se conectan [n] punteros a int
    bool *S = new bool[n];
    int *P = new int[n]; 
    char *conjunto_L = new char[n]; //guarda vértices del conjunto ya conectados
    int **aristas = new int*[n - 1]; //guarda aristas del árbol MST
    for (int i = 0; i < n - 1; i++) //de 0 a n-1
        aristas[i] = new int[2]; //se van 

    int tam_aristas = 0; //aristas hasta ahora
    int tam_L = 0; //tamaño actual de L

    for (int i = 0; i < n; i++) {
        D[i] = INT_MAX; //distancia máxima
        S[i] = false; //no visitado
        P[i] = -1; //ningún vértice con padre
    }

    D[origen] = 0; //donde arranca el árbol

    cout << "\n\n-------- Algoritmo de Prim --------" << endl;

    for (int k = 0; k < n; k++) { 
        int menor = INT_MAX; //número muy alto
        int u = -1; 
        for (int i = 0; i < n; i++) {
            if (!S[i] && D[i] < menor) { //si no ha sido visitado y distancia es menor
                menor = D[i]; //ese será la nueva distancia más corta
                u = i; //u guarda el índice
>>>>>>> a7a1b7f (Actualización código)
            }
        }

        if (u == -1) break; // si no hay más vértices alcanzables, se corta

<<<<<<< HEAD
        S[u] = true;
        conjunto_L[tam_L++] = V[u];

        if (P[u] != -1 && M[P[u]][u] != INF) { //agrego el válido al mst
            aristas[tam_aristas][0] = P[u];
            aristas[tam_aristas][1] = u;
=======
        S[u] = true; //ahora u está dentro del MST
        conjunto_L[tam_L++] = V[u]; //guarda los vértices del conjunto L

        if (P[u] != -1 && M[P[u]][u] != INF) { //agrego el válido al mst
            aristas[tam_aristas][0] = P[u];
            aristas[tam_aristas][1] = u; 
>>>>>>> a7a1b7f (Actualización código)
            tam_aristas++;
        }

        for (int v = 0; v < n; v++) { //actualiza vecinos
<<<<<<< HEAD
            if (M[u][v] != INF && !S[v] && M[u][v] < D[v]) {
                D[v] = M[u][v];
                P[v] = u;
=======
            if (M[u][v] != INF && !S[v] && M[u][v] < D[v]) { //si se conectan y es menor a D[v]
                D[v] = M[u][v]; //ahora D[v] será el valor de M[u][v]
                P[v] = u; //y P[v] guarda u
>>>>>>> a7a1b7f (Actualización código)
            }
        }

        cout << "\nIteración " << k + 1 << ": L = { ";
        for (int i = 0; i < tam_L; i++) cout << conjunto_L[i] << " ";
        cout << "}\n";
    }

    cout << "\nÁrbol de costo mínimo (Prim):\n";
    int costo_total = 0;
<<<<<<< HEAD
    for (int i = 0; i < tam_aristas; i++) {
        int u = aristas[i][0];
=======
    for (int i = 0; i < tam_aristas; i++) { //de 0 a aristas
        int u = aristas[i][0]; 
>>>>>>> a7a1b7f (Actualización código)
        int v = aristas[i][1];
        cout << V[u] << " -- " << V[v] << " (peso " << M[u][v] << ")\n";
        costo_total += M[u][v];
    }
    cout << "Costo total: " << costo_total << endl;

    imprimir_mst(aristas, tam_aristas, M, V, "grafo_mst.txt");
    cout << "\nGrafo del MST generado: grafo_mst.png\n";

<<<<<<< HEAD
    delete[] D;
=======
    delete[] D; //libera memoria
>>>>>>> a7a1b7f (Actualización código)
    delete[] S;
    delete[] P;
    delete[] conjunto_L;
    for (int i = 0; i < n - 1; i++)
        delete[] aristas[i];
    delete[] aristas;
}
