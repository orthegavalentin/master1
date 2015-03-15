#lang racket

(require "parser.rkt")
(require "genetic.rkt")

(define (not-atom i)
  (if (= i 1) 0 1))

(define (generate-random-solution size problem)
 ; (build-vector size (lambda (i) (random 2))))
  (cadr (solve 100 problem 100 size)))


(define (make-clauses-vector problem size)
  (let* ([size (+ 1 size)] [v (make-vector size '())])
    (for-each (λ (clause)
                (for-each (λ (var)
                            (vector-set! v (abs var) (append (vector-ref v (- (abs var) 1)) `(,clause)))) clause)) problem)
    v))

(define (satisfiable? clause solution)
  (ormap (lambda (i)
           (let* ([val (vector-ref solution (- (abs i) 1))]
                  [x (if (= val 1) 1 -1)])
             (> 0 (* i x)))) clause))

(define (cost problem solution)
  (if (= 0 (vector-length solution)) 0 
      (apply + (map (lambda (i)
                      (if (satisfiable? i solution) 0 1)) problem))))

(define (get-unsat-clauses problem solution)
  (filter (λ (i)
            (if (satisfiable? i solution) #f #t)) problem))

(define (flip-variable solution variable)
  (vector-set! solution (- (abs variable) 1) (not-atom (vector-ref solution (- (abs variable) 1)))))

(define (flip problem solution clauses-vector probability)
  (let ([unsats (get-unsat-clauses problem solution)])
    (if (empty? unsats)
        #f
        (begin
          (flip-variable solution
                         (if (< (random 100) probability)
                             (+ 1 (random (vector-length solution)))
                             (let ([c (list-ref unsats (random (length unsats)))])
                               (caar
                                (sort
                                 (foldr (λ (i l)
                                          (flip-variable solution i)
                                          (let ([res `(,(abs i) ,(cost `(,c) solution))])
                                            (flip-variable solution i)
                                            (append `(,res) l))) '() c) (λ (i j)
                                                                          (< (cadr i) (cadr j)))))))) #t))))

(define (solve-walksat problem atom-number iter proba)
  (let* ([solution (generate-random-solution atom-number problem)]
         [clauses-vector '() #|(make-clauses-vector problem atom-number)|#])
    (let f ([cpt 0])
      (displayln (cost problem solution))
      (if (and (< cpt iter) (flip problem solution clauses-vector proba))
          (f (+ cpt 1))
          `(,(cost problem solution) ,solution)))))

(define (main args)
  (let* ([p (read-file (open-input-file (vector-ref args 0) #:mode 'binary))]
         [atom-number (car p)]
         [proba (string->number (vector-ref args 2))]
         [max-tries (string->number (vector-ref args 1))]
         [problem (caddr p)])
    (solve-walksat problem atom-number max-tries proba)))

(time (main (current-command-line-arguments)))
;(time (main #("/home/noe/dev/fac/algo_exploration_mouvement/test.cnf" "100" "5")))