#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> //para los errores. throw_runtime
#include <cstdlib> //graviphz
using namespace std;

string leerCadena(const string &ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        throw runtime_error("Error: No se pudo abrir el archivo: " + ruta);
    }

    string secuenciaCompleta = "";
    string lineaTemp;

    char primerCaracter = file.peek(); //peek mira el 1er caracter

    if (primerCaracter == '>') { //si es >
        getline(file, lineaTemp); // descartamos la primera línea
    }

    while (file >> lineaTemp) { // >> lee ignorando espacios y \n 
        secuenciaCompleta += lineaTemp;
    }

    file.close();
    return secuenciaCompleta;
}

void leerMatrizU(const string &ruta, int U[4][4]) {
    ifstream file(ruta);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo U");
    }

    string encabezado;
    getline(file, encabezado); // ignoro encabezado

    char filaChar; //va por caracter
    for (int i = 0; i < 4; i++) {
        file >> filaChar; 
        for (int j = 0; j < 4; j++) {
            file >> U[i][j];
        }
    }
    file.close();
}

int traduccion(char c) { //se debe traducir a número 
    if (c == 'A') {
        return 0;
    }
    if (c == 'C') {
        return 1;
    }
    if (c == 'G') {
        return 2;
    }
    if (c == 'T') {
        return 3;
    }
    return -1;
}

int obtenerPuntajeU(char c, char d, int U[4][4]) { //obtiene puntaje de similitud U(c,d)
    return U[traduccion(c)][traduccion(d)]; //verificar que traduccion(c) o (d) retorne números válidos (0-3)
}

void generarGraphviz(const string &aliS, const string &aliT, int puntaje) {
    ofstream dot("alineamiento.dot");
    if (!dot.is_open()) {
        cerr << "No se pudo crear el archivo alineamiento.dot" << endl;
        return;
    }

    dot << "digraph G {" << endl; //escribe en el archivo y usa HTML-like Labels
    dot << "  node [shape=plaintext, fontname=\"Courier New, Courier, monospace\"];" << endl;
    dot << "  rankdir=TB;" << endl;
    dot << "  label=\"Alineamiento Optimo (Puntaje máximo: " << puntaje << ")\";" << endl;
    dot << "  labelloc=\"t\";" << endl;

    dot << "  mainNode [label=<" << endl;
    dot << "    <TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"0\" CELLPADDING=\"2\">" << endl;

    int anchoBloque = 50; // cantidad de letras por fila
    size_t len = aliS.length(); //tipo de dato. Bits se adaptan para contar toda la RAM capaz de usar. 32/64

    for (size_t k = 0; k < len; k += anchoBloque) { // nuevas filas para este bloque
        string rowS = "<TR>"; //tableRow, fila horizontal
        string rowMid = "<TR>";
        string rowT = "<TR>";
        string rowVacia = "<TR><TD COLSPAN=\"" + to_string(anchoBloque) + "\" HEIGHT=\"20\"></TD></TR>"; // Espacio entre bloques

        for (size_t i = k; i < k + anchoBloque && i < len; i++) { // celda por celda
            char s = aliS[i];
            char t = aliT[i];
            string colorS = "#FFFFFF";
            string colorT = "#FFFFFF";
            string middleSymbol = "&nbsp;";

            if (s == '-' || t == '-') { //si hay gap, va gris
                if(s == '-') colorS = "#E0E0E0";
                if(t == '-') colorT = "#E0E0E0";
            } else if (s == t) { //si son iguales, los pone verde y una raya
                colorS = "#C6EFCE"; 
                colorT = "#C6EFCE";
                middleSymbol = "<B>|</B>";
            } else {
                colorS = "#FFC7CE"; 
                colorT = "#FFC7CE";
            }

            rowS += "<TD BGCOLOR=\"" + colorS + "\" WIDTH=\"20\" ALIGN=\"CENTER\">" + s + "</TD>"; //TD: celda en la fila
            rowMid += "<TD WIDTH=\"20\" ALIGN=\"CENTER\"><FONT POINT-SIZE=\"10\">" + middleSymbol + "</FONT></TD>";
            rowT += "<TD BGCOLOR=\"" + colorT + "\" WIDTH=\"20\" ALIGN=\"CENTER\">" + t + "</TD>";
        }

        size_t sobran = (k + anchoBloque) - len;
        if (k + anchoBloque > len) {
             for (size_t r = 0; r < sobran; r++) {
                rowS += "<TD BORDER=\"0\"></TD>"; //agrega celdas invisibles para que quede alineado
                rowMid += "<TD BORDER=\"0\"></TD>";
                rowT += "<TD BORDER=\"0\"></TD>";
             }
        }

        rowS += "</TR>"; //cierra las etiquetas en la fila
        rowMid += "</TR>";
        rowT += "</TR>";

        dot << rowS << endl; //cierro dot
        dot << rowMid << endl;
        dot << rowT << endl;
        
        if (k + anchoBloque < len) { //si aún falta, pone fila vacía
            dot << rowVacia << endl; 
        }
    }

    dot << "    </TABLE>" << endl;
    dot << "  >];" << endl;
    dot << "}" << endl;
    dot.close(); 

    cout << "Generando imagen..." << endl;
    int resultado = system("dot -Tpng alineamiento.dot -o alineamiento.png"); 

    if (resultado == 0) {
        cout << "Imagen generada." << endl;
        system("xdg-open alineamiento.png 2>/dev/null &"); 
    } else {
        cout << "Intentando generar en PDF por tamaño..." << endl;
        system("dot -Tpdf alineamiento.dot -o alineamiento.pdf");
        system("xdg-open alineamiento.pdf 2>/dev/null &");
    }
}

