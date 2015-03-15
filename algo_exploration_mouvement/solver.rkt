#lang racket
(require "parser.rkt")
(require "walksat.rkt")

(define cpt 0)

(define (not-atom i)
  (if (= i 1) 0 1))

(define (satisfiable? clause solution)
  (ormap (lambda (i)
           (let* ([val (vector-ref solution (- (abs i) 1))]
                  [x (if (= val 1) 1 -1)])
             (set! cpt (add1 cpt))
             (> 0 (* i x)))) clause))

(define (generate-random-solution size)
  (build-vector size (lambda (i) (random 2))))

(define (cost problem solution)
  (if (= 0 (vector-length solution)) 0 
      (apply + (map (lambda (i)
                      (if (satisfiable? i solution) 1 0)) problem))))

(define (generate-neighbor solution i)
  (vector-set! solution i (not-atom (vector-ref solution i))))

(define (generic-move problem x max-n)
  (let ([best-cost 0]
        [best x]
        [x-cost (cost problem x)])
    (let f ([continue? #t] [i 0])
      (if continue?
          (begin 
            (generate-neighbor x i) 
            (letrec ([c (cost problem x)] [accepted? (> c x-cost)])
              (when (>= c best-cost)
                (set! best (vector-copy x))
                (set! best-cost c))
              (vector-set! x i (not-atom (vector-ref x i)))
              (f (and (not accepted?) (< (add1 i) max-n)) (add1 i))))
          best))))

(define (solve max-tries max-moves atom-number clause-number problem)
  (let ([best #()])
    (for ([i (in-range max-tries)])
      (letrec ([solution (cadr (solve-walksat problem atom-number 1000 0))] [best-walk solution])
        (for ([j (in-range max-moves)])
          (let ([s (generic-move problem solution atom-number)])
            (when (>= (cost problem s) (cost problem best-walk))
              (set! best-walk s))))
        (when (>= (cost problem best-walk) (cost problem best))
          (set! best best-walk))))
    (display (list (cost problem best) '/ clause-number " in " cpt " steps"))
    (newline)
    (list (- clause-number (cost problem best)) best)))

(define (main args)
  (letrec ([p (read-file (open-input-file (vector-ref args 0) #:mode 'binary))]
           [max-tries (string->number (vector-ref args 1))]
           [max-moves (string->number (vector-ref args 2))]
           [atom-number (car p)]
           [clause-number (cadr p)]
           [problem (caddr p)])
    (solve max-tries max-moves atom-number clause-number problem)))

(time (main (current-command-line-arguments)))
;(time (main #("/home/noe/dev/fac/algo_exploration_mouvement/uf20-0912.cnf" "30" "5")))
