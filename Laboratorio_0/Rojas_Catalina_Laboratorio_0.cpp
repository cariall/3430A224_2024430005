#include <iostream>
using namespace std;

int par_o_no(int numero) {
	if (numero%2 == 1) {
		cout<<"El número " << numero << " es impar\n";
	} else {
		cout<<"El número " << numero << " es par\n";
	}
	return numero;
}

void longitud(char texto[]) {
	int contador=0;
	for (int i=0; texto[i] != '\0'; i++) {
	contador++;
}
	cout<<"La longitud de "<<texto<<" es de "<<contador<<" caracteres \n";
}

int main() {
	int numero;
	char texto[100];	
	char texto2[10] = "carozzi";
	cout<<"Ingrese un número: \n";
	cin>>numero;
	cout<<"Ingrese una palabra: \n";
	cin>>texto;

	par_o_no(numero);

	for (int i=1; i<11; i++) {
		par_o_no(i);
	}

	longitud(texto);
	longitud(texto2);
	return 0;
}

