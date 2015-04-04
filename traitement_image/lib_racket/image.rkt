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
      (if (equal? (string-ref x 0) #\#)
          (f)
          (map string->number (string-split x " "))))))

(define (read-data in)
  (let f ([data '()])
    (let ([x (read-byte in)])
      (if (eof-object? x)
          data
          (f (cons x data))))))

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
      (image (car size)
             (cadr size)
             (list->vector (map list->vector (foldl (λ (i l)
                                                      (if (= (length (car l)) (car size))
                                                          (cons `(,i) l)
                                                          (cons (cons i (car l)) (cdr l)))) '(()) (read-data in))))))))

(define (write-image path image)
  (let ([out (open-output-file path #:mode 'binary #:exists 'replace)])
    (write-string "P5\n" out)
    (write-string (~a (image-width image) " " (image-height image) "\n") out)
    (write-string "255\n" out)
    (for* ([i (image-width image)]
           [j (image-height image)])
      (write-byte (at (image-data image) i j) out))))