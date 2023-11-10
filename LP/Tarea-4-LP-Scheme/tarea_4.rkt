#lang scheme

(define-namespace-anchor anc)
(define ns (namespace-anchor->namespace anc)) ;;estos elementos sirven para que funcione el eval dentro de una función

;; Función encargada de mediante una lista y un numero n, mostrar por pantalla otra lista del 0 a n (sin incluir n), sin los valores de la lista entregada.
;;
;; lista: lista con numeros.
;; n: numero que indica el tope del numero maximo que estará en la lista. (El tope no incluye al n)
(define inverso
  (lambda (lista n)
    (let makeL((i (- n 1)) (nlista '()))
      (if (>= i 0)
          (makeL (- i 1) (cons i nlista))
          (let filterL((l lista) (nl nlista))
            (if (null? l)
                nl
                (filterL (cdr l) (remove (car l) nl))
                )
            )
          )
      )
    )
  )

;; Función encargada de mediante una lista, un umbral y un tipo, entregar una nueva lista con la posicion de la lista de los mayores o menores al umbral.
;; La función se realiza mediante recursividad simple.
;;
;; lista: lista con numeros.
;; umbral: numero que define cuales deben ser menores o mayores a ese numero
;; tipo: tipo que indica si se buscaran los mayores o los menores.
(define umbral_simple
  (lambda (lista umbral tipo)
    (let umbS((li lista) (listN '()) (cont 0))
      (if (null? li)
          listN
          (if (equal? #\M tipo)
              (if (> (car li) umbral)
                  (cons cont (umbS (cdr li) listN (+ cont 1)))
                  (umbS (cdr li) listN (+ cont 1))
                  )
              (if (< (car li) umbral)
                  (cons cont (umbS (cdr li) listN (+ cont 1)))
                  (umbS (cdr li) listN (+ cont 1))
                  )    
              )
          )
      )
    )
  )

;; Función encargada de mediante una lista, un umbral y un tipo, entregar una nueva lista con la posicion de la lista de los mayores o menores al umbral.
;; La función se realiza mediante recursividad de cola.
;;
;; lista: lista con numeros.
;; umbral: numero que define cuales deben ser menores o mayores a ese numero
;; tipo: tipo que indica si se buscaran los mayores o los menores.
(define umbral_cola
  (lambda (lista umbral tipo)
    (let umbC((li lista)(listN '()) (cont 0))
      (if (null? li)
          listN
          (if (equal? #\M tipo)
              (if (> (car li) umbral)
                  (umbC (cdr li) (append listN (list cont)) (+ cont 1))
                  (umbC (cdr li) listN (+ cont 1))
                  )
              (if (< (car li) umbral)
                  (umbC (cdr li) (append listN (list cont)) (+ cont 1))
                  (umbC (cdr li) listN (+ cont 1))
                  )    
              )
          )
      )
    )
  )

;; Función encargada de mediante una lista, una lista de selección, y una función lambda.
;; Si el indice del numero de la lista se encuentra en la lista selección, se le aplicará una función f, en caso contrario se dejará igual.
;; La función se realiza con recursividad simple.
;;
;; lista: lista con numeros.
;; seleccion: lista con numero que representan indices.
;; f: funcion lambda a aplicar.
(define modsel_simple
  (lambda (lista seleccion f)
    (letrec
        (
         (modelS (lambda(li listN cont)
               (if(null? li)
                  listN
                  (cons (inSelec (car li) seleccion cont) (modelS (cdr li) (append listN (list )) (+ cont 1)))
                  )
               )
             )
         (inSelec (lambda(n sel cont)
                    (if (null? sel)
                        n
                        (if (= cont (car sel))
                            (f n)
                            (inSelec n (cdr sel) cont)
                            )
                        )
                    )
                  )
         )
      (modelS lista '() 0)
      )
    )
  )

;; Función encargada de mediante una lista, una lista de selección, y una función lambda.
;; Si el indice del numero de la lista se encuentra en la lista selección, se le aplicará una función f, en caso contrario se dejará igual.
;; La función se realiza con recursividad de cola.
;;
;; lista: lista con numeros.
;; seleccion: lista con numero que representan indices.
;; f: funcion lambda a aplicar.
(define modsel_cola
  (lambda (lista seleccion f)
    (letrec
        (
         (modelC (lambda(li listN cont)
               (if(null? li)
                  listN
                  (modelC (cdr li) (append listN (list (inSelec (car li) seleccion cont))) (+ cont 1))
                  )
               )
             )
         (inSelec (lambda(n sel cont)
                    (if (null? sel)
                        n
                        (if (= cont (car sel))
                            (f n)
                            (inSelec n (cdr sel) cont)
                            )
                        )
                    )
                  )
         )
      (modelC lista '() 0)
      )
    )
  )

;; Función encargada de mediante una lista, un umbral y 2 funciones lambda, mostrar por pantalla una lista de 2 elementos, en el cuál el primer valor corresponde a
;; la cantidad de numeros mayores que umbral que al aplicarle la función fM sigue siendo mayor que umbral.
;; El segundo valor corresponde la cantidad de numeros menores que umbral que al aplicarle la función fm sigue siendo menor que umbral.
;; Esto se realiza con un llamado a otras funciones.
;;
;; lista: lista con numeros.
;; umbral: numero que define cuales deben ser menores o mayores a ese numero
;; fM: funcion lambda a aplicar a los numeros mayores que umbral
;; fm: funcion lambda a aplicar a los numeros menores que umbral
(define estables
  (lambda (lista umbral fM fm)
      (list (length (umbral_cola (modsel_cola lista (umbral_cola lista umbral #\M) fM) umbral #\M)) (length (umbral_cola (modsel_cola lista (umbral_cola lista umbral #\m) fm) umbral #\m)))
    )
  )

;; Función encargada de mediante una lista de listas, una posición, una operacion y unos parametros, buscar la sublista que se encuentra en la posicion "pos", dentro de lista
;; y dependiendo de la operación llamar a una función u a otra.
;; Si op es 1, se aplicará la funcion umbral_cola sobre la sublista.
;; Si op es 2, se aplicará la funcion modsel_cola sobre la sublista.
;; Si op es 3, se aplicará la funcion estables sobre la sublista.
;;
;; lista: lista con numeros.
;; pos: posición de la sublista que se quiere buscar dentro de la lista
;; op: numero que indica la operacion a realizar
;; params: lista con parametros, puede variar entre 2 y 3 dependiendo de la operación.
(define query
  (lambda (lista pos op params)
    (let searchPos((li lista) (listN (car lista)) (cont 0))
      (if (= cont pos)
          (cond
            ((= op 1)
             (umbral_cola listN (car params) (car (cdr params)))
             )
            ((= op 2)
             (modsel_cola listN (car params) (eval (car (cdr params)) ns))
             )
            ((= op 3)
             (estables listN (car params) (eval (car (cdr params)) ns) (eval (car (cdr (cdr params))) ns))
             )
            )
          (searchPos (cdr li) (car (cdr li)) (+ cont 1))
          )
      )
    )
  )









