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
Esta función crea una matriz de caracteres a partir de un archivo de texto.

Parametros:
    matriz (char**): Matriz donde se almacenarán los caracteres leídos.
    dimension (int): Dimensión de la matriz.
    dfile (FILE*): Puntero al archivo que se va a leer.
    o (char): Orientación, puede ser 'V' (vertical) u otra letra (horizontal).

Retorno:
    Ninguno.
*/
void crearMatriz(char **matriz, int dimension, FILE *dfile, char o){
    char c;
    int f = 0;

    if(toupper(o) == 'V'){
        for (int i = 0; i < dimension; i++){ 
            c = fgetc(dfile);
            while(c != '\n' && c != EOF){
                matriz[f][i] = c;
                fseek(dfile, 1, SEEK_CUR);
                f++;
                c = fgetc(dfile);
            }
                
            f = 0;
        }
    }else{
        for (int i = 0; i < dimension; i++){ 
            c = fgetc(dfile);
            while(c != '\n' && c != EOF){
                matriz[i][f] = c;
                fseek(dfile, 1, SEEK_CUR);
                f++;
                c = fgetc(dfile);
            }
                
            f = 0;
        }
    }
}

/*
Esta función busca una palabra en una matriz de caracteres.

Parametros:
    palabra (char*): Palabra que se busca en la matriz.
    dimension (int): Dimensión de la matriz.
    matriz (char**): Matriz de caracteres en la que se busca la palabra.

Retorno:
    int: Valor booleano (1 si se encontró la palabra, 0 si no).
*/
int buscarPalabra(char *palabra, int dimension, char **matriz){
    int size =  strlen(palabra);
    int cont = 0;
    for(int i = 0; i<dimension; i++){
        for(int j = 0; j<dimension; j++){
            if(palabra[cont] == matriz[i][j]){
                cont++;
            }else{
                cont=0;
            }

            if(cont == size){
                return true;
            }
        }
    }
    return false;
}

/*
Esta función busca una palabra en una matriz de caracteres basada en la orientación del archivo. Tambien crea una matriz dinamica y la libera

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

    char **matriz = (char **)malloc(dimension * sizeof(char *));
    
    for (int i = 0; i < dimension; i++) {
        matriz[i] = (char *)malloc(dimension * sizeof(char));
    }

    crearMatriz(matriz, dimension, dfile, orientacion[0]);

    bool res = buscarPalabra(palabra, dimension, matriz);

    for (int i = 0; i < dimension; i++) {
        free(matriz[i]);
    }
    free(matriz);

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
