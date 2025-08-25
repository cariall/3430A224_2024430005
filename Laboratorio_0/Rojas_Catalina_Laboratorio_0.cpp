#include <iostream>

int par_o_no(int numero) {
	if (numero%2 == 1) {
		std::cout<<"El número " << numero << " es impar\n";
	} else {
		std::cout<<"El número " << numero << " es par\n";
	}
	return numero;
}

int main() {
	int numero;
	std::cout<<"Ingrese un número: \n";
	std::cin>>numero;
	par_o_no(numero);
	std::cout<<"El número que ingresaste es "<<numero<<"\n";
	return 0;
}

