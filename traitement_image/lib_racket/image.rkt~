#lang racket/gui

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
  (vector-ref (vector-ref matrix y) x))

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

(read-image "./lena.pgm")