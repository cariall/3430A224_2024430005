#include <iostream>

int par_o_no(int numero) {
	if (numero%2 == 1) {
		std::cout<<"El número " << numero << " es impar\n";
	} else {
		std::cout<<"El número " << numero << " es par\n";
	}
	return numero;
}

void longitud(char texto[]) {
	int contador=0;
	for (int i=0; texto[i] != '\0'; i++) {
	contador++;
}
	std::cout<<"La longitud de "<<texto<<" es de "<<contador<<" caracteres \n";
}

int main() {
	int numero;
	char texto[100];	

	std::cout<<"Ingrese un número: \n";
	std::cin>>numero;
	std::cout<<"Ingrese una palabra: \n";
	std::cin>>texto;

	par_o_no(numero);
	longitud(texto);

	return 0;
}

