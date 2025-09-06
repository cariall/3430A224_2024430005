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

float imc_paciente(PACIENTE *paciente) {
	float imc = paciente->peso/(paciente->altura*paciente->altura);
	return imc;
}

void imprimir(PACIENTE *paciente) {
	float imc = imc_paciente(paciente);
        printf("\tNombre: %s. \n\tEdad: %d. \n\tPeso: %f. \n\tAltura: %f. \n\tIMC: %f. \n\t+-------------+\n", paciente->nombre, paciente->edad, paciente->peso, paciente->altura, imc);
	}

void imprimir_dinamico(PACIENTE *head) {
	cout<<"\n\tLista de Pacientes: \n\t+-------------+\n";
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

void promedios(PACIENTE *head, float *prom_peso, float *prom_edad) { 
	if (head == NULL) { //si está vacío
		cout << "Lista vacía\n";
		*prom_peso = 0.0; //retorno cero
		*prom_edad = 0.0;
	}

	PACIENTE *current = head; //current guardará la info de cabeza
	float suma_peso = 0.0;
	float suma_edad = 0.0;
	int contador = 0;
	
	while (current != NULL) { //si current no está vacío
		suma_peso += current->peso; //sumamos suma+current->peso = 0+peso, después peso+otro_peso... etc
		suma_edad += current->edad;
		contador++; //contador para saber cuántas personas son
		current=current->next; //current valdrá el siguiente nodo y si no es nulo, vuelve al ciclo
	}

	*prom_peso = suma_peso/contador;
	*prom_edad = suma_edad/contador;

	printf("\n\t+-------------+\n\tPromedio peso: %f. \n\tPromedio edad: %f. \n\t+-------------+\n\n", *prom_peso, *prom_edad);
}

void menu() {
    cout << "\n+----Menú-----+\n";
	cout << "1. Cargar más pacientes desde csv\n";
    cout << "2. Mostrar todos los pacientes\n";
    cout << "3. Agregar paciente\n";
    cout << "4. Eliminar paciente\n";
    cout << "5. Mostrar promedios\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opción: ";
}

void cargarDesdeArchivo(PACIENTE **head, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r"); //FILE representa un archivo en c y "r" significa lectura. fopen lo abre, necesita de nombre y modo.
    if (!archivo) { //si puntero es nulo, fopen no pudo abrir el archivo
        cout << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    char nombre[20];
    int edad;
    float peso, altura;

    while (fscanf(archivo, "%19[^,],%d,%f,%f\n", nombre, &edad, &peso, &altura) == 4) { //fscanf lee datos desde un archivo y %19[^,] lee como string hasta una coma.
        // % indica formato de d, f, etc. 19=caracteres a leer, []=indica caracteres a leer, ^=negación, ","=indica que lea mientras no haya coma.
		PACIENTE *nuevo = new PACIENTE;
        strcpy(nuevo->nombre, nombre);
        nuevo->edad = edad;
        nuevo->peso = peso;
        nuevo->altura = altura;
        agregar(head, nuevo);
    }

    fclose(archivo); //cierra archivo
    cout << "\nPacientes cargados desde archivo con éxito.\n";
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

	float promedioPeso, promedioEdad;
	int opcion;

	do {
		menu();
		cin>>opcion;
		cin.ignore();

		if (opcion == 1) {
			cargarDesdeArchivo(&head, "pacientes.csv"); //adjunté un csv llamado pacientes.csv, si quisiera agregar otro, por favor cambiar nombre
        } else if (opcion == 2) {
			imprimir_dinamico(head);
		} else if (opcion == 3) {
			PACIENTE *nuevo = new PACIENTE;
			strcpy(nuevo->nombre, "Juan");
            nuevo->edad = 20;
            nuevo->peso = 70.4;
            nuevo->altura = 1.70;
            agregar(&head, nuevo);
            cout << "\nPaciente "<< nuevo->nombre << " agregado con éxito.\n";
		} else if (opcion == 4) {
			eliminar(&head, paciente_3);
			cout << "\nPaciente "<<paciente_3->nombre<<" eliminado con éxito.\n";
		} else if (opcion == 5) {
			promedios(head, &promedioPeso, &promedioEdad);
		}
	}	while (opcion != 6);

	cout << "El programa se ha cerrado\n";
	return 0;
}
