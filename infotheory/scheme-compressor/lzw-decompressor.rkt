#lang racket

(require "utils.rkt")

(provide decompress)

(define (decompress in out)
  (let ([encoding-length (read-byte in)])
    (let ([data (read-lzw in encoding-length '())])
      (let f ([dico (init-dico encoding-length)]
              [data data]
              [size 255]
              [w (list (to-integer (take data encoding-length)))])
        (if (empty? data)
            (close-output-port out)
            (let ([x (to-integer (take data encoding-length))] [size (if (>= size (expt 2 encoding-length)) 255 size)])
              (if (< x size)
                  (let ([entry (vector-ref dico x)])
                    (write-result entry out)
                    (vector-set! dico size (append w (list (car entry))))
                    (f dico (read-lzw in encoding-length (drop data encoding-length)) (+ 1 size) entry))
                  (let ([entry (append w (list (car w)))])
                    (write-result entry out)
                    (vector-set! dico size entry)
                    (f dico (read-lzw in encoding-length (drop data encoding-length)) (+ 1 size) entry)))))))))

(define (write-result result out)
  (write-bytes (list->bytes result) out))

(define (read-lzw in encoding-length old)
  (if (<= encoding-length (length old))
      old
      (let f ([x (read-byte in)])
        (if (eof-object? x)
            '()
            (let ([l (append old (binary-with-encoding-length (to-binary x) 8))])
              (read-lzw in encoding-length l))))))

(define (init-dico encoding-length)
  (let ([dico (make-vector (expt 2 encoding-length) 0)])
    (for ([i (in-range 256)])
      (vector-set! dico i (list i)))
    dico))