#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "certamen.h"

/*
Función encargada de crear el certamen con un numero de preguntas.

    Parametros:
        n_preguntas(int): cantidad de preguntas del certamen.
    Retorno:
        certamen(tCertamen*): retorna el certamen ya creado con un numero de preguntas.
*/
tCertamen* crearCertamen(int n_preguntas){
    tCertamen* certamen = malloc(sizeof(tCertamen));
    certamen->n_preguntas = n_preguntas;
    certamen->preguntas = malloc(n_preguntas*sizeof(tPregunta));
    return certamen;
}

/*
Función encargada de crear una pregunta mediante las variables recibidas por parametros y la funcion revisar pasada por parametro.

    Parametros:
        tipo(char*): tipo del enunciado de la pregunta.
        enunciado(void*): Puntero generico a cualquier tipo de enunciado.
        respuesta(void*): Puntero generico a cualquier tipo de respuesta entregada por el usuario.
        (*revisar)(void*, void*)(bool): Puntero a una función que indica la forma de revisar la pregunta.
    Retorno:
        pregunta(tPregunta*): retorna la pregunta ya creada por los parametros pasados anteriormente.
*/
tPregunta* crearPregunta(char* tipo, void* enunciado, bool (*revisar)(void*, void*)){
    tPregunta* pregunta = malloc(sizeof(tPregunta));
    pregunta->enunciado = enunciado;
    strcpy(pregunta->tipo,tipo);
    pregunta->revisar = revisar;
    return pregunta;
}

/*
Función que asigna una pregunta al certamen.

    Parametros:
        certamen(tCertamen): certamen que contiene las preguntas a las que se le quiere asignar la respuesta del usuario.
        n_Pregunta(int): Numero de la pregunta a la que se le quiere asignar la respuesta.
        respuesta(void*): Puntero generico a cualquier tipo de respuesta entregada por el usuario.
    Retorno:
        correctas(int): Numero de preguntas correctas del usuario al realizar el certamen.
*/
void asignarPregunta(tCertamen* certamen, int n_pregunta, tPregunta* pregunta){
    certamen->preguntas[n_pregunta] = *pregunta;
    free(pregunta);
}

/*
Función que retorna una pregunta del certamen.

    Parametros:
        certamen(tCertamen): certamen que contiene las preguntas del certamen.
        n_Pregunta(int): Numero de la pregunta que se quiere retornar.
    Retorno:
        certamen->preguntas[n_pregunta](tPregunta): pregunta del certamen buscada
*/
tPregunta leerPregunta(tCertamen* certamen, int n_pregunta){
    return certamen->preguntas[n_pregunta];
}

/*
Función que asigna la respuesta del usuario a la pregunta.

    Parametros:
        certamen(tCertamen): certamen que contiene las preguntas a las que se le quiere asignar la respuesta del usuario.
        n_Pregunta(int): Numero de la pregunta a la que se le quiere asignar la respuesta.
        respuesta(void*): Puntero generico a cualquier tipo de respuesta entregada por el usuario.
    Retorno:
        void
*/
void asignarRespuestaUsuario(tCertamen* certamen,int n_pregunta, void* respuesta){
    certamen->preguntas[n_pregunta].respuesta = respuesta;
}

/*
Función que retorna el numero de preguntas correctas del usuario.

    Parametros:
        certamen(tCertamen): certamen que contiene las preguntas a las que se quiere revisar si son correctas.

    Retorno:
        correctas(int): Numero de preguntas correctas del usuario al realizar el certamen.
*/
int nCorrectasCertamen(tCertamen certamen){
    int nPreguntas = certamen.n_preguntas, correctas = 0;
    for(int i = 0; i<nPreguntas;i++){ 
        tPregunta* pregunta = certamen.preguntas;
        if(pregunta[i].revisar(pregunta[i].enunciado,pregunta[i].respuesta)){
            correctas++;
        }
    }
    return correctas;
}

