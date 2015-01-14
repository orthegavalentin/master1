#lang racket

(require "lzw-compressor.rkt")
(require "lzw-decompressor.rkt")


(compress
 (open-input-file "/home/noe/Téléchargements/ACSI.ods" #:mode 'binary)
 (open-output-file "/home/noe/Téléchargements/out.bin" #:mode 'binary #:exists 'replace))

(decompress 
 (open-input-file "/home/noe/Téléchargements/out.bin" #:mode 'binary)
 (open-output-file "/home/noe/Téléchargements/out.ods" #:mode 'binary #:exists 'replace))
