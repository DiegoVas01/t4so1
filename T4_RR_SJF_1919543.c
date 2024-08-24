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
#include<conio.h>
/* Constante: m�ximo 50 procesos*/
#define max_procesos 50
/* Variables universales */
int tiempo_general=0;
int cant_procesos=0;
int i=0, j=0; //Iteradores

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
	printf("Iniciando simulaci�n de Round Robin\n");
	do{
		bandera_fin=1;
		for(i=0; i<cant_procesos; i++){
			if(procesos[i].tiempo_espera > 0){
				bandera_fin=0;
				if(procesos[i].tiempo_espera>quantum){
					tiempo_general=tiempo_general+quantum;
					procesos[i].tiempo_espera=procesos[i].tiempo_espera-quantum;
					printf("El proceso: %i con tiempo: %i, va por el tiempo: %i y lleva tiempo de espera: %i\n", procesos[i].pid, procesos[i].quantum_proceso, tiempo_general, procesos[i].tiempo_espera);
					sleep(quantum);
				}else{
					tiempo_general=tiempo_general+procesos[i].tiempo_espera;
					procesos[i].tiempo_espera=0;
					printf("El proceso %i termin� en el tiempo: %i\n", procesos[i].pid, tiempo_general);
				}
			}
		}
	}while(bandera_fin!=1);
}

/* Funci�n para el algoritmo SJF-Shortest Job First */
void SJF(Proceso procesos[cant_procesos]){
	printf("\nIniciando algoritmo SJF\n");
	/* Ordenamiento de burbuja */
	for (i=0; i<cant_procesos-1; i++) {
        for (j=0; j<cant_procesos-1; j++) {
            if (procesos[j].quantum_proceso > procesos[j+1].quantum_proceso) {
                /* Se genera una estructura auxiliar */
				Proceso proceso_auxiliar = procesos[j];
                procesos[j]=procesos[j+1];
                procesos[j+1]=proceso_auxiliar;
            }
        }
    }
    
    for(i=0; i<cant_procesos; i++){
    	tiempo_general=tiempo_general+procesos[i].quantum_proceso;
    	printf("El proceso %i, fue completado al tiempo: %i\n", procesos[i].pid, tiempo_general);
	}
	
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
		
		/* Invocaci�n del algoritmo: Round Robin */
		int quantum_rr=0;
		printf("Ingrese el QUANTUM para Round Robin: ");
		scanf("%i", &quantum_rr);
		Round_Robin(procesos, quantum_rr);
		
		/* Invocaci�n del algoritmo: SJF */
		tiempo_general=0;
		SJF(procesos);
		
	}else{
		printf("�No puede generar m�s de 50 procesos!");
	}
	getch();
	return 0;
}
