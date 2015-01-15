#lang racket
(require "heap.rkt")
(require "utils.rkt")

(define (make-frequences in)
  (let f ([in in] [frequences (make-vector 256 0)])
    (let ((x (read-byte in)))
      (if (eof-object? x)
          frequences
          (let ((n x))
            (vector-set! frequences n (+ (vector-ref frequences n) 1))
            (f in frequences))))))

(define (sort-frequences frequences)
  (let f ((l '()) (i 0))
    (if (eq? i (vector-length frequences))
        (map (lambda (x)
               (make-node (cadr x) (car x) '() '()))
             (sort l (lambda (x y)
                       (< (cadr x) (cadr y)))))
        (if (eq? (vector-ref frequences i) 0)
            (f l (+ i 1))
            (f (append l (list (list i (vector-ref frequences i)))) (+ i 1))))))

(define (make-huffman-heap l)
  (let ((v (make-heap (length l) (lambda (x y) (< (car x) (car y))))))
    (let f ((l l))
      (if (empty? l)
          v
          (begin
            (insert v (car l))
            (f (cdr l)))))))

(define (make-huffman l)
  (let f ([v (make-huffman-heap l)])
    (if (eq? (size v) 2)
        (first v)
        (let ([right (first-and-remove v)] [left (first-and-remove v)])
          (insert v (make-node (+ (car right) (+ (car left))) '() left right))
          (f v)))))

(define (make-node freq char left right)
  (list freq char left right))

(define (make-dictionnary huffman)
  (let f ((huffman huffman) (s '()))
    (if (empty? (caddr huffman))
        (list (list (cadr huffman) s))
        (begin
          (append (f (cadddr huffman) (append s '(1))) (f (caddr huffman) (append s '(0))))))))

(define (get-encoding-length dico)
  (let f ([dico (cdr dico)] [max (length (car (cdar dico)))])
    (if (empty? dico)
        max
        (let ([size (length (car (cdar dico)))])
          (if (< max size)
              (f (cdr dico) size)
              (f (cdr dico) max))))))

(define (export-dico dico max-size out)
  (write-bytes (bytes max-size) out)
  (let f ([dico dico] [data '()])
    (if (empty? dico)
        (void)
        (let ([current (car dico)])
          (let ([new-data (append (to-binary (car current)) (binary-with-encoding-length (cadr current) max-size))])
            (let ([data (write-result (append data new-data) out)])
              (f (cdr dico) data)))))))

(define (write-result l out)
  (if (> 8 (length l))
      l
      (let ((n (to-integer (take l 8))))
        (write-bytes (bytes n) out)
        (write-result (drop l 8) out)))) 

(define (parse-dico in)
  (let ([size (read-byte in)])
    

(define (compress in out)
  (let ([dico (make-dictionnary 
               (make-huffman 
                (sort-frequences 
                 (make-frequences (open-input-file in)))))])
    (pretty-display dico)
    (let ([out (open-output-file out #:mode 'binary #:exists 'replace)])
      (export-dico dico (get-encoding-length dico) out)
      (close-output-port out))))

(compress "/home/noe/Téléchargements/test1.txt" "/home/noe/Téléchargements/out.bin")