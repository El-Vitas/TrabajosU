# Instrucciones
## 1. Certamen
Después de haber programado exitosamente un traductor para los pixelarts en Minecraft usted se tomó un merecido tiempo de descanso, comenzando una partida del famoso juego de bloques con sus amigos, en donde construyeron y tuvieron aventuras. Antes de que lo pudieran notar pasaron semanas, y ahora están a tan solo días de la fecha de un certamen muy importante para el cual no han estudiado. En un último intento por salvar este, usted decide hacer un programa que le permita simular un certamen para poder practicar tantas veces como sea necesario en el poco tiempo que queda.
## 2. Definición
Para esta tarea usted deberá crear un programa en C capaz de crear un certamen en base a las especificaciones en un archivo de texto y responderlo en base al input por consola de un usuario. Para lograr esto deberán crear una estructura de datos que almacene el certamen y sus preguntas haciendo uso de memoria dinámica, punteros a void y punteros a función.
### 2.1. Tipos de preguntas
Los exámenes podrán tener 4 tipos de preguntas:
* **AlternativaSimple**: Estas preguntas tienen un enunciado, múltiples alternativas y se responden seleccionando una de las alternativas.
* **AlternativaMultiple**: Estas preguntas tiene un enunciado, múltiples alternativas y se responden seleccionando múltiples de las alternativas.
* **VerdaderoFalso**: Estas preguntas tienen un enunciado y se responden con un booleano Verdadero o Falso.
* **Completar**: Estas preguntas tienen múltiples secciones de texto que deben ser respondidas completadas con una palabra que une las distintas secciones de texto. Ej:
    * Enunciado: “Este”,” debe ser”, “.”
    * Respuesta: “enunciado”, “completado”
    * Frase completa: “Este enunciado debe ser completado”
### 2.2. Archivo certamen.txt
Su programa leerá el certamen desde el archivo *certamen.txt*. Este archivo comienza con una línea con un entero **N**, seguido de **N** preguntas. Cada pregunta comienza con una línea con un string **tipo** que indica el tipo de pregunta a la que corresponder, seguido del enunciado de la pregunta, la forma del cual dependerá del tipo de pregunta.

