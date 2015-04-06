#lang racket/gui

(provide image)
(provide image-width)
(provide image-height)
(provide image-data)
(provide read-image)
(provide write-image)
(provide at)
(provide init-matrix)
(provide set-matrix!)

(struct image (width height data) #:transparent)

(define (read-size in)
  (let f ()
    (let ([x (read-line in)])
      (if (or (< (string-length x) 2) (equal? (string-ref x 0) #\#))
          (f)
          (map string->number (string-split x " "))))))

(define (at matrix x y)
  (vector-ref (vector-ref matrix x) y))

(define (set-matrix! matrix x y v)
  (vector-set! (vector-ref matrix x) y v))

(define (init-matrix width height)
  (let ([v (make-vector width 0)])
    (vector-map (λ (i)
                  (make-vector height 0)) v)))

(define (read-image path)
  (let ([in (open-input-file path #:mode 'binary)])
    (unless (string=? (read-line in) "P5")
      (error "incorrect file type"))
    (let* ([size (read-size in)])
      (read-line in)
      (let ([img (image
                  (car size)
                  (cadr size)
                  (init-matrix (car size) (cadr size)))])
        (let f ([i 0] [j 0])
          (let ([x (read-byte in)])
            (cond [(eof-object? x)
                   (close-input-port in)
                   img]
                  [else (set-matrix! (image-data img) i j x)
                        (if (= j (- (cadr size) 1))
                            (f (+ 1 i) 0)
                            (f i (+ 1 j)))])))))))
  
  (define (write-image path image)
    (let ([out (open-output-file path #:mode 'binary #:exists 'replace)])
      (write-string "P5\n" out)
      (write-string (~a (image-width image) " " (image-height image) "\n") out)
      (write-string "255\n" out)
      (for* ([i (image-width image)]
             [j (image-height image)])
        (write-byte (at (image-data image) i j) out))
      (close-output-port out)))