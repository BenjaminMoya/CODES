#lang racket
;Recursión natural factorial
(define (factorial x)
  (if (= x 1) 1
      (* x (factorial (- x 1))  ))
  )

;Recursión natural sumatoria
(define (sumatoria x)
  (if (= x 1) 1
      (+ x (sumatoria (- x 1))  ))
  )

;Recursión de árbol fibonacci
(define (fibonacci n)
  (if (= n 0) 0
      (if (= n 1) 1
          (+ (fibonacci (- n 1)) (+ (fibonacci (- n 2)))))
  ))


; Recursión de cola
(define (auxFibonacci n ac1 ac2)
  (if (= n 1) ac2
      (auxFibonacci (- n 1) ac2 (+ ac1 ac2)))
  )

(define (fibonacci2 n)
  (auxFibonacci n 0 1))


;Ejercicio resolución simple

(define (ejercicio n)
  (if (< n 3) n
      (+ (ejercicio (- n 1)) (* 2 (ejercicio (- n 2))) (* 3 (ejercicio (- n 3)))))
  )


;Con recursión de cola
;Descripción de la función: Implementa la función descrita en Moodle
;Dominio: Enteros 
;Recorrido: Enteros
;Tipo de recursión: De cola
(define auxEjercicio2 (lambda(n ac1 ac2 ac3)
  (if (< n 3) n ;Condición de borde / Solución conocida
  (if (= n 3) (+ ac1 (* 2 ac2) (* 3 ac3)) 
      (auxEjercicio2 (- n 1) (+ ac1  (* 2 ac2) (* 3 ac3)) ac1 ac2 )) ; Descomposición recursión
   )))

(define H (lambda (n)
  (auxEjercicio2 n  2 1 0)))