#lang racket

(require "heap.rkt")

(define (bwt s)
  (let ([heap (make-heap (string-length s) (lambda (x y) (char<? (car x) (car y))))] [size (string-length s)])
    (for ([i (in-range size)])
      (insert heap (list (string-ref s i) (string-ref s (modulo (- (+ i size) 1) size)) i)))
    (last-column (sort-heap heap))))

(define (last-column vec)
  (let ([v (make-vector (vector-length vec))] [indexes (make-vector (vector-length vec))])
    ; (displayln vec)
    (for ([i (in-range (vector-length vec))])
      ;(displayln (vector-ref vec i))
      (let ([c (cdr (vector-ref vec i))])
        (vector-set! v i (car c))
        (vector-set! indexes i (cadr c))))
    ;(displayln indexes)
    (list->string (vector->list v))))

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

(define (reverse-bwt s)
  (let ([prec (make-precedings s)] [lt (make-less-than s)] [first 14])
    (let f ([reversed '()] [last first])
      (if (eq? (length s) (length reversed))
          (list->bytes reversed)
          (letrec ([x (vector-ref prec last)]
                   [current (+ (cadr x) (vector-ref lt (car x)))])
            (let ([last-char (vector-ref prec last)])
              (vector-set! prec last (list (car last-char) (- (cadr last-char) 1))))
            (f (append (list (car x)) reversed) current))))))

(bwt "this is a test.")
(reverse-bwt (bytes->list(string->bytes/utf-8 "ssat tt hiies .")))
