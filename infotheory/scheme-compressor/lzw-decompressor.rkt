#lang racket

(require "utils.rkt")

(define (decompress in out)
  (let ([encoding-length (read-byte in)])
    (let ([data (read-lzw in encoding-length '())])
      (let f (
              [dico (init-dico encoding-length)]
              [data (read-lzw in encoding-length (drop data encoding-length))]
              [size 256]
              [w (list (to-integer (take data encoding-length)))])
        (if (empty? data)
            (void)
            (let ([x (to-integer (take data encoding-length))])
              (if (< x size)
                  (let ([entry (vector-ref dico x)])
                    (display w)
                    (write-result entry out)
                    (vector-set! dico size (append w (car w)))
                    (f dico (read-lzw in encoding-length (drop data encoding-length)) (+ 1 size) entry))
                  (let ([entry (append w (list (car w)))])
                    (display w)
                    (write-result entry out)
                    (vector-set! dico size entry)
                    (f dico (read-lzw in encoding-length (drop data encoding-length)) (+ 1 size) entry)))))))))

(define (write-result result out)
  (display result)
  (let f ([result result])
    (if (empty? result)
        (void)
        (begin
          (write-char (integer->char (car result)))
          (f (cdr result))))))

(define (read-lzw in encoding-length old)
  (let f ([x (read-byte in)])
    (if (eof-object? x)
        '()
        (let ([l (append old (to-binary (read-byte in)))])
          (if (<= encoding-length (length l))
              l
              (read-lzw in encoding-length l))))))

(define (init-dico encoding-length)
  (let ([dico (make-vector (expt 2 encoding-length) 0)])
    (for ([i (in-range 256)])
      (vector-set! dico i (list i)))
    dico))

(decompress (open-input-file "/home/noe/Téléchargements/out.bin" #:mode 'binary) (open-output-file "/home/noe/Téléchargements/out.txt" #:mode 'binary #:exists 'replace))