/*
Función que retorna el numero de preguntas del certamen.

    Parametros:
        certamen(tCertamen): certamen que contiene las preguntas que luego se retornarán.

    Retorno:
        certamen.n_preguntas(int): Numero de preguntas que contiene el certamen.
*/
int largoCertamen(tCertamen certamen){ return certamen.n_preguntas; }

/*
Función que se encarga de revisar si la respuesta entregada por el usuario es correcta o no.
Esto lo hace para el tipo de enunciado AlternativaSimple.
Si la respuesta es correcta retorna true en caso contrario retorna false.

    Parametros:
        enunciado(void*): Puntero generico a cualquier tipo de enunaciado. Contiene la información del enunciado del certamen
        respuesta(void*): Puntero generico a cualquier tipo de respuesta. Contiene la información de la respuesta del usuario.

    Retorno:
        (bool): Booleano que en caso de que la respuesta del usuario sea correcta será true, en caso contrario es false
*/
bool revisarAlternativaSimple(void* enunciado, void* respuesta){
    tEnunciadoAlternativa* enun = (tEnunciadoAlternativa*)enunciado;
    int res = atoi((char*)respuesta);
    if((res == enun->alternativa_correcta)) return true;
    else return false;
}

/*
Función que se encarga de revisar si la respuesta entregada por el usuario es correcta o no.
Esto lo hace para el tipo de enunciado AlternativaMultiple.
Si la respuesta es correcta retorna true en caso contrario retorna false.

    Parametros:
        enunciado(void*): Puntero generico a cualquier tipo de enunaciado. Contiene la información del enunciado del certamen
        respuesta(void*): Puntero generico a cualquier tipo de respuesta. Contiene la información de la respuesta del usuario.

    Retorno:
        (bool): Booleano que en caso de que la respuesta del usuario sea correcta será true, en caso contrario es false
*/
bool revisarAlternativaMultiple(void* enunciado, void* respuesta){
    tEnunciadoAlternativaMultiple* enun = (tEnunciadoAlternativaMultiple*)enunciado;
    int* res = (int*)respuesta;
    int* arrCorrectas = enun->alternativa_correcta;
    int correctas = enun->n_correctas, cont = correctas;
    bool flag;
    for(int i = 0; i<correctas; i++){ //compara si las respuestas son iguales independiente del orden
        flag = false;
        for(int j = 0; j<cont; j++){
            if(res[i] == arrCorrectas[j]){
                arrCorrectas[j] = arrCorrectas[cont-1];
                arrCorrectas[cont-1] = 0;
                flag = true;
                break;
            }
        }
        if(!flag) return false;
        else cont--;
    }
    return true;
}

/*
Función que se encarga de revisar si la respuesta entregada por el usuario es correcta o no.
Esto lo hace para el tipo de enunciado VerdaderoFalso.
Si la respuesta es correcta retorna true en caso contrario retorna false.

    Parametros:
        enunciado(void*): Puntero generico a cualquier tipo de enunaciado. Contiene la información del enunciado del certamen
        respuesta(void*): Puntero generico a cualquier tipo de respuesta. Contiene la información de la respuesta del usuario.

    Retorno:
        (bool): Booleano que en caso de que la respuesta del usuario sea correcta será true, en caso contrario es false
*/
bool revisarVerdaderoFalso(void* enunciado, void* respuesta){
    tEnunciadoVerdaderoFalso* enun = (tEnunciadoVerdaderoFalso*)enunciado;
    bool* res = (bool*)respuesta;
    bool opcion = enun->respuesta;
    if(*res == opcion)return true;
    else return false;
}

