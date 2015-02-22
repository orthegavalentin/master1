#lang racket

(provide read-file)

(define (make-clauses in)
  (let f ([data '()])
    (let ([line (read-line in)])
      (if (or (eof-object? line) (string=? line "%"))
          data
          (f (append data (list (map string->number (take (string-split line " ") 3)))))))))


(define (read-file in)
  (let f ()
    (let ([line (read-line in)])
      (if (or (eof-object? line) (eq? (string-ref line 0) #\c))
          (f)
          (let ([l (string-split line)])
            (list (string->number (caddr l)) (string->number (cadddr l)) (make-clauses in)))))))