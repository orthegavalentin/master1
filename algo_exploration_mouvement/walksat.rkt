#lang racket

(require "parser.rkt")
;(require "genetic.rkt")

(define (not-atom i)
  (if (= i 1) 0 1))

(define (var->index var)
  (- (abs var) 1))

(define (generate-random-solution size problem)
  (build-vector size (lambda (i) (random 2))))
;(cadr (solve 100 problem 100 size)))


(define (make-clauses-vector problem size)
  (let* ([size (+ 1 size)] [v (make-vector size '())])
    (for-each (λ (clause)
                (for-each (λ (var)
                            (vector-set! v (abs var) (append (vector-ref v (var->index var)) `(,clause)))) clause)) problem)
    v))

(define (satisfiable? clause solution)
  (ormap (lambda (i)
           (let* ([val (vector-ref solution (var->index i))]
                  [x (if (= val 1) 1 -1)])
             (> 0 (* i x)))) clause))

(define (cost problem solution)
  (if (= 0 (vector-length solution)) 0 
      (apply + (map (lambda (i)
                      (if (satisfiable? i solution) 0 1)) problem))))

(define (get-clauses sat problem solution)
  (filter (λ (i)
            (if (eq? sat (satisfiable? i solution)) #f #t)) problem))

(define (flip-variable solution variable)
  (vector-set! solution (var->index variable) (not-atom (vector-ref solution (var->index variable)))))

(define (get-variable-with-fewest-unsats clause solution clauses-vector)
  (caar (sort
         (map (λ (i)
                (let ([sat-clauses (get-clauses #t (vector-ref clauses-vector (var->index i)) solution)])
                  (flip-variable solution i)
                  (let ([x `(,i ,(- (length sat-clauses) (length (get-clauses #t (vector-ref clauses-vector (var->index i)) solution))))])
                     (flip-variable solution i)
                    x))) clause)
         (λ (i j)
           (< (cadr i) (cadr j))))))

(define (flip problem solution clause-number clauses-vector probability)
  (let* ([unsats (get-clauses #f problem solution)] [current-cost (- clause-number (length unsats))])
    (if (zero? current-cost)
        #f
        (let ([index (if (< (random 100) probability)
                             (+ 1 (random (vector-length solution)))
                             (let ([c (list-ref unsats (random (length unsats)))])
                                (get-variable-with-fewest-unsats c solution clauses-vector)))])
           (flip-variable solution index)
          (when (> (cost problem solution) current-cost)
            (flip-variable solution index))
          #t))))
                              

(define (solve-walksat problem atom-number clause-number iter proba)
  (let* ([solution (generate-random-solution atom-number problem)]
         [clauses-vector (make-clauses-vector problem atom-number)])
    (let f ([cpt 0])
      ;(displayln (cost problem solution))
      (if (and (< cpt iter) (flip problem solution clause-number clauses-vector proba))
          (f (+ cpt 1))
          `(,(cost problem solution) ,solution)))))

(define (main args)
  (let* ([p (read-file (open-input-file (vector-ref args 0) #:mode 'binary))]
         [atom-number (car p)]
         [clause-number (cadr p)]
         [proba (string->number (vector-ref args 2))]
         [max-tries (string->number (vector-ref args 1))]
         [problem (caddr p)])
    (solve-walksat problem atom-number clause-number max-tries proba)))

(time (main (current-command-line-arguments)))
;(time (main #("/home/noe/dev/fac/master1/fac/algo_exploration_mouvement/test.cnf" "1000" "5")))