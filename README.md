# Tarea 4 
## Autor
Carla Pérez Gavilán Del Castillo- A01023033-CSF
## Instrucciones

Implemente un programa en C que realice lo siguiente:

- Recibe como argumento en la línea de comandos el número de procesos hijos a crear (opción -n). El programa debe validar que el valor especificado sea un número entero. 
- Sugerencia: revise la función atoi (Enlaces a un sitio externo.).
- Crea los n procesos hijos siempre y cuando no existan errores. Si al crear un proceso hijo se genera un error, entonces debe mostrar un mensaje indicando el número de procesos hijos creados hasta ese momento y no debe intentar crear más procesos hijos.
- Espera a que terminen todos los procesos hijos en el mismo orden en que se crearon.
- A medida que los procesos hijos van terminando, debe ir guardando el valor de retorno de cada proceso hijo.
- Una vez que terminen todos los procesos hijos, el proceso padre debe mostrar una tabla en el siguiente formato:

```
PID Hijo	Promedio	Histograma
20	20	********************
10	15	**************
50	35	*****************************
60	40	**************************************
```

Sugerencia: Para determinar la cantidad de * a imprimir, defina una relación respecto al promedio máximo obtenido. Por ejemplo, si el promedio máximo obtenido es 1000, entonces divida los promedios entre 100. De esta manera, para el promedio máximo imprimirá 10 * y todos los demás estarán acotados por debajo de este máximo.

Por su parte, cada proceso hijo debe:

- Calcular el promedio entre su PID y el PID de su padre.
- Imprimir un mensaje que diga: "Soy el proceso hijo con PID = $pid y mi promedio es = $promedio".
    - $pid debe sustituirse por el valor del PID del proceso hijo.
    - $promedio debe sustituirse por el resultado de calcular el promedio entre el PID del proceso hijo y el PID del proceso padre.
- Al terminar, debe regresar el promedio calculado como valor de retorno  al proceso padre.

## Solución 
 ### Cálculo del histograma
 Se utilizó la relación 20-max-(max-x), donde **max** es el promedio máximo y **x** es el promedio de ese hijo. Por lo tanto, 20 será el tamaño del histograma más grande. 

## Referencias

[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=3104960&assignment_repo_type=AssignmentRepo)