/*
Función que se encarga de revisar si la respuesta entregada por el usuario es correcta o no.
Esto lo hace para el tipo de enunciado completar.
Si la respuesta es correcta retorna true en caso contrario retorna false.

    Parametros:
        enunciado(void*): Puntero generico a cualquier tipo de enunaciado. Contiene la información del enunciado del certamen
        respuesta(void*): Puntero generico a cualquier tipo de respuesta. Contiene la información de la respuesta del usuario.

    Retorno:
        (bool): Booleano que en caso de que la respuesta del usuario sea correcta será true, en caso contrario es false
*/
bool revisarCompletar(void* enunciado, void* respuesta){
    tEnunciadoCompletar* enun = (tEnunciadoCompletar*)enunciado;
    int nTextos = enun->n_textos;
    char** res = (char**)respuesta;
    for(int i = 0; i<nTextos-1;i++){
        if((strcmp(res[i],enun->respuestas[i]))!=0) return false;
    }
    return true;
}

/*
Función encargada de liberar la memoria pedida dinamicamente del certamen, la funcíon se encarga de dependiendo el tipo de la pregunta liberar cada variable que tiene memoria dinamica.

    Parametros:
        certamen(tCertamen*): certamen en el cuál se quiere liberar la memoria pedida dinamicamente

    Retorno:
        void
*/
void clearCertamen(tCertamen* certamen){
    int nPreguntas = certamen->n_preguntas;
    int nAlternativas, nTextos;
    tPregunta pregunta;

    for(int i = 0; i<nPreguntas;i++){
        pregunta = certamen->preguntas[i];
        if((strcmp(pregunta.tipo,"AlternativaSimple")==0)){
            tEnunciadoAlternativa* enun = (tEnunciadoAlternativa*)pregunta.enunciado;
            nAlternativas = enun->n_alternativas;
            for(int j=0; j<nAlternativas;j++){ //libera las alternativas
                free(enun->alternativas[j]);
            }
            free(enun->alternativas); //libera el puntero a las alternativas
            char* respuesta = (char*)certamen->preguntas[i].respuesta;
            free(enun); //libera el enunciado
            free(respuesta); //libera la respuesta usuario
        }

        else if((strcmp(pregunta.tipo,"AlternativaMultiple")==0)){
            tEnunciadoAlternativaMultiple* enun = (tEnunciadoAlternativaMultiple*)pregunta.enunciado;
            nAlternativas = enun->n_alternativas;
            for(int j=0; j<nAlternativas;j++){ //libera las alternativas
                free(enun->alternativas[j]);
            }
            free(enun->alternativas); //libera el puntero a las alternativas
            free(enun->alternativa_correcta); //libera alternativas correctas (arreglo dinamico de int normales)
            int* respuesta = (int*)certamen->preguntas[i].respuesta;
            free(enun); //libera enunciado
            free(respuesta); //libera respuesta usuario
        }

        else if((strcmp(pregunta.tipo,"VerdaderoFalso")==0)){
            tEnunciadoVerdaderoFalso* enun = (tEnunciadoVerdaderoFalso*)pregunta.enunciado;
            bool* respuesta = (bool*)certamen->preguntas[i].respuesta;
            free(enun); //libera enunciado
            free(respuesta); //libera respuesta usuario
        }

        else{ // Enunciado completar
            tEnunciadoCompletar* enun = (tEnunciadoCompletar*)pregunta.enunciado;
            nTextos = enun->n_textos;
            char** respuesta = (char**)certamen->preguntas[i].respuesta;;
            for(int j=0; j<nTextos-1;j++){ //libera respuestas, textos y respuestas del usuario
                free(enun->respuestas[j]);
                free(enun->textos[j]);
                free(respuesta[j]);
            }
            free(enun->textos[nTextos-1]);//libera texto faltante del for
            free(enun->respuestas);//libera puntero a respuestas
            free(enun->textos);//libera puntero a textos
            free(enun);//libera enunciado
            free(respuesta);//libera respuesta usuario
        }
    }
    free(certamen->preguntas); //libera puntero a preguntas
    free(certamen); //libera certamen
}



