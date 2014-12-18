#lang racket
(require "heap.rkt")

;(define frequences (make-vector 256 0))
(define dictionnary '())

(define (make-frequences in)
  (let f ([in in] [frequences (make-vector 256 0)])
    (let ((x (read-char in)))
      (if (eof-object? x)
          frequences
          (let ((n (char->integer x)))
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

(define (make-huffman l)
  (display l)
  (let f ([l l])
    (if (eq? (length l) 2)
        (make-node (+ (car (car l)) (car (cadr l))) '() (car l) (cadr l))
        (begin
          (f (append (cddr l) (list (make-node (+ (car (car l)) (car (cadr l))) '() (car l) (cadr l)))))))))

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
    (open-input-string "salut tout le monde")))))