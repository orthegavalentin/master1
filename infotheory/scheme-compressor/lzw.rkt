#lang racket

(define encoding-length 16)

(define (compress in out)
  (let ([dico (init-dico)] [result '()] [w '()] [index 256])
    (let f ([in in] [dico dico] [result result] [w w] [index index])
      (let ((x (read-byte in)))
        (if (eof-object? x)
            (begin 
              (write-result result out)
              (close-output-port out))
            (let ((temp (pair w x)))
              (if (hash-has-key? dico temp)
                  (f in dico result temp index)
                  (begin
                    (hash-set! dico temp index)
                    (let ([result (write-result
                                   (append result
                                           (binary-with-encoding-length
                                                  (to-binary (hash-ref dico w)))) out)]
                          [w (list x)])    
                      (if (eq? (hash-count dico) (expt 2 encoding-length))
                          (f in (init-dico) result w 256)
                          (f in dico result w (+ 1 index))))))))))))

(define (write-result l out)
  (if (> 8 (length l))
      l
      (let ((n (to-integer (take l 8))))
        (write-bytes (bytes n) out)
        (write-result (drop l 8) out))))


(define (to-binary n)
  (let div ([n n])
    (let ([n n] [rest (modulo n 2)])
      (if (equal? (- n rest) 0)
          (list rest)
          (append (div (/ (- n rest) 2)) (list rest))))))

(define (to-integer l)
  (let ([n 0] [l (reverse l)] [result 0])
    (let f ([n n] [l l] [result result])
      (if (empty? l)
          result
          (f (+ 1 n) (cdr l) (+ result (* (car l) (expt 2 n))))))))

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

(compress (open-input-file "/home/noe/Téléchargements/ecranoffline.png") (open-output-file "/home/noe/Téléchargements/out.bin" #:mode 'binary #:exists 'replace))