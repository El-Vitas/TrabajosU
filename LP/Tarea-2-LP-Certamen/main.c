#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "certamen.h"

/*
Función encargada de leer lo escrito por el usuario mediante la consola.
La lectura se realiza de manera dinamica, independiente del largo.
Finalmente guarda lo leido en una variable que fue pasada por parametro por referencia.

    Parametros:
        respuesta(char**): Variable que contiene la dirección de una cadena, cuando la variable se modifica, se modifica tambien la variable original fuera de la función.

    Retorno:
        void
*/
void lecturaDinamica(char** respuesta){
    *respuesta = '\0';
    int sizeRespuesta = 0;
    bool flag = true;
    while(flag){ //leer respuesta por consola independiente del tamaño 
        *respuesta = (char*)realloc(*respuesta,sizeRespuesta+1);
        int c = getchar();
        if( c == EOF || c == '\n'){
            respuesta[0][sizeRespuesta] = '\0';
            flag = false;
        }else{
            respuesta[0][sizeRespuesta] = (char)c;
            sizeRespuesta++;
        }
    }
}

/*
Función encargada de leer una linea del archivo txt.
La lectura se realiza de manera dinamica, independiente del largo.
Finalmente guarda lo leido en una variable que fue pasada por parametro por referencia.

    Parametros:
        str(char**): Variable que contiene la dirección de una cadena, cuando la variable se modifica, se modifica tambien la variable original fuera de la función.
        archivo(FILE*): Archivo en el que se quiere leer la linea.

    Retorno:
        void
*/
void leerLineaArchivo(FILE* archivo, char** str){
    int cont = 0;
    int largo = 5;
    char c;
    *str = (char*)malloc(largo*sizeof(char));
    while((c = fgetc(archivo))!= EOF && c != '\n'){
        if(c != '\r'){
            if(cont == largo){ // ir ajugastando tamaño arr
                largo+= 32;
                *str = (char*)realloc(*str,largo);
            }
            str[0][cont] = c;
            cont++;
        }
    }
    *str = (char*)realloc(*str,cont+1);
    str[0][cont] = '\0'; //nos aseguramos que el final contenga el caracter nulo
}

/*
Función encargada de leer archivo txt dependiendo de las variables del struct tEnunciadoAlternativa.
La lectura se realiza de manera dinamica mediante la funcion, leerLineaArchivo().
Se guarda cada linea correspondiente dentro las variables de un struct tEnunciadoAlternativa, finalmente se retorna ese struct.

    Parametros:
        archivo(FILE*): Archivo en el que se quiere leer las correspondientes lineas.

    Retorno:
        tSimple(tEnunciadoAlternativa*): Puntero a struct el cuál fue siendo completado mediante la lectura.
*/
tEnunciadoAlternativa* leerAlternativaSimple(FILE* archivo){
    char* str;
    int n;
    tEnunciadoAlternativa* tSimple = malloc(sizeof(tEnunciadoAlternativa));

    leerLineaArchivo(archivo, &str); //enunciado
    strcpy(tSimple->enunciado,str);
    free(str); //se libera la memoria pedida antes mediante leerLineaArchivo

    leerLineaArchivo(archivo,&str);// numero alternativas
    n = atoi(str);
    free(str);

    tSimple->n_alternativas = n;
    tSimple->alternativas = malloc(n*sizeof(char*));
    for(int i = 0; i<n;i++){ //alternativas
        leerLineaArchivo(archivo,&str);
        tSimple->alternativas[i] = str; // ahora tSimple.alternativas[i] apunta a la memoria dinamica, por eso aun no se elimina str
    }

    leerLineaArchivo(archivo,&str);//alternativa correcta
    n = atoi(str);
    tSimple->alternativa_correcta = n;
    free(str);

    return tSimple; 
}

