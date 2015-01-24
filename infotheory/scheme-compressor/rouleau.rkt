#lang racket

(require "lzw-compressor.rkt")
(require "lzw-decompressor.rkt")
(require "huffman.rkt")
(require "b-w.rkt")
(require "move-to-front.rkt")

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

(define (compress-bwt input output)
  (let ([output (open-output-file output #:mode 'binary #:exists 'replace)])
    (c-mtf (c-bwt (open-input-file input #:mode 'binary) output) output)))

(define (decompress-bwt input output)
  (letrec ([in (open-input-file input #:mode 'binary)] [index (get-index in)])
    (d-bwt (open-output-file output #:mode 'binary #:exists 'replace) (d-mtf in) index)))

(define (display-help)
  (displayln "rouleau -c[ompress] input_file output_file")
  (displayln "rouleau -d[ecompress] input_file output_file")
  (displayln "rouleau -b[urrows-wheeler] input_file output_file")
  (displayln "rouleau -i[nverse-burrows-wheeler] input_file output_file"))

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
      [(or
        (equal? (vector-ref args 0) "-b")
        (equal? (vector-ref args 0) "-burrows-wheeler"))
       (compress-bwt (vector-ref args 1) (vector-ref args 2))]
      [(or
        (equal? (vector-ref args 0) "-i")
        (equal? (vector-ref args 0) "-inverse-burrows-wheeler"))
       (decompress-bwt (vector-ref args 1) (vector-ref args 2))]
      [else (display-help)])))

;(main)

(compress-bwt "/home/noe/Téléchargements/test.txt" "/home/noe/Téléchargements/out.bin")
(display "compressed")
(decompress-bwt "/home/noe/Téléchargements/out.bin" "/home/noe/Téléchargements/out.txt")