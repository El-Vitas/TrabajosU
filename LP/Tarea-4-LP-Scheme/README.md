# Instrucciones
## 1.	Objetivo
En esta tarea deberán implementar una serie de funciones para conocer y aplicar correctamente los conceptos y técnicas del paradigma de programación funcional, utilizando el lenguaje Scheme.
## 2. Funciones a implementar
### 1. Inverso
* **Sinopsis**: (inverso lista n)
* **Característica Funcional**: Funciones puras
* **Descripción**: Se le entrega una lista de números (lista) y un numero (n), debe retornar una lista con todos los números entre 0 y n (sin incluir) que no estén en lista.

*Ejemplo*:
`````rkt
>(inverso '(1 3 7) 10)
(0 2 4 5 6 8 9)
`````
### 2.	Umbral
* **Sinopsis**: (umbral_simple lista umbral tipo) (umbral_cola lista umbral tipo)
* **Característica Funcional**: Listas simples, recursión simple y recursión cola
* **Descripción**: Se le entrega una lista de números (lista), un numero (umbral) y un carácter (tipo). Si tipo es ‘M‘ debe retornar una lista con todas las posiciones de los elementos de lista que sean Mayores que umbral, si tipo es ‘m‘ entonces debe retornar todas las posiciones de los elementos menores que umbral.
Esta funcionalidad se debe implementar en dos funciones, donde (umbral_simple lista umbral tipo) debe realizar recursión de simple y (umbral_cola lista umbral tipo) debe realizar recursión de cola.

*Ejemplo*:
`````rkt
>(umbralsimple '(15 2 1 3 27 5 10) 5 #\M)
(0 4 6)
>(umbralcola '(15 2 1 3 27 5 10) 5 #\m)
(1 2 3)
`````

### 3. Modificar seleccionados
* **Sinopsis**: (modsel simple lista seleccion f) (modsel cola lista seleccion f)
* **Característica Funcional**: Funciones lambda, recursión simple y recursión cola
* **Descripción**: Se le entrega dos listas de números (lista y seleccion) y una función lambda (f), por cada número en la lista, si su índice está en selección entonces se le debe aplicar la función f, en caso contrario el número se mantiene igual.
Esta funcionalidad se debe implementar en dos funciones, donde (modsel_simple lista seleccion f) debe realizar recursión simple y ( (modsel_cola lista seleccion f)) debe realizar recursión de cola.

*Ejemplo*:
`````rkt
>(modselsimple '(15 2 1 3 27 5 10) '(0 4 6) (lambda (x) (modulo x 2)))
(1 2 1 3 1 5 0)
>(modselsimple '(15 2 1 3 27 5 10) '(3 1 2) (lambda (x) (+ x 5)))
(15 7 6 8 27 5 10)
`````

### 4. Estables
* **Sinopsis**: (estables lista umbral fM fm)
* **Característica Funcional**: Listas simples, inmutabilidad y funciones lambda
* **Descripción**: Se le entrega una lista de números (lista), un numero (umbral) y dos funciones lambda (fM y fm). Utilizando las funciones implementadas anteriormente, retornar una lista con dos números, en donde el primero es la cantidad de números mayores que el umbral que al aplicarles fM siguen siendo mayores que el umbral, y el segundo es la cantidad de números menores que el umbral que al aplicarles fm siguen siendo menores que el umbral.

*Ejemplo*:
`````rkt
>(estables '(15 2 1 3 27 5 10) 5 (lambda (x) (/ x 2)) (lambda (x) (* x 2)))
(2 1)
`````

### 5. ¡Todo lo anterior, y ahora en 2D!
* **Sinopsis**: (query lista pos op params)
* **Característica Funcional**: Manejo de listas
* **Descripción**: Se le entrega una lista de listas de enteros (lista), la posición de una lista de enteros dentro de esta lista de listas (pos), un numero entre 1 y 3 que indica una operación a realizar sobre la lista (op) y una lista con los parámetros necesarios para esa operación (params).
Para los valores de pos:
    * 1: Debe aplicar Umbral sobre la lista en la posición pos. La variable params contendrá dos elementos: el valor del umbral y el tipo de umbral.
    * 2: Debe aplicar modsel sobre la lista en la posición pos. La variable params contendrá dos elementos: una lista con la selección y una función a aplicar a la selección.
    * 3: Debe aplicar estables sobre la lista en la posición pos. La variable params contendrá tres elementos: el valor del umbral, una función fM y una función fm. La función debe retornar el resultado de la operación (no la lista de listas modificada).
    
*Ejemplos*:
`````rkt
>(query '((0 1 2 3 4) (4 3 2 1 0) (15 2 1 3 27 5 10)) 1 1 '(1 #\M))
(0 1 2)
>(query '((0 1 2 3 4) (4 3 2 1 0) (15 2 1 3 27 5 10)) 0 2 '((0 4) (lambda
(x) (+ x 100))))
(100 1 2 3 104)
>(query '((0 1 2 3 4) (4 3 2 1 0) (15 2 1 3 27 5 10)) 2 3 '(5 (lambda (x)
(/ x 2)) (lambda (x) (* x 2))))
(2 1)
`````
## 3. Programa 
Para ejecutar el programa debe descargar el software racket. http://racket-lang.org/download/
Luego abrir el archivo .rkt y dar a run.
Finalmente dentro de la consola del racket podrá ejecutar las funciones del programa.
