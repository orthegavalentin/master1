#lang racket

(define encoding-length 12)

(define (compress in)
  (let ([dico (init-dico)] [result '()] [w '()] [index 256])
    (let f ([in in] [dico dico] [result result] [w w] [index index])
      (let ((x (read-byte in)))
        (if (eof-object? x)
            result
            (begin
              (let ((temp (pair w x)))
                (if (hash-has-key? dico temp)
                    (f in dico result temp index)
                    (begin
                      (hash-set! dico temp index)
                      (let ([result (append result (binary-with-encoding-length
                                                    (to-binary (hash-ref dico w))))] [w (list x)])
                        
                        (if (eq? (hash-count dico) (expt 2 encoding-length))
                            (f in (init-dico) result w 256)
                            (f in dico result w (+ 1 index)))))))))))))

(define (to-binary n)
  (let div ([n n])
    (let ([n n] [rest (modulo n 2)])
      (if (equal? (- n rest) 0)
          (list rest)
          (append (div (/ (- n rest) 2)) (list rest))))))

(define (binary-with-encoding-length l)
  (append (make-list (- encoding-length (length l)) 0)  l))

(define (pair x y)
  (append x (list y)))

(define (init-dico)
  (let ([dico (make-hash)] [i 0])
    (let f ((i i))
      (if (eq? i 256)
          dico
          (begin 
            (hash-set! dico (list i) i)
            (f (+ 1 i)))))))

(define res (compress (open-input-file "/home/noe/Téléchargements/comp.txt")))
(ceiling (/ (length res) 8))