/*
Función encargada de leer archivo txt dependiendo de las variables del struct tEnunciadoAlternativaMultiple.
La lectura se realiza de manera dinamica mediante la funcion, leerLineaArchivo().
Se guarda cada linea correspondiente dentro las variables de un struct tEnunciadoAlternativaMultiple, finalmente se retorna ese struct. 

    Parametros:
        archivo(FILE*): Archivo en el que se quiere leer las correspondientes lineas.

    Retorno:
        tMultiple(tEnunciadoAlternativaMultiple*): Puntero a struct el cuál fue siendo completado mediante la lectura.
*/
tEnunciadoAlternativaMultiple* leerAlternativaMultiple(FILE* archivo){
    char* str;
    int n;
    tEnunciadoAlternativaMultiple* tMultiple = malloc(sizeof(tEnunciadoAlternativaMultiple));

    leerLineaArchivo(archivo, &str); //enunciado
    strcpy(tMultiple->enunciado,str);
    free(str); //se libera la memoria pedida antes mediante leerLineaArchivo

    leerLineaArchivo(archivo,&str);// numero alternativas
    n = atoi(str);
    free(str);

    tMultiple->n_alternativas = n;
    tMultiple->alternativas = malloc(n*sizeof(char*));
    for(int i = 0; i<n;i++){ //alternativas
        leerLineaArchivo(archivo,&str);
        tMultiple->alternativas[i] = str; // ahora tSimple.alternativas[i] apunta a la memoria dinamica, por eso aun no se elimina str
    }

    leerLineaArchivo(archivo,&str);//numero alternativas correctas
    n = atoi(str);
    free(str);

    tMultiple->n_correctas = n;
    int* correcta = malloc(n*sizeof(int));
    for(int i = 0; i<n;i++){ //alternativas correctas
        leerLineaArchivo(archivo,&str);
        correcta[i] = atoi(str);
        free(str);
    }
    tMultiple->alternativa_correcta = correcta;
    return tMultiple; 
}

/*
Función encargada de leer archivo txt dependiendo de las variables del struct tEnunciadoVerdaderoFalso.
La lectura se realiza de manera dinamica mediante la funcion, leerLineaArchivo().
Se guarda cada linea correspondiente dentro las variables de un struct tEnunciadoVerdaderoFalso, finalmente se retorna ese struct. 

    Parametros:
        archivo(FILE*): Archivo en el que se quiere leer las correspondientes lineas.

    Retorno:
        tVF(tEnunciadoVerdaderoFalso*): Puntero a struct el cuál fue siendo completado mediante la lectura.
*/
tEnunciadoVerdaderoFalso* leerVerdaderoFalso(FILE* archivo){
    char* str;
    bool opcion;
    tEnunciadoVerdaderoFalso* tVF = malloc(sizeof(tEnunciadoVerdaderoFalso));

    leerLineaArchivo(archivo, &str); //enunciado
    strcpy(tVF->enunciado,str);
    free(str); //se libera la memoria pedida antes mediante leerLineaArchivo

    leerLineaArchivo(archivo,&str);//alternativa
    switch (*str){ //traspasar respuesta a bool
        case 'v':
        case 'V':
            opcion = true;
            break;
    
        default:
            opcion = false;
            break;
    }
    free(str);
    tVF->respuesta = opcion;

    return tVF; 
}

/*
Función encargada de leer archivo txt dependiendo de las variables del struct tEnunciadoCompletar.
La lectura se realiza de manera dinamica mediante la funcion, leerLineaArchivo().
Se guarda cada linea correspondiente dentro las variables de un struct tEnunciadoCompletar, finalmente se retorna ese struct. 

    Parametros:
        archivo(FILE*): Archivo en el que se quiere leer las correspondientes lineas.

    Retorno:
        tCompletar(tEnunciadoCompletar*): Puntero a struct el cuál fue siendo completado mediante la lectura.
*/
tEnunciadoCompletar* leerCompletar(FILE* archivo){
    char* str;
    int n;
    tEnunciadoCompletar* tCompletar = malloc(sizeof(tEnunciadoCompletar));

    leerLineaArchivo(archivo, &str); //numero de textos
    n = atoi(str);
    free(str); //se libera la memoria pedida antes mediante leerLineaArchivo

    tCompletar->n_textos = n;
    tCompletar->textos = malloc(n*sizeof(char*));
    for(int i = 0; i<n; i++){ // textos
        leerLineaArchivo(archivo, &str);
        tCompletar->textos[i] = str; //tCompletar->textos[i] apunta a la mem dinamica, por eso no se borra str aun
    }

    tCompletar->respuestas = malloc((n-1)*sizeof(char*));
    for (int i = 0; i<n-1; i++){ //respuestas
        leerLineaArchivo(archivo, &str);
        tCompletar->respuestas[i] = str; //tCompletar->respuestas[i] apunta a la mem dinamica, por eso no se borra str aun
    }

    return tCompletar; 
}

