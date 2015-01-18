#lang racket
(require "heap.rkt")
(require "utils.rkt")

(define (make-frequences in)
  (let f ([frequences (make-vector 256 0)])
    (let ((x (read-byte in)))
      (if (eof-object? x)
          frequences
          (let ((n x))
            (vector-set! frequences n (+ (vector-ref frequences n) 1))
            (f frequences))))))

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

(define (get-encoding-length frequences)
  (let ([m (vector-ref frequences 0)])
    (for ([i (in-range 256)])
      (set! m (max (vector-ref frequences i) m)))
    (inexact->exact (* 8 (ceiling (/ (/ (log m) (log 2)) 8))))))

(define (export-dico frequences encoding-length out)
  (write-result (binary-with-encoding-length (to-binary encoding-length) 8) out)
  (for ([i (in-range 256)])
    (if (> (vector-ref frequences i) 0)
           (begin
             (write-result (binary-with-encoding-length (to-binary i) 8) out)
             (write-result (binary-with-encoding-length (to-binary (vector-ref frequences i)) encoding-length) out))
           (void)))
  (write-result (binary-with-encoding-length (to-binary 0) (+ encoding-length 8)) out))

(define (write-result l out)
  (if (> 8 (length l))
      l
      (let ((n (to-integer (take l 8))))
        (write-bytes (bytes n) out)
        (write-result (drop l 8) out)))) 

(define (read-frequence in encoding-length)
  (let f ([data (binary-with-encoding-length (to-binary (read-byte in)) 8)])
    (if (= (length data) encoding-length)
        (to-integer data)
        (f (append data (binary-with-encoding-length (to-binary (read-byte in)) 8))))))

(define (parse-dico in)
  (let ([in (open-input-file in #:mode 'binary)])
  (let ([encoding-length (read-byte in)] [frequences (make-vector 256 0)])
    (let f ()
          (let ([index (read-byte in)] [freq (read-frequence in encoding-length)])
            (if (and (= 0 index) (= 0 freq))
                frequences
                (begin
                  (vector-set! frequences index freq)
                  (f))))))))

(define (compress in out)
  (let ([frequences (make-frequences (open-input-file in #:mode 'binary))])
    (let ([dico (make-dictionnary 
                 (make-huffman 
                  (sort-frequences 
                   frequences)))])
      (pretty-display dico))
    (newline)
    (displayln frequences)
    (let ([out (open-output-file out #:mode 'binary #:exists 'replace)])
      (export-dico frequences (get-encoding-length frequences) out)
      (close-output-port out))))

(compress "/home/noe/Téléchargements/test1.txt" "/home/noe/Téléchargements/out.bin")
(newline)
(display (parse-dico "/home/noe/Téléchargements/out.bin"))