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
#include <string.h>
#include <sys/wait.h>

typedef struct{
    pid_t pid;
    int promedio;
} Process;

void printTable(Process * proc, int num);
char * getHistogram(int times);
int main(int argc, char * const * argv) {

    char *nvalue = NULL;
    int numc = 0;
    int c;
    Process * proc;
    Process *last;
    int estado;

    opterr = 0;
    
    while ((c = getopt (argc, argv, "n:")) != -1)
        switch (c)
    { 
        case 'n':
            nvalue = optarg;
             if(atoi(nvalue) == 0){
                printf("El argumento no es un entero\n");
                break;
            }else{
                printf("El argumento es un entero\n");
                numc = atoi(nvalue);
            }
            break;
        case '?':
            if (optopt == 'n')
                fprintf (stderr, "Opción -%n requiere un argumento.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Opción desconocida '-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Opción desconocida '\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
    }
    
    printf(" creando %d hijos \n", numc);   
    pid_t pid;
    int i = 0;
    proc = malloc(numc*sizeof(Process));
    int product_count = numc;
    Process *aux = proc;

    while(i<numc){
        printf(" iteración %d \n", i);
        pid = fork();
       

        if (pid == -1)
        {
            printf("Error al crear el proceso hijo \n");
            product_count--;
            break; 
        }
        if (pid == 0)
        {
            printf("soy hijo con pid %d y pid de mi padre es %d \t", getpid(), getppid()); 
            int promedio = (getpid() + getppid())/2;
            printf("el promedio es %d \n", promedio);
            exit(promedio);
        }else{
            aux->pid =  pid;
            aux++;
        }
        printf("\n\n");
        i++;
    }

    for(Process * a = proc; a<proc+product_count; a++){
            if (waitpid(a->pid, &estado, 0) != -1)
            {
                if (WIFEXITED(estado)) {
                    printf("Ya terminó el hijo con PID %d con promedio = %d \n", a->pid, WEXITSTATUS(estado));
                    a->promedio = WEXITSTATUS(estado);
                }
            }
    }
            
    printTable(proc, numc);
    free(proc);
    return 0;
    
}

void printTable(Process * proc, int num){
    printf("\n");
    printf("%-20s%-20s%-20s\n", "PID hijo", "Promedio", "Histograma");
    for(Process * aux = proc; aux< proc+num; aux++){
        printf("%-20d%-20d%-20s\n", aux->pid, aux->promedio, "******"); 
    }
    
    printf("\n");
}