* Si la pregunta es de tipo **AlternativaSimple** entonces contendrá una línea con el string **enunciado**, una línea con el entero **n_alternativas** que indica el número de alternativas de la pregunta, **n_alternativas** líneas cada una con un string que corresponde a una alternativa y una línea con un entero correspondiente a la alternativa correcta.
* Si la pregunta es de tipo **AlternativaMultiple** entonces contendrá una línea con el string **enunciado**, una línea con el entero **n_alternativas** que indica el número de alternativas de la pregunta, **n_alternativas** líneas cada una con un string que corresponde a una alternativa, una línea con el entero **n_correctas** que indica el número de alternativas correctas y **n_correctas** líneas cada una con un entero que indica una alternativa correcta.
* Si la pregunta es de tipo **VerdaderoFalso** entonces contendrá una línea con el string **enunciado** y una línea con **V** o **F**.
* Si la pregunta es de tipo **Completar** entonces contendrá una línea con el entero **n_textos**, seguido de **n_textos** líneas cada una con un string correspondiente a una parte del texto que debe ser completado, seguido de **n_textos - 1** líneas cada una con un string correspondiente a las respuestas correctas.
Puede asumir que este archivo siempre será correcto, por lo que no hay que comprobar que cumpla este formato.
### 2.3.	Estructura de datos
La información extraída de certamen.txt debe ser almacenada en una estructura de la siguiente forma:
`````c
1	typedef struct {
2		char enunciado[128];
3		int n_alternativas;
4		char∗∗ alternativas;
5		int alternativa_correcta;
6	} tEnunciadoAlternativa;
7
8	typedef struct {
9		char enunciado[128];
10		int n_alternativas;
11		char∗∗ alternativas;
12		int n_correctas ;
13		int∗ alternativa_correcta;
14	} tEnunciadoAlternativaMultiple;
15
16	typedef struct {
17		char enunciado[128];
18		bool respuesta;
19	} tEnunciadoVerdaderoFalso ;
20
21	typedef struct {
22		int n_textos;
23		char∗∗ textos;
24		char∗∗ respuestas;
25	} tEnunciadoCompletar ;
26
27	typedef struct {
28		char tipo[64];
29		void∗ enunciado;
30		void∗ respuesta;
31		bool (∗revisar)(void ∗ , void∗);
32 	} tPregunta;
33
34	typedef struct {
35		intn_preguntas;
36		tPregunta* preguntas;
37 	} tCertamen;
`````
### 2.4. Funciones
Además, se deben implementar las siguientes funciones para manipular la estructura de datos anteriormente explicada:
`````c
1	// Crea un nuevo certamen vacío
2	tCertamen∗ crearCertamen(int n_preguntas );
3
4	// Crea una pregunta con el enunciado y función de revision dados
5	tPregunta∗ crearPregunta (
6		tCertamen∗ certamen ,
7		char∗ tipo ,
8		void∗ enunciado
9		bool revisar(void∗ , void∗));
10
11	// Asigna la pregunta a la posición n pregunta del certamen
12	void asignarPregunta(
13		tCertamen∗ certamen ,
14		int n_pregunta ,
15		tPregunta∗ pregunta);
16
17	// Retorna la pregunta en la posicion n pregunta del certamen
18	tPregunta leerPregunta (tCertamen∗ certamen , int n_pregunta);
19
20	// Retorna	el numero de respuestas correctas que tiene el certamen
21	int nCorrectasCertamen(tCertamen certamen);
22
23	// Retorna	el numero de preguntas en un certamen
24	int largoCertamen (tCertamen certamen);
25
26	// Revisa si la respuesta a la pregunta es correcta
27	bool revisarAlternativaSimple (tPregunta pregunta);
28	bool revisarAlternativaMultiple (tPregunta pregunta);
29	bool revisarVerdaderoFalso (tPregunta pregunta);
30	bool revisarCompletar (tPregunta pregunta);
`````
### 2.5. Responder
Luego de leer el archivo certamen.txt y cargar la información en la estructura de datos, se le debe permitir al usuario responder el certamen a través de la consola y una vez que termine de responder se le debe mostrar su calificación. Para esto deberán hacer uso de la estructura y funciones implementadas. El formato en el que el usuario responderá el cuestionario queda a su criterio, pero para cada pregunta se debe indicar el número de pregunta, el tipo de pregunta, el enunciado, las opciones que tiene para responder (si es que aplica) y el que debe ingresar para responder (un string, un entero, múltiples enteros separados por espacios, etc)
## 3.	Ejemplos
### 3.1.	Ejemplo 1
```
1	3
2	AlternativaSimple
3	¿Cuál es la respuesta correcta a esta pregunta?
4	3
5	Esta alternativa
6	La tercera alternativa
7	La segunda alternativa
8	1
9	VerdaderoFalso
10	A monad is a monoid in the category of endofunctors
11	V
12	AlternativaMultiple
13	¿Cuáles de estos juegos usan principalmente cubos?
14	5
15	Minecraft
16	Terraria
17	Beat Saber
18	Genshin Impact
19	Apex Legends
20	2
21	1
22	3
```
### 3.2.	Ejemplo 2
```
1	3
2	Completar
3	2
4	I don’t want to deny who I’ve been. Because even my 5 are a part of who I am today.
5	failures
6	Completar
7	3
8	Un puntero es una variable que almacena la
9	de un
10	.
11	dirección de memoria
12	objeto
13	Completar
14	4
15	C es un
16	de propósito sito general desarrollado como evolución al lenguaje
17	. Se trata de un lenguaje
18	tipado.
19	lenguaje de programación
20	B
21	débilmente
```
## Programa
Programa encargado de leer un archivo certamen.txt, traspasarlo a una estructura de datos que simula ser una clase, para que el usuario pueda responderlo.
Al finalizar las preguntas se le entrega al usuario la calificacíon, y si es que aprueba o reprueba. 

Reprueba < (total de preguntas)*0.55 <= Aprueba

### Sobre el codigo:

En el codigo se suele usar mucho el metodo atoi para pasa a tipo int, esto es debido al caso en que el numero sea de 2 o más digitos.
La liberación de memoria dinamica se realiza al finalizar el programa, simulando ser un destructor.
En el codigo indica al momento de ejecutarse de que manera debe ser respondida la pregunta.
Se modificó, según se indicó en el foro de dudas del aula las funciones revisar, las cuales ahora reciben dos parametros de tipo (void*)

### De igual forma se indicará la forma en que el usuario debe responder: 

Las respuestas de tipo alternativa simple se deben responder con el digito de la alternativa correcta.
Las respuestas de tipo alternativa multiple se deben responder primero indicando el numero de alternativas que considere que son correctas, seguido de los digitos de las alternativas correctas, cada una separado de una linea (un enter).
Las respuestas de tipo verdadero y falso se deben responder con un 'V' o con un 'F', según sea el caso.
Las respuestas de tipo completar se deben responder escribiendo la palabra u oración segun el orden correspondiente, cada palabra u oración debe ser separado por una linea (un enter).

### El programa cuenta de 3 archivos:

**certamen.c** : Contiene las definiciones de las funciones.
**certamen.h** : Contiene la implementación de los struct y de las funciones.
**main.c** : Modulo principal, encargado de traspasar el certamen.txt a una estructura de datos, realizar el certamen y de revisar el certamen.

### Tambien se incluye un archivo tipo makefile para poder compilar el programa.
**make** : compila el programa creando un archivo a ejectuar con "./certamen" (sin comillas).
**make clean** : elimina los archivos creados mediante make.
