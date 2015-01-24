#lang racket

(define (move-to-front s)
  (let ([l  (create-list)])
    (map (lambda (i)
           (let ([x (- 256 (length (member i l)))])
             (set! l (append (list i) (remove i l))) x)) s)))

(define (create-list)
  (let f ([i 0] [l '()])
    (if (eq? i 256)
        l
        (f (+ 1 i) (append l (list i))))))

(move-to-front (bytes->list(string->bytes/utf-8 "bananaaa")))