/*
	Derechos de Autor: Diego Vásquez [9989-19-19543]
	Ciudad de Guatemala, agosto de 2024
	Tarea 4 - Sistemas Operativos I
	Simulación de algoritmos de planificación: Round Robin y SJF
	Ingeniería en Sistemas - Universidad Mariano Gálvez de Guatemala
	
*/

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
/* Constante: máximo 50 procesos*/
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


/* Función para la creación de un proceso */
Proceso crearProceso(int pid){
	Proceso proceso_x;
	proceso_x.pid=pid;
	
	printf("Ingrese el quantum del proceso del proceso %i, con tiempo de llegada %i: ", pid, pid-1);
	scanf("%d", &proceso_x.quantum_proceso);
	proceso_x.tiempo_espera=proceso_x.quantum_proceso;
	
	return proceso_x;
}

/* Función para el algoritmo de ROUND ROBIN */
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
					printf("El proceso %i terminó en el tiempo: %i\n", procesos[i].pid, tiempo_general);
				}
			}
		}
	}while(bandera_fin!=1);
}

/* Función principal */
int main(){
	/* Permite leer caracteres del español en la consola */
	setlocale(LC_ALL, "spanish");
	
	printf("Ingrese la cantidad de procesos: ");
	scanf("%i", &cant_procesos);
	
	if(cant_procesos<=max_procesos){
		/* Invocación de la estructura "Proceso" */
		Proceso procesos[cant_procesos];
		
		for(i=0; i<cant_procesos; i++){
			procesos[i]=crearProceso(i+1);
		}
		
		/* Invocación de la función: Round Robin */
		int quantum_rr=0;
		printf("Ingrese el QUANTUM para Round Robin: ");
		scanf("%i", &quantum_rr);
		Round_Robin(procesos, quantum_rr);
		
	}else{
		printf("¡No puede generar más de 50 procesos!");
	}
	getch();
	return 0;
}

