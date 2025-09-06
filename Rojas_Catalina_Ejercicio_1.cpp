#include <iostream>
#include <cstring>
using namespace std;

struct PACIENTE {
	char nombre[20];
	int edad;
	float peso;
	float altura;
}
;

void imprimir(PACIENTE paciente) {
        cout<<"Paciente "<<paciente.nombre<< " de edad "<< paciente.edad <<", peso: "<<paciente.peso<<" y altura: "<<paciente.altura<<endl;
}

int main() {
	PACIENTE paciente_1;
	PACIENTE paciente_2;
	PACIENTE paciente_3;

	strcpy(paciente_1.nombre, "Juan"); //usar strcpy para copiar cada carácter del arreglo char  como un objeto entero
	paciente_1.edad = 20;
	paciente_1.peso =  70.4;
	paciente_1.altura = 1.70;
	
	strcpy(paciente_2.nombre, "Maloy"); 
        paciente_2.edad = 36;
        paciente_2.peso =  51,5;
        paciente_2.altura = 1.55;
       
	strcpy(paciente_3.nombre, "Tomás"); 
        paciente_3.edad = 45;
        paciente_3.peso =  89.2;
        paciente_3.altura = 1.60;
	
	PACIENTE pacientes[3] = {paciente_1, paciente_2, paciente_3};
	
	for (int i=0; i<3; i++) {
		PACIENTE paciente_actual = pacientes[i];
		imprimir(paciente_actual);	
       }
	
return 0;
}
