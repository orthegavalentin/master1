#lang racket

(provide c-mtf)
(provide d-mtf)

(define (move-to-front s)
  (let ([l  (create-list)])
    (map (lambda (i)
           (let ([x (- 256 (length (member i l)))])
             (set! l (append (list i) (remove i l))) x)) s)))

(define (decode-move-to-front s)
  (let ([l (create-list)])
    (map (lambda (i)
           (let ([x (list-ref l i)])
             (set! l (append (list x) (remove x l))) x)) s)))

(define (create-list)
  (let f ([i 0] [l '()])
    (if (eq? i 256)
        l
        (f (+ 1 i) (append l (list i))))))

(define (read-file in)
    (let f ([data '()])
      (let ([s (read-byte in)])
        (if (eof-object? s)
            data
            (f (append data (list s)))))))

(define (c-mtf l out)
  (write-bytes (list->bytes (move-to-front l)) out)
  (close-output-port out))

(define (d-mtf in)
  (decode-move-to-front (read-file in)))