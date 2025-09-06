#include <iostream>
#include <cstring>
#include <cstdio> //para poder imprimir con %d, %s, %f
using namespace std;

struct PACIENTE {
	char nombre[20];
	int edad;
	float peso;
	float altura;
	PACIENTE *next; //guardo dirección del prox nodo, así recorro la lista
};

void imprimir(PACIENTE *paciente) {
        printf("\tNombre: %s. \n\tEdad: %d. \n\tPeso: %f. \n\tAltura: %f. \n\t+-------------+\n\n", paciente->nombre, paciente->edad, paciente->peso, paciente->altura);
	}

void imprimir_dinamico(PACIENTE *head) {
	cout<<"\n Lista de Pacientes: \n";
	PACIENTE *current = head;
	while (current != NULL) {
		imprimir (current);
		current = current->next;
	}
}

void agregar(PACIENTE **head, PACIENTE *nuevo_paciente) { //uso doble puntero porque si no, se copiaría *head = NULL. Es para diferenciar
	nuevo_paciente->next = NULL;
	if (*head == NULL) {
		*head = nuevo_paciente;
	} else {
		PACIENTE *current = *head; //si espacio no está vacío, creamos un current con estructura paciente
		while (current->next != NULL) { //y si el siguiente tampoco está vacío
			current = current->next; //lo recorro hasta llegar a uno vacío
		}
		current->next = nuevo_paciente; //si sgte espacio está vacío, lo establezco como nuevo_paciente
		}
}

void eliminar(PACIENTE **head, PACIENTE *paciente) {
	if (*head == NULL || paciente == NULL) { //si la cabeza está vacía o la info del paciente está vacía
		cout<<"No hay nada que eliminar\n"; //no hay nada que eliminar
	}

	if (*head == paciente) { //si la cabeza tiene la info de paciente
    	*head = paciente->next; //la cabeza tendrá la sgte info de paciente
    	paciente->next = NULL;  //y esa sgte info quedará vacía
	}

	PACIENTE *current = *head; //determino current como variable que guarde espacio head
	while (current->next != NULL && current->next != paciente) { //mientras lo que le sigue no sea nulo o sea del paciente
		current = current->next; //pasaremos dicha info a la actual
	}

	if (current->next == paciente) { //si la info siguiente es de paciente
		current->next = paciente->next; //vamos a establecer que la info siguiente de paciente sea current->next
		paciente->next = NULL; //y esta info será nula
	}

}

int main() {
	PACIENTE *head = NULL; //head guarda un espacio vacío
	PACIENTE *paciente_1 = new PACIENTE; //en espacio de paciente_1 se guarda estructura paciente con ciertos datos
	PACIENTE *paciente_2 = new PACIENTE;
	PACIENTE *paciente_3 = new PACIENTE;

	strcpy(paciente_1->nombre, "Juan"); //usar strcpy para copiar cada carácter del arreglo char  como un objeto entero
	paciente_1->edad = 20;
	paciente_1->peso =  70.4;
	paciente_1->altura = 1.70;
	agregar(&head, paciente_1); //agrego la dirección de head (vacío) y la estructura
	
	strcpy(paciente_2->nombre, "Maloy"); 
        paciente_2->edad = 36;
        paciente_2->peso =  51.5;
        paciente_2->altura = 1.55;
	agregar(&head, paciente_2);        

	strcpy(paciente_3->nombre, "Tomás"); 
        paciente_3->edad = 45;
        paciente_3->peso =  89.2;
        paciente_3->altura = 1.60;
	agregar(&head, paciente_3);

	imprimir_dinamico(head);
	eliminar(&head, paciente_1);
	imprimir_dinamico(head);
	
return 0;
}
