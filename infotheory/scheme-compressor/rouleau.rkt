#lang racket

(require "lzw-compressor.rkt")
(require "lzw-decompressor.rkt")
(require "huffman.rkt")

(define (compress-file input output)
  (compress
   (open-input-file input #:mode 'binary)
   (open-output-file "temp.bin" #:mode 'binary #:exists 'replace))
  
  (h-compress (open-input-file "temp.bin" #:mode 'binary)
              (open-input-file "temp.bin" #:mode 'binary)
              (open-output-file output #:mode 'binary #:exists 'replace))
  (delete-file "temp.bin"))

(define (decompress-file input output)
  (h-decompress (open-input-file input #:mode 'binary)            
                (open-output-file "temp.bin" #:mode 'binary #:exists 'replace))
  (decompress 
   (open-input-file "temp.bin" #:mode 'binary)
   (open-output-file output #:mode 'binary #:exists 'replace))
  (delete-file "temp.bin"))

(define (display-help)
  (displayln "rouleau -c[ompress] input_file output_file")
  (displayln "rouleau -d[ecompress] input_file output_file"))

(define (main)
  (let ([args (current-command-line-arguments)])
    (cond
      [(< (vector-length args) 3) (display-help)]
      [(or
        (equal? (vector-ref args 0) "-c")
        (equal? (vector-ref args 0) "-compress"))
       (compress-file (vector-ref args 1) (vector-ref args 2))]
      [(or
        (equal? (vector-ref args 0) "-d")
        (equal? (vector-ref args 0) "-decompress"))
       (decompress-file (vector-ref args 1) (vector-ref args 2))]
      [else (display-help)])))

;(main)

(compress-file "/home/noe/Téléchargements/test.txt" "/home/noe/Téléchargements/out.bin")
(decompress-file "/home/noe/Téléchargements/out.bin" "/home/noe/Téléchargements/out.txt")