/*
Función encargada de clasificar la pregunta dependiendo de su tipo de enunciado mientras se lee un archivo, para luego asignar la pregunta al certamen.
Primero se obtiene un struct dependiendo del tipo de enunciado, con todos los valores. Luego se crea la pregunta y se le asigna al certamen.

    Parametros:
        certamen(tCertamen*): Certamen en el que se asignar la pregunta.
        str(char*): Cadena de texto que contiene el nombre del tipo de enunciado.
        archivo(FILE*): Archivo en el que se quiere leer las correspondientes lineas.
        nPregunta(int): Numero de la pregunta que se quiere guardar.

    Retorno:
        void
*/
void clasificarPregunta(tCertamen* certamen,char* str, FILE* archivo, int nPregunta){
    tPregunta* pregunta;
    if((strcmp(str,"AlternativaSimple")==0)){
        tEnunciadoAlternativa* tEnunciado = leerAlternativaSimple(archivo);
        pregunta = crearPregunta(str,tEnunciado,&revisarAlternativaSimple);
    }

    else if((strcmp(str,"AlternativaMultiple")==0)){
        tEnunciadoAlternativaMultiple* tEnunciado = leerAlternativaMultiple(archivo);
        pregunta = crearPregunta(str,tEnunciado,&revisarAlternativaMultiple);
    }

    else if((strcmp(str,"VerdaderoFalso")==0)){
        tEnunciadoVerdaderoFalso* tEnunciado = leerVerdaderoFalso(archivo);
        pregunta = crearPregunta(str,tEnunciado,&revisarVerdaderoFalso);
    }

    else{ // Enunciado completar
        tEnunciadoCompletar* tEnunciado = leerCompletar(archivo);
        pregunta = crearPregunta(str,tEnunciado,&revisarCompletar);
    }
    asignarPregunta(certamen,nPregunta,pregunta);
}

/*
Función encargada de clasificar la pregunta dependiendo de su tipo de enunciado mientras se responde un certamen.
Dependiendo del tipo del enunciado de la pregunta, se realizará la pregunta de una manera u de otra.

    Parametros:
        certamen(tCertamen*): Certamen en el que se responder la pregunta.
        pos(int): posición de la pregunta dentro del certamen.

    Retorno:
        void
*/
void clasificarResponder(tCertamen* certamen,int pos){
    tPregunta pregunta = leerPregunta(certamen,pos);
    if((strcmp(pregunta.tipo,"AlternativaSimple")==0)){ //formato pregunta para preguntas simples
        tEnunciadoAlternativa* enun= (tEnunciadoAlternativa*)pregunta.enunciado;
        printf("%s\n",enun->enunciado); //mostar enunciado
        printf("Numero de alternativas: %d\n",enun->n_alternativas); //mostrar numero alternativas
        for(int j = 0; j<enun->n_alternativas;j++){ //mostrar alternativas
            printf("%d) %s\n",j+1,enun->alternativas[j]);
        }
        printf("Escriba a continuación su respuesta con el numero de la alternativa:\n");
        char* respuesta;
        lecturaDinamica(&respuesta); 
        asignarRespuestaUsuario(certamen,pos,respuesta); // guarda la respuesta
    }

    else if((strcmp(pregunta.tipo,"AlternativaMultiple")==0)){ //formato pregunta para preguntas Multiples
        tEnunciadoAlternativaMultiple* enun= (tEnunciadoAlternativaMultiple*)pregunta.enunciado;
        printf("%s\n",enun->enunciado); //mostrar enunciado
        printf("Numero de alternativas: %d\n",enun->n_alternativas); //mostar numero alternativas
        for(int j = 0; j<enun->n_alternativas;j++){ //mostrar alternativas
            printf("%d) %s\n",j+1,enun->alternativas[j]);
        }
        int numRespuesta;
        char* resp;
        printf("Ingrese cantidad de alternativas que cree que son correctas(Maximo %d):\n",enun->n_alternativas);
            lecturaDinamica(&resp); 
            numRespuesta = atoi(resp);
            free(resp);
        int* respuesta = malloc(numRespuesta*sizeof(int));

        printf("En cada linea ingrese el numero de la alternativa que cree que es correcta (alternativas distintas):\n");
        for(int i = 0; i<numRespuesta;i++){ //ir guardando el valor entero de las respuestas
            lecturaDinamica(&resp); 
            respuesta[i] = atoi(resp);
            free(resp);
        }
        asignarRespuestaUsuario(certamen,pos,respuesta); // guarda la respuesta
    }

    else if((strcmp(pregunta.tipo,"VerdaderoFalso")==0)){
        tEnunciadoVerdaderoFalso* enun= (tEnunciadoVerdaderoFalso*)pregunta.enunciado;
        printf("%s\n",enun->enunciado); //mostar enunciado
        char* respuesta;
        bool *opcion = malloc(sizeof(bool));
        printf("Escriba a continuacion la respuesta con 'V' o 'F', según corresponda\n");
        lecturaDinamica(&respuesta);
        switch (*respuesta){ //pasa la respuesta a bool
            case 'V':
            case 'v':
                *opcion = true;
                break;
            default:
                *opcion = false;
                break;
        }
        free(respuesta);
        asignarRespuestaUsuario(certamen,pos,opcion); // guarda la respuesta
    }

    else{ // Enunciado completar
        tEnunciadoCompletar* enun= (tEnunciadoCompletar*)certamen->preguntas[pos].enunciado;
        int nTextos = enun->n_textos,i;
        printf("Completa el siguiente texto:\n");
        for(i = 0;i<nTextos;i++){ //textos
            printf("%d) %s\n",i+1,enun->textos[i]);
        }

        printf("Alternativas a ordenar: %d\n",nTextos-1);
        for(i = 0;i<nTextos-1;i++){ //respuestas
            printf("%d) %s\n",i+1,enun->respuestas[i]);
        }
        
        printf("A continuación escriba una PALABRA/FRASE en cada linea, según el orden correspondiente:\n");
        char** respuesta = malloc((nTextos-1)*sizeof(char*));
        for(i = 0; i<nTextos-1;i++){ //respuesta usuario
            lecturaDinamica(&respuesta[i]); 
        }
        asignarRespuestaUsuario(certamen,pos,respuesta); // guarda la respuesta
    }
}

