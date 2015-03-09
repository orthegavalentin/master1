#lang racket
(require "parser.rkt")

(define population-size 100)
(define mutate-factor 7)
(define cpt 0)

(define (not-atom i)
  (if (= i 1) 0 1))

(define (generate-random-solution size problem)
  (let ([x (build-vector size (lambda (i) (random 2)))])
    (list (cost problem x) x)))

(define (generate-random-population population-size individual-size problem)
  (let f ([p '()] [i 0])
    (if (= i population-size)
        p
        (f (append p (list (generate-random-solution individual-size problem))) (add1 i)))))

(define (satisfiable? clause solution)
  (if (< 0 (apply + (map (lambda (i)
                           (letrec ([val (vector-ref solution (- (abs i) 1))] [x (if (= val 1) 1 -1)])
                             (set! cpt (add1 cpt))
                             (if (< 0 (* i x)) 1 0))) clause))) #t #f))

(define (cost problem solution)
  (if (= 0 (vector-length solution)) 0 
      (apply + (map (lambda (i)
                      (if (satisfiable? i solution) 0 1)) problem))))

(define (mutate solution)
  (let ([r (random (vector-length solution))])
    (vector-set! solution r (not-atom (vector-ref solution r)))))

(define (crossover mother father problem)
  (let ([r (random (vector-length mother))] [child (vector-copy mother)])
    (vector-copy! child r father r)
    (mutate child)
    (list (cost problem child) child)))

(define (get-parents population)
  (let f ([parents '()] [p population])
    (if (empty? p)
        parents
        (f (append parents (list (list (car p) (cadr p)))) (cddr p)))))

(define (next-generation population problem)
  (let ([population (sort population (lambda (i j)
                                       (< (car i) (car j))))])
    (if (zero? (caar population))
        (list (car population))        
        (letrec ([p (take population (/ population-size 2))] [parents (get-parents p)])
          (append p (map (lambda (i)
                           (crossover (cadr (car i)) (cadr (cadr i)) problem)) parents) 
                  (map (lambda (i)
                         (crossover (cadr (cadr i)) (cadr (car i)) problem)) parents))))))

(define (solve i max-iterations population problem )
  (let ([p (next-generation population problem)])
    (if (= (length p) 1)
        (car p)
        (if (eq? max-iterations i)
            (car p)
            (solve (add1 i) max-iterations p problem)))))


(define (main)
  (letrec ([args (current-command-line-arguments)]
           [p (read-file (open-input-file (vector-ref args 0) #:mode 'binary))]
           [atom-number (car p)]
           [clause-number (cadr p)]
           [size (string->number (vector-ref args 1))]
           [problem (caddr p)])
    (set! population-size (+ size (- 4 (modulo size 4))))
    (set! mutate-factor (string->number (vector-ref args 2)))
    (solve 0 (string->number (vector-ref args 3)) (generate-random-population population-size atom-number problem) problem)))

(time (main))
(displayln cpt)
