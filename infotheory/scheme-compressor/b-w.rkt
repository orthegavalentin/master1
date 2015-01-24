#lang racket

(require "heap.rkt")



(define (bwt s)
  (letrec ([size (string-length s)] [heap (make-heap size (lambda (x y) (string<? (car x) (car y))))])
    (for ([i (in-range size)])
      (insert heap (list (string-join (list (substring s i (string-length s)) (substring s 0 i)) "") i)))
    (last-column (sort-heap heap))))

(define (last-column vec)
  (list->bytes (vector->list (vector-map (lambda (i)
                (when (eq? (cadr i) 0)
                  (display (vector-member i vec)))
                (char->integer (string-ref (car i) (- (string-length (car i)) 1)))) vec))))
  

(define (make-precedings s)
  (let ([v (make-vector 256 0)])
    (list->vector (map (lambda (i)
                         (vector-set! v i (+ 1 (vector-ref v i)))
                         (list i (- (vector-ref v i) 1)))
                       s))))

(define (make-less-than s)
  (let ([sorted (sort-data s)] [lt (make-vector 256 -1)])
    (for ([i (in-range (vector-length sorted))])
      (let ([x (vector-ref sorted i)])
        (when (eq? (vector-ref lt x) -1)
          (vector-set! lt x i))))
    lt))

(define (sort-data s)
  (let ([heap (make-heap (length s) <)])
    (let f ([s s])
      (if (empty? s)
          (sort-heap heap)
          (begin
            (insert heap (car s))
            (f (cdr s)))))))

(define (reverse-bwt s first)
  (let ([prec (make-precedings s)] [lt (make-less-than s)])
    (let f ([reversed '()] [last first])
      (if (eq? (length s) (length reversed))
          (list->bytes reversed)
          (letrec ([x (vector-ref prec last)]
                   [current (+ (cadr x) (vector-ref lt (car x)))])
            (let ([last-char (vector-ref prec last)])
              (vector-set! prec last (list (car last-char) (- (cadr last-char) 1))))
            (f (append (list (car x)) reversed) current))))))

(bwt "this is a test.")
(reverse-bwt (bytes->list(string->bytes/utf-8 "ssat tt hiies .")) 14)
