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

(compress-file "/home/noe/Téléchargements/sublime-text_build-3065_amd64.deb" "/home/noe/Téléchargements/out.bin")
(display "compressed")
(decompress-file "/home/noe/Téléchargements/out.bin" "/home/noe/Téléchargements/out.txt")