# Instrucciones
## 1.	PixelArt
Un jugador de Minecraft amante del pixelart, un día buscando creaciones de otros jugadores, se encontró con un sitio web que aseguraba tener diseños que nunca antes había visto, con instrucciones muy detalladas de cómo construirlos; sin embargo, ¡este sitio no contaba con imágenes para saber cómo se ven los resultados de seguir esas instrucciones!


*Code 1: Ejemplo de instrucciones*

```
1	Ancho 8
2	Color de fondo RGB(13,181,13)
3
4	Avanzar Derecha Avanzar 2
5	Pintar Negro Avanzar
6	Repetir 2 veces { Pintar Negro Izquierda Avanzar }
7	Pintar Negro
8	Derecha Avanzar 3
9	Pintar Negro Avanzar
10	Repetir 2 veces { Pintar Negro Derecha Avanzar }
11	Pintar Negro
12	Izquierda Avanzar
13	Repetir 3 veces { Avanzar Pintar Negro }
14	Derecha Avanzar 3 Derecha
15	Repetir 3 veces { Pintar Negro Avanzar }
16	Derecha Avanzar
17	Repetir 3 veces {
18	Pintar Negro Avanzar
19	Pintar Negro Derecha Avanzar
20	Derecha Avanzar Derecha Derecha
21	}
```
Es por lo anterior que este jugador le pidió a los alumnos de Lenguajes de Programación que utilicen los contenidos del curso para crear un programa capaz de interpretar las instrucciones del sitio y producir una imagen del resultado.
Para esta tarea se debe utilizar Python 3 y los siguientes paquetes:
RegEx para las expresiones regulares de la tarea
NumPy y Pillow para convertir los resultados a imágenes. El código para este proceso se les será entregado.
## 2.	Lenguaje PixelArt (LPA)
### 2.1.	Acerca de LPA
El Lenguaje PixelArt es un nuevo lenguaje interactivo que permite a un jugador, mediante una secuencia de instrucciones, producir uno de los pixelarts del sitio. Siempre se asume que el jugador comienza en la esquina superior izquierda apuntando hacia la derecha. El objetivo es simular el procedimiento que seguirá un jugador y guardar el resultado como una matriz (lista de listas en Python) de valores RGB (tupla de 3 valores entre 0 y 255 en Python).
### 2.2.	Matriz
La matriz sería de tamaño n×n, siendo n un valor que se especificará más adelante, donde inicialmente todos los valores parten en un mismo color.
### 2.3.	Comandos
Todo archivo siempre comienza con los siguientes comandos en este orden:

* **Ancho** N: Indica que la imagen será de tamaño N×N.

* **Color de fondo** Color:Indica el color de fondo que tendrá la imagen, es decir, si un bloque no es pintado entonces será de este color. El formato que sigue Color se indica más adelante.
Posterior a estos habrá una línea en blanco y luego seguirán las instrucciones, las cuales pueden ser cualquier combinación de las siguientes:

* **Izquierda**: El jugador debe girar en 90° a la izquierda.

* **Derecha**: El jugador debe girar en 90° a la derecha.

* **Avanzar** N: El jugador debe avanzar N cuadros en la dirección en la que está mirando. En caso de que no se entregue un número, el jugador deber ‘a avanzar 1 bloque.

* **Pintar** Color: El jugador debe pintar el bloque en el que se encuentra de color Color. El formato que sigue Color se indica más adelante.

* **Repetir** N **veces** {Instrucciones}: El jugador debe repetir las instrucciones indicadas en Instrucciones N veces. Las instrucciones pueden ser cualquiera de las anteriormente nombradas a excepción de **Ancho** y **Color de fondo**. Esto sígnica que pueden haber instrucciones de **Repetir** anidadas.

Cuando un comando requiera de un Color como parámetro, este podrá recibir uno de los siguientes valores:

* **Rojo**: Deberá pintar de color rojo, escribiendo en la matriz de memoria la tupla (255,0,0).
* **Verde**: Deberá pintar de color verde, escribiendo en la matriz de memoria la tupla (0,255,0).
* **Azul**: Deberá pintar de color azul, escribiendo en la matriz de memoria la tupla (0,0,255).
* **Negro**: Deberá pintar de color negro, escribiendo en la matriz de memoria la tupla (0,0,0).
* **Blanco**: Deberá pintar de color blanco, escribiendo en la matriz de memoria la tupla (255,255,255).
* **RGB**(R,G,B): Deberá pintar del color indicado, escribiendo en la matriz de memoria la tupla (R,G,B).
A continuación se presenta un EBNF que describe formalmente la sintaxis que siguen las instrucciones de un programa:

*Code 2: EBNF*
```
1	instruccion ::= ’Izquierda’ | ’Derecha’
2	| ’Avanzar’ [numero] | ’Pintar’ color
3	| ’Repetir’ numero ’veces’ ’{’ {instruccion} ’}’
4
5 numero ::= 0 | no_zero {’0’ | no_zero}
6
7 no_zero ::= ’1’ | ’2’ | ’3’ | ’4’ | ’5’ | ’6’ | ’7’ | ’8’ | ’9’
8
9	color ::= ’Rojo’ | ’Verde’ | ’Azul’ | ’Negro’ | ’Blanco’
10	| ’RGB(’ numero ’,’ numero ’,’ numero ’)’
 ```
 
