#lang racket
(require "parser.rkt")

(define max-tries 100)
(define max-moves 5)

(define cpt 0)

(define (not-atom i)
  (if (= i 1) 0 1))

(define (satisfiable? clause solution)
  (if (< 0 (apply + (map (lambda (i)
                           (letrec ([val (vector-ref solution (- (abs i) 1))] [x (if (= val 1) 1 -1)])
                             (if (< 0 (* i x)) 1 0))) clause))) #t #f))

(define (generate-random-solution size)
  (build-vector size (lambda (i) (random 2))))

(define (cost problem solution)
  (if (= 0 (vector-length solution)) 0 
      (apply + (map (lambda (i)
                      (if (satisfiable? i solution) 1 0)) problem))))

(define (generate-neighbor solution)
  (let ([r (random (vector-length solution))])
    (vector-set! solution r (not-atom (vector-ref solution r)))))

(define (generic-move problem x max-n)
  (let ([best-cost 0]
        [best x]
        [x-cost (cost problem x)]
        [temp (vector-copy x)])
    (let f ([continue? #t] [i 0])
      (set! cpt (add1 cpt))
      (generate-neighbor x)
      (if continue?
          (letrec ([c (cost problem x)] [accepted? (> c x-cost)])
            (when (> c best-cost)
              (set! best x)
              (set! best-cost c))
            (vector-copy! x 0 temp)
            (f (and (not accepted?) (< i max-n)) (add1 i)))
            best))))

(define (solve atom-number clause-number problem)
  (let ([best #()] [solution #()])
    (for ([i (in-range max-tries)])
      (set! solution (generate-random-solution atom-number))
      (let ([best-walk solution])
        (for ([j (in-range max-moves)])
          (generic-move problem solution atom-number)
          (when (> (cost problem solution) (cost problem best-walk))
            (set! best-walk solution)))
        (when (> (cost problem best-walk) (cost problem best))
          (set! best best-walk))))
    (list (cost problem best) best)))

(define (main)
  (letrec ([p (read-file (open-input-file "uf20-0912.cnf" #:mode 'binary))]
           [atom-number (car p)]
           [clause-number (cadr p)]
           [problem (caddr p)])
    (solve atom-number clause-number problem)))

(main)
(display cpt)