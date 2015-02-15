#lang racket
(require "parser.rkt")

(define (convert atom-number clause-number problem out)
  (write-string (~a "E\n" atom-number "\n") out)
  (for ([i (in-range 1 (add1 atom-number))])
    (write-string (~a "a" i ";0;1\n") out))
  (write-string (~a clause-number "\n") out)
  (map (λ (i)
         (let ([x (car i)] [y (cadr i)] [z (caddr i)]
               [f (λ (i)
                    (if (> 0 i) 1 0))])
           (write-string (~a "a" (abs x) ";a" (abs y) ";a" (abs z)
                             "\n1\n" (f x) ";" (f y) ";" (f z) "\n") out))) problem))

(define (main)
  (letrec ([args (current-command-line-arguments)]
           [p (read-file (open-input-file (vector-ref args 0) #:mode 'binary))]
           [out (open-output-file (vector-ref args 1) #:mode 'binary #:exists 'replace)]
           [atom-number (car p)]
           [clause-number (cadr p)]
           [problem (caddr p)])
    (convert atom-number clause-number problem out)))

(main)