/*
Función encargada de traspasar el achivo texto a un certamen para finalmente retornar el certamen.
    Parametros:
        No posee.

    Retorno:
        certamen(tCertamen*): Certamen en que cada variable fue completada previamente. Contiene al certamen traspasado de txt.
*/
tCertamen* traspasarCertamen(){
    FILE* archivo;
    archivo = fopen("certamen.txt","r");
    if (archivo == NULL){
        printf("Error al abrir el archivo de texto\n");
        exit(1);
    }
    
    int nPreguntas;
    char* str;
    leerLineaArchivo(archivo,&str);
    nPreguntas = atoi(str);
    free(str);

    tCertamen* certamen = crearCertamen(nPreguntas);

    for(int i = 0; i<nPreguntas; i++){ //va leyendo cada pregunta clasificandola segun corresponda
        leerLineaArchivo(archivo, &str);
        clasificarPregunta(certamen,str,archivo,i);
        free(str);
    }
    fclose(archivo);
    
    return certamen;
}

/*
Función encargada de realizar el certamen, llevando a cabo las preguntas al usuario.
    Parametros:
        No posee.

    Retorno:
        certamen(tCertamen*): Certamen en que cada variable fue completada previamente. Contiene al certamen traspasado de txt.
*/
void responderCertamen(tCertamen* certamen){
    int nPreguntas = largoCertamen(*certamen);
    for(int i = 0; i<nPreguntas; i++){
        printf("\nPregunta numero: %d\n",i+1);
        printf("%s\n",certamen->preguntas[i].tipo);
        clasificarResponder(certamen,i);
    }
}

/*
Función principal del programa encargada hacer las llamas necesarias para poder realizar el correcto funcionamiento del programa.
Como primer paso traspasa el certamen de un txt a un tCertamen. Segundo paso, realiza el certamen, haciendo las preguntas al usuario.
Tercer paso indica la calificación y si el usuario reprueba o aprueba el certamen. Finalmente elimina el certamen liberando la memoria.

    Parametros:
        No posee.

    Retorno:
        0(int): indica que el programa finalizó correctamente.
*/
int main() {
    tCertamen* certamen = traspasarCertamen();
    responderCertamen(certamen);
    int resultado = nCorrectasCertamen(*certamen);
    int nPreguntas = largoCertamen(*certamen);
    printf("\n%d respuesta(s) correcta(s) de %d pregunta(s).\n",resultado,nPreguntas);
    if((float)resultado < (nPreguntas*0.55)){
        printf("Reprobaste\n");
    }else{
        printf("Aprobaste\n");
    }
    clearCertamen(certamen);
    return 0;
}