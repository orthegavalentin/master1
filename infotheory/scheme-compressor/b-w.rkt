#lang racket

(require "heap.rkt")

(define (bwt s)
  (let ([heap (make-heap (string-length s) (lambda (x y) (char<? (car x) (car y))))] [size (string-length s)])
    (for ([i (in-range size)])
      (insert heap (list (string-ref s i) (string-ref s (modulo (- (+ i size) 1) size)) i)))
    (last-column (sort-heap heap))))

(define (last-column vec)
  (let ([v (make-vector (vector-length vec))] [indexes (make-vector (vector-length vec))])
    (displayln vec)
    (for ([i (in-range (vector-length vec))])
      (displayln (vector-ref vec i))
      (let ([c (cdr (vector-ref vec i))])
        (vector-set! v i (car c))
        (vector-set! indexes i (cadr c))))
    (displayln indexes)
    (list->string (vector->list v))))


(bwt "abca")