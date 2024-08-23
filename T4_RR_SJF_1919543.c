/*
	Derechos de Autor: Diego V�squez [9989-19-19543]
	Ciudad de Guatemala, agosto de 2024
	Tarea 4 - Sistemas Operativos I
	Simulaci�n de algoritmos de planificaci�n: Round Robin y SJF
	Ingenier�a en Sistemas - Universidad Mariano G�lvez de Guatemala
	
*/

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
/* Constante: m�ximo 50 procesos*/
#define max_procesos 50
/* Variables universales */
int tiempo_general=0;
int cant_procesos=0;
int i=0; //Iterador

/* Estructura del proceso */
typedef struct{
	int pid;
	int quantum_proceso;
	int tiempo_espera;
} Proceso;


/* Funci�n para la creaci�n de un proceso */
Proceso crearProceso(int pid){
	Proceso proceso_x;
	proceso_x.pid=pid;
	
	printf("Ingrese el quantum del proceso del proceso %i, con tiempo de llegada %i: ", pid, pid-1);
	scanf("%d", &proceso_x.quantum_proceso);
	proceso_x.tiempo_espera=proceso_x.quantum_proceso;
	
	return proceso_x;
}

/* Funci�n para el algoritmo de ROUND ROBIN */
void Round_Robin(Proceso procesos[cant_procesos], int quantum){
	int bandera_fin;
	
	do{
		bandera_fin=1;
		for(i=0; i<cant_procesos; i++){
			if(procesos[i].tiempo_espera > 0){
				bandera_fin=0;
				if(procesos[i].tiempo_espera>quantum){
					tiempo_general=tiempo_general+quantum;
					procesos[i].tiempo_espera=procesos[i].tiempo_espera-quantum;
				}else{
					tiempo_general=tiempo_general+procesos[i].tiempo_espera;
					procesos[i].tiempo_espera=0;
					printf("El proceso %i termin� en el tiempo: %i\n", procesos[i].pid, tiempo_general);
				}
			}
		}
	}while(bandera_fin!=1);
}

/* Funci�n principal */
int main(){
	/* Permite leer caracteres del espa�ol en la consola */
	setlocale(LC_ALL, "spanish");
	
	printf("Ingrese la cantidad de procesos: ");
	scanf("%i", &cant_procesos);
	
	if(cant_procesos<=max_procesos){
		/* Invocaci�n de la estructura "Proceso" */
		Proceso procesos[cant_procesos];
		
		for(i=0; i<cant_procesos; i++){
			procesos[i]=crearProceso(i+1);
		}
		
		/* Invocaci�n de la funci�n: Round Robin */
		int quantum_rr=0;
		printf("Ingrese el QUANTUM para Round Robin: ");
		scanf("%i", &quantum_rr);
		Round_Robin(procesos, quantum_rr);
		
	}else{
		printf("�No puede generar m�s de 50 procesos!");
	}
	getch();
	return 0;
}

