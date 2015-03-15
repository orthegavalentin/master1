#lang racket
(require "parser.rkt")
(provide solve)

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
  (ormap (lambda (i)
           (let* ([val (vector-ref solution (- (abs i) 1))]
                  [x (if (= val 1) 1 -1)])
             (> 0 (* i x)))) clause))

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

(define (next-generation population problem population-size)
  (let ([population (sort population (lambda (i j)
                                       (< (car i) (car j))))])
    (if (zero? (caar population))
        (list (car population))        
        (let* ([p (take population (/ population-size 2))] [parents (get-parents p)])
          (append p (map (lambda (i)
                           (crossover (cadr (car i)) (cadr (cadr i)) problem)) parents) 
                  (map (lambda (i)
                         (crossover (cadr (cadr i)) (cadr (car i)) problem)) parents))))))

(define (solve max-iterations problem size atom-number)
  (let* ([population-size (+ size (- 4 (modulo size 4)))]
         [population (generate-random-population population-size atom-number problem)]
         [i 0])
    (let f ([i i] [p population])
      (if (= (length p) 1) ;; solution trouvée
          (car p)
          (if (eq? max-iterations i) ;;nombre d'itérations atteint
              (car p)
              (f (add1 i) (next-generation p problem population-size)))))))

(define (main args)
  (let* ([p (read-file (open-input-file (vector-ref args 0) #:mode 'binary))]
         [atom-number (car p)]
         [clause-number (cadr p)]
         [size (string->number (vector-ref args 1))]
         [max-iterations (string->number (vector-ref args 2))]
         [problem (caddr p)])
    (solve max-iterations problem size atom-number)))

(time (main (current-command-line-arguments)))
;(time (main #("/home/noe/dev/fac/algo_exploration_mouvement/uf20-0912.cnf" "120" "100")))
