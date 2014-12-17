#lang racket

(define frequences (make-vector 256 0))

(define (make-frequences in)
  (let f ([in in])
    (let ((x (read-char in)))
      (if (eof-object? x)
          (void)
          (let ((n (char->integer x)))
            (vector-set! frequences n (+ (vector-ref frequences n) 1))
            (f in))))))

(define (sort-frequences)
  (let ([l '()] [i 0])
    (let f ((l l) (i i))
      (if (eq? i (vector-length frequences))
          (sort l
                (lambda (x y)
                  (< (cadr x) (cadr y))))
          (if (eq? (vector-ref frequences i) 0)
              (f l (+ i 1))
              (f (append l (list (list i (vector-ref frequences i)))) (+ i 1)))))))

(define (make-huffman l)
  (let f ([l l])
    (if (eq? (length l) 1)
        l
        (f (cons (list (cons 1 (car l)) (cons 0 (cadr l))) (cddr l))))))



(make-frequences (open-input-string "sosa"))
(display frequences)
(newline)
(define huffman (make-huffman (sort-frequences)))
(display huffman)