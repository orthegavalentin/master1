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

(define (make-avg-list in)
  (let f ([data '()])
    (let ([x (read-line in)])
      (if (eof-object? x)
          data
          (let ([x (string-split x " ")])
          (f (cons (cons (string->number (car x)) (cadr x)) data)))))))

(define (to-mosaique img dictionnary size)
  (define (find-closest-avg avg dictionnary)
    (let ([val (car dictionnary)])
      (when (andmap (λ (i)
                (cond [(> (car i) avg) (set! val i) #f]
                      [else #t])) (cdr dictionnary)) (set! val (car (reverse dictionnary))))
      val))
  
  (let ([dictionnary (sort dictionnary (λ (i j)
                                         (< (car i) (car j))))]
        [w (image-width img)]
        [h (image-height img)])
    (let ([out (image w h (init-matrix w h))])
      (for* ([i (build-list (/ (image-width out) size) (λ (i) (* i size)))]
             [j (build-list (/ (image-height out) size) (λ (i) (* i size)))])
        (let* ([avg (at (image-data img) i j)]
               [closest (find-closest-avg avg dictionnary)]
               [small-img (to-smaller-size (read-image (cdr closest)) 64)])
          (for* ([x (in-range size)]
                 [y (in-range size)])
            (set-matrix! (image-data img) (+ x i) (+ y j) (at (image-data small-img) x y)))))))
  img)

(write-image "out.pgm" (to-mosaique (to-pixel-size (read-image "test.pgm") 8) (make-avg-list (open-input-file "out.txt")) 8))
