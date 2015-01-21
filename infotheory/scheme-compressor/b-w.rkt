#lang racket

(require "heap.rkt")

(define (bwt s)
  (let ([heap (make-heap (string-length s) (lambda (x y) (char<? (car x) (car y))))] [size (string-length s)])
    (for ([i (in-range size)])
      (insert heap (list (string-ref s i) (string-ref s (modulo (- (+ i size) 1) size)) i)))
    (last-column (sort-heap heap))))

(define (last-column vec)
  (let ([v (make-vector (vector-length vec))] [indexes (make-vector (vector-length vec))])
   ; (displayln vec)
    (for ([i (in-range (vector-length vec))])
      ;(displayln (vector-ref vec i))
      (let ([c (cdr (vector-ref vec i))])
        (vector-set! v i (car c))
        (vector-set! indexes i (cadr c))))
    ;(displayln indexes)
    (list->string (vector->list v))))


(bwt "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris quis metus nunc. Integer id pretium urna. Nulla malesuada sapien at odio fermentum, vitae ornare tortor accumsan. Aliquam maximus lacinia quam, sed posuere lorem commodo nec. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Duis at consectetur nisl. Donec at tortor erat. Nam dictum sapien sed sapien dignissim, id rutrum dui lobortis. Aliquam erat volutpat. Pellentesque pellentesque enim a tortor commodo sodales. In dapibus neque leo, id pretium sem vulputate ut.

Vestibulum condimentum porta ipsum nec maximus. Nunc a eros sapien. Sed convallis sem mi, in condimentum sapien euismod ac. Interdum et malesuada fames ac ante ipsum primis in faucibus. Proin viverra ligula nisi, eget tincidunt libero rutrum nec. Nullam aliquet varius erat at accumsan. Aenean laoreet purus a lacus feugiat, et semper ex blandit. Phasellus fermentum dui purus, ac dapibus neque condimentum non.

In at lobortis lorem. Sed lacinia accumsan felis, a sollicitudin ex blandit a. Pellentesque ac ex vitae lectus consectetur accumsan. Etiam metus nulla, accumsan in velit eu, varius lacinia arcu. Curabitur at mauris a dolor efficitur faucibus. Cras tortor lectus, rutrum vitae ipsum nec, feugiat faucibus enim. Nunc ut leo condimentum, sodales libero sed, congue lectus. Nunc mollis turpis est, vitae suscipit diam scelerisque semper. Phasellus non viverra nisi. Donec aliquet viverra porttitor. Aliquam neque neque, placerat non urna ac, sagittis fringilla mauris.

Aenean et tellus sit amet erat sagittis hendrerit. Fusce efficitur vel urna nec fermentum. Vivamus tempus maximus nisl molestie dictum. Phasellus et mi malesuada, lacinia est blandit, consectetur risus. Integer fringilla rutrum justo nec imperdiet. Integer viverra nisi id fermentum fringilla. Cras at elit quis ipsum varius ultrices quis non nunc. Nulla scelerisque justo augue, eget dignissim nibh venenatis sodales. Donec eu auctor dui, dictum porttitor eros. Vestibulum vulputate, neque vel fringilla rutrum, elit felis ultrices metus, ut pulvinar elit tellus non libero. Phasellus vulputate turpis risus, sed sollicitudin odio pretium a. Aenean sodales vulputate augue sed condimentum. Praesent imperdiet erat eu augue semper dignissim.

Cras tortor lorem, mollis quis vestibulum sed, maximus eget urna. Proin eu est eget massa tempus interdum. Aenean arcu orci, gravida ac risus sit amet, dignissim auctor ex. Cras commodo urna in volutpat euismod. Ut finibus enim sapien, nec luctus diam interdum ac. Suspendisse et leo feugiat, placerat massa et, facilisis neque. Vestibulum varius, felis vel laoreet rutrum, augue elit molestie leo, quis egestas sem neque nec orci.")