void reconstruirAlineamiento(const string &S, const string &T, int **f, int V, int U[4][4]) { //reconstruye alineamiento
    string alineamientoS = ""; //vacío
    string alineamientoT = ""; //vacío
    int i = S.length(); // n
    int j = T.length(); // m
    int puntajeFinal = f[i][j];
    
    while (i > 0 || j > 0) { //i > 0 ó j > 0, no puede ser i=0 && j=0
        
        if (j == 0) { // j=0, primera columna. Entra a j si no hay más que emparejar
            alineamientoS = S[i-1] + alineamientoS; // concateno S[i] al inicio de S
            alineamientoT = '-' + alineamientoT; //concateno - al inicio de T
            i--; //bajo i
        } 
        
        else if (i == 0) { // es la primera fila 
            alineamientoS = '-' + alineamientoS; //concateno - en S
            alineamientoT = T[j-1] + alineamientoT; //concateno T[j] en T
            j--; //bajo J
        }
        
        else { //si no es ni 1ra columna, ni 1ra fila
            int puntajeMatch = f[i-1][j-1] + obtenerPuntajeU(S[i-1], T[j-1], U); //puntaje en diagonal
            int puntajeGapS = f[i-1][j] + V; //puntaje de un gap en t, desde arriba
            int puntajeGapT = f[i][j-1] + V; //puntaje de un gap en s, desde izq

            if (f[i][j] == puntajeGapS) { //si f[i][j] == f[i-1][j]+V (arriba)
                alineamientoS = S[i-1] + alineamientoS; // caracter de S
                alineamientoT = '-' + alineamientoT;    // gap en T
                i--;
            } 

            else if (f[i][j] == puntajeGapT) {  //si f[i][j] == f[i][j-1]+V (izq)
                alineamientoS = '-' + alineamientoS;    // gap en S
                alineamientoT = T[j-1] + alineamientoT; // caracter de T
                j--;
            } 

            else if (f[i][j] == puntajeMatch); { //si es el mismo en diagonal
                alineamientoS = S[i-1] + alineamientoS;
                alineamientoT = T[j-1] + alineamientoT;
                i--;
                j--;
            } 
            
        }
    }
    
    int matches = 0;
    int mismatches = 0;
    int gaps = 0;
    int longitudTotal = alineamientoS.length();

    for (int k = 0; k < longitudTotal; k++) { 
        char s = alineamientoS[k];
        char t = alineamientoT[k];

        if (s == '-' || t == '-') {
            gaps++; //cuenta gaps
        } else if (s == t) {
            matches++; //cuenta matches
        } else {
            mismatches++;
        }
    }
    
    double porcentajeIdentidad = 0.0; //qué tan idénticos son
    if (longitudTotal > 0) {
        porcentajeIdentidad = (double)matches / longitudTotal * 100.0; //hace que matches sea double para que dé %
    }

    cout << "\n========================================" << endl;
    cout << "       ESTADÍSTICAS DEL ALINEAMIENTO      " << endl;
    cout << "========================================" << endl;
    cout << "Longitud total:                  " << longitudTotal << endl;
    cout << "Matches:                         " << matches << endl;
    cout << "Mismatches:                      " << mismatches << endl;
    cout << "Gaps:                            " << gaps << endl;
    cout << "----------------------------------------" << endl;
    cout << "Puntaje final:                   " << puntajeFinal << endl;
    cout << "Identidad:                       " << porcentajeIdentidad << "%" << endl;
    cout << "========================================" << endl;

    generarGraphviz(alineamientoS, alineamientoT, puntajeFinal);   
}

