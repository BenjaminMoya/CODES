#lang racket
;descripción: función para calcular n-esimo término de la sucesión de fibonacci
;dom: enteros positivos + {0}
;rec: enteros positivos + {0}
;tipo recursión: arbórea - binaria
(define fib (lambda (n)
              ;caso base
              (if (<= n 1) ;n entero positivo + {0}
                  n ;solución conocida
                  (+ (fib (- n 2)) (fib (- n 1))) ;descomposición recursiva
              )
       )
 )