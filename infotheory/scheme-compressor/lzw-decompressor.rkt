#lang racket

(require "utils.rkt")

(define (decompress in out)
  (let ([encoding-length (read-byte in)])
    (let f (
    (display encoding-length)))

(define (read-lzw in encoding-length old)
  (let f ([l (append old (to-binary (read-bytes in)))])
    (if (<= (encoding-length (length l)))
        l
        (f (l (to-binary (read-bytes in)))))))
    
(decompress (open-input-file "/home/noe/Téléchargements/out.bin" #:mode 'binary) (void))