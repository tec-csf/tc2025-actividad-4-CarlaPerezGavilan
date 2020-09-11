//
//  main.c
//  Actividad 4: Comunicación entre procesos
//
//  Created by Carla Pérez Gavilán on 10/09/2020.
//  Copyright (c) 2020 Carla Pérez Gavilán . All rights reserved.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Estructura de Proceso que guarda promedio y PID */
typedef struct
{
    pid_t pid;
    int promedio;
} Process;

/* Funciones de impresión */
void printTable(Process * proc, int num, int max);
void getHistogram(int times);

int main(int argc, char * const * argv) {

    /* Intializing */
    // nvalue: obtiene string del flag
    char *nvalue = NULL;

    //numc: nvalue cuando se convierte en entero 
    int numc = 0;

    //c: flag que recibe num de hijos
    int c =  0;

    //max: el mayor de los promedios 
    int max = 0;

    //proc: arreglo de número de procesos hijos
    Process * proc;

    //last: último indice de arreglo de procesos hijos
    Process *last;

    //estado: variable para regresar cantidad 
    int estado = 0;

    //pid: variable temporal para guardar id del pid
    pid_t pid;

    //i: index de ciclos 
    int i = 0;

    // productCount: cantidad de procesos que se generaron en realidad 
    int productCount;

    //aux: indice auxiliar para ciclos
    Process *aux;

    /* Obtener argumento de numero de hijos */    
    while ((c = getopt (argc, argv, "n:")) != -1)
        switch (c)
    { 
        case 'n':
            nvalue = optarg;
             if(atoi(nvalue) == 0)
             {
                printf("El argumento no es un entero\n");
                exit(0);
            }else
            {
                printf("El argumento es un entero\n");
                numc = atoi(nvalue);
            }
            break;
        case '?':
            if (optopt == 'n')
                fprintf (stderr, "Opción -n requiere un argumento.\n");
            else if (isprint (optopt))
                fprintf (stderr, "Opción desconocida '-%c'.\n", optopt);
            else
                fprintf (stderr, "Opción desconocida '\\x%x'.\n", optopt);
            return 1;
        default:
            abort ();
    }
    
    printf(" --> Creando %d hijos \n", numc);   
   
    /* Reservando memoria para arreglo */
    proc = malloc(numc*sizeof(Process));
    productCount = numc;
    aux = proc;

    /*Creación de n procesos en un ciclo */
    while(i < numc)
    {
        //Creación de proceso 
        pid = fork();
       
        
        if (pid == -1)
        {
            //Código de error
            printf("Error al crear el proceso hijo \n");
            productCount--;
            break; 
        }
        if (pid == 0)
        {
            //Código de hijos
            int promedio = (getpid() + getppid())/2;
            printf("Soy el proceso hijo con PID = %d y mi promedio es = %d y mi padre tiene PID = %d \n", getpid(), promedio, getppid());
            exit(promedio);
        }else
        {
            //Código de padre 
            sleep(3);
            aux->pid =  pid;
            aux++;
        }
        i++;
    }

    // Último proceso generado 
    last = proc + productCount;

    // Ciclo para esperar procesos hijos
    for(aux = proc; aux < last; aux++)
    {
            if (waitpid(aux->pid, &estado, 0) != -1)
            {
                if (WIFEXITED(estado)) 
                {
                    printf("Ya terminó el hijo con PID %d con promedio = %d \n", aux->pid, WEXITSTATUS(estado));
                    aux->promedio = WEXITSTATUS(estado);
                    if(aux->promedio > max)
                    {
                        max = aux->promedio;
                    }
                }
            }
    }

    //Imprimir tabla 
    printTable(proc, numc, max);

    //Liberar memoria
    free(proc);

    return 0;
    
}

/**
 *  Imprimir tabla
 * @param[out] proc: arreglo de procesos para imprimir tabla
 * @param[out] num: cantidad de procesos creados 
 * @param[out] max: promedio máximo
*/
void printTable(Process * proc, int num, int max)
{
    printf("\n");
    printf("%-20s%-20s%-20s\n", "PID hijo", "Promedio", "Histograma");

    for(Process * aux = proc; aux< proc+num; aux++)
    {
        printf("%-20d%-20d", aux->pid, aux->promedio);
        int hist = 20-(2*(max- aux->promedio)); 
        getHistogram(hist);
    }
    
    printf("\n");
}


/**
 * Imprimir histograma
 *
 * @param[out] times: cantidad de veces que queremos imprimir un asterisco
 */
void getHistogram(int times)
{
    for(int i = 0; i<times; i++)
    {
        printf("*");
    }
    printf("\n");
}