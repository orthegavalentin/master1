#lang racket
(require "../lib_racket/image.rkt")

(define (avg-of-area img x y size)
  (define avg 0)
  (for* ([i (in-range size)]
         [j (in-range size)])
    (set! avg (+ avg (at (image-data img) (+ x i) (+ y j)))))
  (round (/ avg (* size size))))

(define (to-smaller-size img size)
  (let* ([w (/ (image-width img) size)] [h (/ (image-height img) size)])
    (let ([out (image w h (init-matrix w h))])
      (for* ([i (build-list (image-width out) (λ (i) (* i size)))]
             [j (build-list (image-height out) (λ (i) (* i size)))])
        (set-matrix! (image-data out) (/ i size) (/ j size) (avg-of-area img i j size)))
      out)))

(define (to-pixel-size img size)
  (let ([w (image-width img)] [h (image-height img)])
    (let ([out (image w h (init-matrix w h))])
      (for* ([i (build-list (/ (image-width out) size) (λ (i) (* i size)))]
             [j (build-list (/ (image-height out) size) (λ (i) (* i size)))])
        (let ([avg (avg-of-area img i j size)])
          (for* ([x (in-range size)]
                 [y (in-range size)])
            (set-matrix! (image-data out) (+ x i) (+ y j) avg))))
      out)))

(write-image "out.pgm" (to-pixel-size (read-image "lena.pgm") 16))