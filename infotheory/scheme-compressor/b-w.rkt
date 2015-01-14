#lang racket

(require "heap.rkt")

(define (bwt s)
  (let ([heap (make-heap (string-length s) (lambda (x y) (char<? (car x) (car y))))] [size (string-length s)])
    (for ([i (in-range size)])
      (insert heap (list (string-ref s i) (string-ref s (modulo (- (+ i size) 1) size)) i)))
    (last-column (sort-heap heap))))

(define (last-column vec)
  (displayln vec)
  (let ([v (make-vector (vector-length vec))])
    (for ([i (in-range (vector-length vec))])
      (displayln (vector-ref vec i))
      (vector-set! v i (cadr (vector-ref vec i))))
    (list->string (vector->list v))))

;(define (reverse-bwt s)

(bwt "this is a test.")