#include <stdbool.h>
/*
Struct que contiene las variables para crear un enunciado de tipo alternativa simple
*/
typedef struct {
    char enunciado[128];
    int n_alternativas;
    char** alternativas;
    int alternativa_correcta;
} tEnunciadoAlternativa;

/*
Struct que contiene las variables para crear un enunciado de tipo alternativa Multiple
*/
typedef struct {
    char enunciado[128];
    int n_alternativas;
    char** alternativas;
    int n_correctas;
    int* alternativa_correcta;
} tEnunciadoAlternativaMultiple;

/*
Struct que contiene las variables para crear un enunciado de tipo alternativa VerdaderoFalso
*/
typedef struct {
    char enunciado[128];
    bool respuesta;
} tEnunciadoVerdaderoFalso;

/*
Struct que contiene las variables para crear un enunciado de tipo alternativa Completar
*/
typedef struct {
    int n_textos;
    char** textos;
    char** respuestas;
} tEnunciadoCompletar;

/*
Struct de tipo pregunta que contiene las respuestas del usuario, el tipo y la forma de revisar el cada pregunta.
*/
typedef struct {
    char tipo[64];
    void* enunciado;
    void* respuesta;
    bool (*revisar)(void*, void*);
} tPregunta;

/*
Struct que contiene todo el certamen en si, mediante otros struct.
*/
typedef struct {
    int n_preguntas;
    tPregunta* preguntas;
} tCertamen;


tCertamen* crearCertamen(int n_preguntas);
tPregunta* crearPregunta(char* tipo, void* enunciado, bool (*revisar)(void*,void*));
void asignarPregunta(tCertamen* certamen, int n_pregunta, tPregunta* pregunta);
tPregunta leerPregunta(tCertamen* certamen, int n_pregunta);
void asignarRespuestaUsuario(tCertamen* certamen,int n_pregunta, void* respuesta);
int nCorrectasCertamen(tCertamen certamen);
int largoCertamen(tCertamen certamen);

bool revisarAlternativaSimple(void* enunciado, void* respuesta);
bool revisarAlternativaMultiple(void* enunciado, void* respuesta);
bool revisarVerdaderoFalso(void* enunciado, void* respuesta);
bool revisarCompletar(void* enunciado, void* respuesta);

void clearCertamen(tCertamen* certamen);