int main(int argc, char* argv[]) {
        string rutaS, rutaT, rutaU;
        int V = 0;
        bool v_set = false; 

        if (argc < 9) {
            cerr << "Uso: " << argv[0] << " -C1 <arch1> -C2 <arch2> -U <matriz> -V <valor_gap>" << endl;
            return 1;
        }

        for (int i = 1; i < argc; i++) {
            string arg = argv[i];
            if (arg == "-C1" && i + 1 < argc) {
                rutaS = argv[++i];
            } else if (arg == "-C2" && i + 1 < argc) {
                rutaT = argv[++i];
            } else if (arg == "-U" && i + 1 < argc) {
                rutaU = argv[++i];
            } else if (arg == "-V" && i + 1 < argc) {
                V = stoi(argv[++i]); // pasar a int
                v_set = true;
            }
    }

        try {
            string S = leerCadena(rutaS);
            string T = leerCadena(rutaT);
            int U[4][4]; // matriz 4x4
            leerMatrizU(rutaU, U); // leer datos
    
            int n =  S.length(); 
            int m = T.length();

            int **f = new int*[n+1]; //[n+1] punteros enteros van hacia f
            for (int i = 0; i <= n; i++) { 
                f[i] = new int[m+1];
            }
    
            f[0][0] = 0; // f(0, 0) = 0 
    
            for (int i = 1; i<=n; i++) { //1ra columna
                f[i][0] = f[i-1][0] + V; 
            }
        
            for (int j = 1; j <= m; j++) { //1ra fila
                f[0][j] = f[0][j-1] + V;
            } 
        
            for (int i = 1; i <= n; i++) { //lleno matriz
                for (int j = 1; j <= m; j++) {
                    int match  = f[i-1][j-1] + obtenerPuntajeU(S[i-1], T[j-1], U); // f(i-1, j-1) + U[S[i]][T[j]]
                    int gapS   = f[i-1][j] + V;  // f(i-1, j) + V 
                    int gapT   = f[i][j-1] + V;  // f(i, j-1) + V 
                    f[i][j] = max(match, max(gapS, gapT)); // max entre todos se ubica en matriz
                }
            }
            
            reconstruirAlineamiento(S, T, f, V, U);
        
            for (int i = 0; i <= n; i++) {
                delete[] f[i]; //libero memoria para que no vaya a fallar
            }
            delete[] f;
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
            return 1;
        }

        return 0; 

    }
