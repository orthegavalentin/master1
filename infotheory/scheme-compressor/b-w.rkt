#lang racket

(require "heap.rkt")
(require "utils.rkt")

(provide c-bwt)
(provide d-bwt)
(provide get-index)

(define (bwt s)
  (letrec ([size (length s)] [v (make-vector size)])
    (for ([i (in-range size)])
      (vector-set! v i i))
    (last-column (sort (vector->list v) (lambda (x y) (compare x y s size))) s size)))

(define (compare x y l size)
  (let f ([x x] [y y])
    (if (eq? (* 2 size) x)
        #f
        (let ([x-byte (list-ref l (modulo x size))] [y-byte (list-ref l (modulo y size))])
          (if (eq? x-byte y-byte)
              (f (+ 1 x) (+ 1 y))
              (< x-byte y-byte))))))

(define (last-column l s size)
  (let ([index 0])
    (list (map (lambda (i)
                 (when (eq? i 0)
                   (set! index (- size (length (member i l)))))
                 (list-ref s (modulo (- (+ i size) 1) size))) l) index)))

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

(define (write-result l out)
  (if (> 8 (length l))
      l
      (let ((n (to-integer (take l 8))))
        (write-bytes (bytes n) out)
        (write-result (drop l 8) out)))) 

(define (read-file in)
  (bytes->list (port->bytes in)))

(define (get-index in)
  (let ([size (read-byte in)])
    (let f ([data '()])
      (if (eq? (length data) size)
          (to-integer data)
          (f (append data (binary-with-encoding-length (to-binary (read-byte in)) 8)))))))

(define (c-bwt in out)
  (letrec ([x (bwt (read-file in))] [index (cadr x)] [size (if (= 0 index) 8 (inexact->exact (* 8 (ceiling (/ (integer-length index) 8)))))])
    (write-byte size out)
    (write-result (binary-with-encoding-length (to-binary index) size) out)
    (car x)))

(define (d-bwt out s index)
  (write-bytes (reverse-bwt s index) out)
  (close-output-port out))

(c-bwt (open-input-file "/home/noe/Téléchargements/test.txt" #:mode 'binary) (current-output-port))