#lang racket
(require "heap.rkt")

(define (make-frequences in)
  (let f ([in in] [frequences (make-vector 256 0)])
    (let ((x (read-byte in)))
      (if (eof-object? x)
          frequences
          (let ((n x))
            (vector-set! frequences n (+ (vector-ref frequences n) 1))
            (f in frequences))))))

(define (sort-frequences frequences)
  (let ([l '()] [i 0])
    (let f ((l l) (i i))
      (if (eq? i (vector-length frequences))
          (map (lambda (x)
                 (make-node (cadr x) (car x) '() '()))
               (sort l (lambda (x y)
                         (< (cadr x) (cadr y)))))
          (if (eq? (vector-ref frequences i) 0)
              (f l (+ i 1))
              (f (append l (list (list i (vector-ref frequences i)))) (+ i 1)))))))

(define (make-huffman-heap l)
  (let ((v (make-heap (length l) (lambda (x y) (< (car x) (car y))))))
    (let f ((l l))
      (if (empty? l)
          v
          (begin
            (insert v (car l))
            (f (cdr l)))))))

(define (make-huffman l)
  (let ((v (make-huffman-heap l)))
    (let f ([v v])
      (if (eq? (size v) 2)
          (first v)
          (let ([right (first-and-remove v)] [left (first-and-remove v)])
            (insert v (make-node (+ (car right) (+ (car left))) '() left right))
            (f v))))))

(define (make-node freq char left right)
  (list freq char left right))

(define (make-dictionnary huffman)
  (let f ((huffman huffman) (s '()))
    (if (empty? (caddr huffman))
        (list (list (cadr huffman) s))
        (begin
          (append (f (cadddr huffman) (append s '(1))) (f (caddr huffman) (append s '(0))))))))

(make-dictionnary 
 (make-huffman 
  (sort-frequences 
   (make-frequences 
    (open-input-file "/home/noe/Téléchargements/ecranoffline.png")))))