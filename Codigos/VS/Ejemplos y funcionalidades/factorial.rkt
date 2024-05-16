#lang racket
;función que cálcula el factorial de n
;dominio: enteros positivos + {0}
;recorrido: entero positivo
;t. recursividad: natural o lineal
(define factorial (lambda (n)
                    ;caso base
                    (if (= n 0) ;condición de borde
                        1 ;solución conocida
                        (* n (factorial (- n 1)))))) ;descom. recursiva


;(factorial 4)

;--------------
;función que cálcula el factorial de n
;factorialEnvoltorio permite encapsular/ocultar
;aspectos de la implementación interna sin revelar
;la necesidad del segundo parámetro "result"
;dominio: enteros positivos + {0}
;recorrido: entero positivo
;t. recursividad: cola
(define factorialEnvoltorio (lambda (n)
           (define factorialCola (lambda (n result)
                        ;caso base
                        (if (= n 0)  ;condición de borde
                            result   ;solución
                            (factorialCola (- n 1) (* n result))))) ; descomposición recursiva

           (factorialCola n 1)
       )
  )

(factorialEnvoltorio 4)                      
                        

