#lang racket
(require "../lib_racket/image.rkt")

(define (avg-of-area img x y sizex sizey)
  (define avg 0)
  (for* ([i (in-range sizex)]
         [j (in-range sizey)])
    (set! avg (+ avg (at (image-data img) (+ x i) (+ y j)))))
  (round (/ avg (* sizex sizey))))

(define (to-smaller-size img sizex sizey)
  (let* ([w (/ (image-width img) sizex)] [h (/ (image-height img) sizey)])
    (let ([out (image w h (init-matrix w h))])
      (for* ([i (build-list (image-width out) (λ (i) (* i sizex)))]
             [j (build-list (image-height out) (λ (i) (* i sizey)))])
        (set-matrix! (image-data out) (/ i sizex) (/ j sizey) (avg-of-area img i j sizex sizey)))
      out)))

(define (to-pixel-size img sizex sizey)
  (let ([w (image-width img)] [h (image-height img)])
    (let ([out (image w h (init-matrix w h))])
      (for* ([i (build-list (/ (image-width out) sizex) (λ (i) (* i sizex)))]
             [j (build-list (/ (image-height out) sizey) (λ (i) (* i sizey)))])
        (let ([avg (avg-of-area img i j sizex sizey)])
          (for* ([x (in-range sizex)]
                 [y (in-range sizey)])
            (set-matrix! (image-data out) (+ x i) (+ y j) avg))))
      out)))

(define (make-avg-list in)
  (let f ([data '()])
    (let ([x (read-line in)])
      (if (eof-object? x)
          data
          (let ([x (string-split x " ")])
          (f (cons (cons (string->number (car x)) (cadr x)) data)))))))

(define (to-mosaique path dictionnary sizex sizey)
  (let ([img (to-pixel-size (read-image path) sizex sizey)])
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
        (for* ([i (build-list (/ (image-width out) sizex) (λ (i) (* i sizex)))]
               [j (build-list (/ (image-height out) sizey) (λ (i) (* i sizey)))])
          (let* ([avg (at (image-data img) i j)]
                 [closest (find-closest-avg avg dictionnary)]
                 [small-img (to-smaller-size (read-image (cdr closest)) (/ (image-width out) sizex) (/ (image-height out) sizey))])
            (for* ([x (in-range sizex)]
                   [y (in-range sizey)])
              (set-matrix! (image-data img) (+ x i) (+ y j) (at (image-data small-img) x y)))))))
    img))

(define (main args)
  (write-image "out.pgm" (to-mosaique (vector-ref args 0) (make-avg-list (open-input-file (vector-ref args 1))) (string->number (vector-ref args 2)) (string->number (vector-ref args 3)))))

(main (current-command-line-arguments))
