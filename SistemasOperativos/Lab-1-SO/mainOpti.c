#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <stdbool.h>
#include <ctype.h>

/*
Esta función lee un archivo de texto y obtiene los datos de orientación, dimensión y tamaño de archivo.

Parametros:
    orientacion (char*): dirección de memoria donde se almacenará la orientación leída.
    dimension (int*): dirección de memoria donde se almacenará la dimensión leída.
    dim_file (char*): dirección de memoria donde se almacenará el tamaño de archivo leído.
    dfile (FILE*): puntero al archivo que se va a leer.
*/
void getData(char *orientacion, int *dimension, char *dim_file, FILE *dfile){
    fseek(dfile, 0L, SEEK_END);
    *dimension = ftell(dfile);           
    fseek(dfile, 0L, SEEK_SET);

    fgets(orientacion, 12*sizeof(char), dfile);
    orientacion[strcspn(orientacion, "\r\n")] = 0;

    if(*dimension > 80000){
        *dimension = 200;
        strcpy(dim_file, "200x200");
    }else if(*dimension > 20000){
        *dimension = 100;
        strcpy(dim_file, "100x100");
    }else{
        *dimension = 50;
        strcpy(dim_file, "50x50");
    }
}

/*
Esta función busca una palabra en sentido vertical en un archivo de texto.

Parametros:
    palabra (char*): Palabra que se busca en el archivo.
    dimension (int): Dimensión de la matriz (considerando solo las letras).
    dfile (FILE*): Puntero al archivo que se va a leer.

Retorno:
    int: Valor booleano (1 si se encontró la palabra, 0 si no).
*/
int buscarVertical(char *palabra, int dimension, FILE *dfile){
    int size =  strlen(palabra);

    for (int i = 0; i < dimension; i++){ 
        fseek(dfile, 2*i + 10, SEEK_SET);
        char c = fgetc(dfile);
        int cont = 0;
        while(c != '\n' && c != EOF){
            if(palabra[cont] == c){
                cont++;
            }else{
                cont=0;
            }

            if(cont == size){
                return true;
            }
            fseek(dfile, dimension*2, SEEK_CUR);
            c = fgetc(dfile);
        }
    }

    return false;
}

/*
Esta función busca una palabra en sentido horizontal en un archivo de texto.

Parametros:
    palabra (char*): Palabra que se busca en el archivo.
    dimension (int): Dimensión de la matriz (considerando solo las letras).
    dfile (FILE*): Puntero al archivo que se va a leer.

Retorno:
    int: Valor booleano (1 si se encontró la palabra, 0 si no).
*/
int buscarHorizontal(char *palabra, int dimension, FILE *dfile){
    int size =  strlen(palabra);

    for (int i = 0; i < dimension; i++){ 
        char c = fgetc(dfile);
        int cont = 0;
        while(c != '\n' && c != EOF){
            if(palabra[cont] == c){
                cont++;
            }else{
                cont=0;
            }

            if(cont == size){
                return true;
            }
            fseek(dfile, 1, SEEK_CUR);
            c = fgetc(dfile);
        }
    }

    return false;
}

/*
Esta función busca una palabra en una matriz de caracteres basada en la orientación del archivo.

Parametros:
    p (char*): Palabra que se busca en la matriz.
    orientacion (char*): Orientación del archivo (puede ser "H" para horizontal o "V" para vertical).
    dimension (int): Dimensión de la matriz.
    dfile (FILE*): Puntero al archivo que se va a leer.

Retorno:
    int: Valor booleano (1 si se encontró la palabra, 0 si no).
*/
int palabraEncontrada(char *p, char *orientacion, int dimension,FILE *dfile){
    char *palabra = (char*)malloc(strlen(p)* sizeof(char));
    strcpy(palabra, p);

    int i = 0;
    while (palabra[i]) {
        palabra[i] = toupper(palabra[i]);
        i++;
    }
    bool res;

    if(toupper(*orientacion) == 'V'){
        res = buscarVertical(palabra, dimension, dfile);
    }else{
        res = buscarHorizontal(palabra, dimension, dfile);
    }
    return res;
}

/*
Esta función principal realiza la búsqueda de palabras en archivos y realiza acciones según el resultado.

Parametros:
    Ninguno.

Retorno:
    int: Valor que indica si el programa se ejecutó correctamente (0 en este caso).
*/
int main(void){
    DIR *d;
    struct dirent *dir;
    d = opendir("./archivos");
    if (d){
        while ((dir = readdir(d)) != NULL){
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                strtok(dir->d_name, ".");
                FILE *dfile;

                char *direccion = (char*)malloc((strlen(dir->d_name) + 10)* sizeof(char));
                sprintf(direccion, "archivos/%s.txt", dir->d_name);

                dfile = fopen(direccion, "r");

                if(dfile == NULL){
                    printf("Error al abrir el archivo");   
                    exit(1);             
                }

                int dimension;
                char dim_file[10];
                char orientacion[15];

                getData(orientacion, &dimension, dim_file, dfile);

                clock_t start_t, end_t;
                start_t = clock();
                int busqueda = palabraEncontrada(dir->d_name, orientacion, dimension,dfile);
                end_t = clock();

                printf("tiempo de busqueda de %s (%s %s) = %f\n", dir->d_name, orientacion, dim_file, (double)(end_t-start_t)/CLOCKS_PER_SEC);

                if(busqueda){
                    char *cwd_dir = (char*)malloc((strlen(dir->d_name) + 25)* sizeof(char));
                    sprintf(cwd_dir, "CWD/%s/%s/%s.txt", orientacion, dim_file, dir->d_name);
                    FILE *cwd_file;
                    cwd_file = fopen(cwd_dir, "a");
                    fclose(cwd_file);
                    rename(direccion, cwd_dir);
                }

                fclose(dfile);
            }
        }
        
        closedir(d);
    }
}