Puede haber múltiples instrucciones en una línea. Adicionalmente las instrucciones de tipo Repetir pueden abarcar múltiples líneas.
### 2.4.	Orden de operaciones
Las instrucciones siempre se ejecutan de izquierda a derecha.
## 3.	Objetivo de la tarea
Se debe crear un programa el cual permita recibir una cantidad indefinida de líneas en un archivo codigo.txt, en donde la primera línea siempre indicara el tamaño de la matriz que se utilizará, la segunda el color de fondo, la tercera será una línea en blanco y luego cada línea siguiente corresponderá a una serie de instrucciones.
Su programa debe ser capaz interpretar el código, detectar errores de sintaxis, y detectar errores de ejecución. Sintaxis: a partir del archivo codigo.txt, su programa debe generar un archivo errores.txt, donde se encontraran todas las líneas que tengan una sintaxis incorrecta, indicando el número de línea en la cual se encuentra el error, en el caso que no hayan errores el archivo deberá contener la frase “No hay errores!”. Interprete: debe producir pixelart.png y mostrar por consola los valores de la matriz RGB en caso de que la ejecución y la revisión de sintaxis sea exitosa. Si durante la ejecución las instrucciones causaran que el jugador salga del área que cubre la matriz, se debe indicar por consola la línea que produjo este error y terminar la ejecución.

### 3.1. Ejemplos

#### 3.1.1. Ejemplo 1

*Code 3: Ejemplo 1*
```
1	Ancho 10
2	Color de fondo Blanco
3
4	Avanzar Derecha Avanzar
5	Repetir 4 veces {
6	Repetir 8 veces { Pintar Negro Avanzar } 7 Derecha Derecha Avanzar Derecha
8 }
```
*Code 4: errores.txt*
```
No hay errores!
```
<image src="examples/Imagen1.jpg" alt="Descripción de la imagen">
Figura 1: pixelart.png
	
#### 3.1.2. Ejemplo 2
	
*Code 5: Ejemplo 2*
```
1	Ancho 3
2	Color de fondo RGB(0,0,0)
3
4	Pintar Rojo Avanzar 2 Derecha
5	Pintar Verde Avanzar 2 Derecha
6	Pintar Azul Avanzar 2 Derecha
7	Pintar Blanco Avanzar Derecha Avanzar
8	Pintar RGB(0,255,255)
```
*Code 6: errores.txt*
```
No hay errores!
```

<image src="examples/Imagen2.jpg" alt="Descripción de la imagen">
Figura 2: pixelart.png
	
#### 3.1.3. Ejemplo 3
	
*Code 7: Ejemplo 3*
```
1	Ancho 3
2	Color de fondo Negro
3
4	Repetir 2 {
5	Pintar RGB(255,0,0) Avanzar Derecha 1 Avanzar
6	}
7	Pintar RGB(255,0,0)
```
*Code 8: errores.txt*
```
1	4 Repetir 2 {
2	5 Pintar RGB(255,0,0) Avanzar Derecha 1 Avanzar
```
## Programa
Informacion: El programa cuenta de 4 archivos .py: instrucciones.py: Funciones ligadas a las instrucciones del programa. informacion.py: Informacion extra necesaria para el programa. matrizRGB.py: Matriz del programa, funciones relacionadas a matrices y a convertir matrices a imagen pixelart.py: Modulo principal del programa, el cual se tiene que ejecutar para el funcionamiento de este.

Cuenta con 2 archivos de texto:
* archivo.txt: Archivo donde se encontrarán todas las instrucciones del programa.
* errores.txt: Archivo donde se mostrarán los errores de sintaxis del programa. (este archivo se crea automaticamente despues de la ejecucion del programa.)
    
Cuenta con un archivo .png:
* pixelart.png: Imagen creada en caso de que la sintaxis del programa sea correcta (este archivo se crea automaticamente despues de la ejecucion del programa.).

Respecto a los errores de sintaxis y de ejecución: 
* El programa considerará error de sintaxis cada conjunto de caracteres o simbolos que no pertenezca las instrucciones validas entregadas en el respectivo pdf de la tarea.
	
* El programa considerará como error un repetir que abre pero no cierra. El error se marcará en la linea que empezó el repetir. Si se encuentran más repetir dentro, el error lo seguirá marcando en el primer repetir que se encuentra fuera de los otros repetir.
	
* El programa leera todo el texto buscando un error de sintaxis, en caso de que exista algun error, el programa al terminar el analisis de la sintaxis escribirá en el texto error.txt todos los errores y terminará el programa.
	
* Errores como: Salirse de una posicion permitida dentro de la matriz , o rango de numeros RGB incorrectos. Se considerarán errores de ejecución y el programa imprimira los errores por consola y luego finalizará.

Sobre instrucción repetir: La instrucción repetir funciona recursivamente entre 3 funciones. opciones, cierreRep, repetir.

Ejecución del programa: Para ejecutar el programa se deben tener todos los archivos tanto .py como .txt dentro de la misma carpeta, de no ser así se necesitaría modificar el codigo. Luego con los archivos dentro de la misma carpeta se necesita ejecutar pixelart.py

Al realizar todo lo anterior si las instrucciones entregadas son correctas, aparecerá un archivo llamado pixelart.png el cuál corresponde a la imagen creada 
mediante las instrucciones. De no ser así se le marcará un error por consola, o en el archivo errores.txt (este archivo se crea automaticamente despues de la ejecucion del programa).
