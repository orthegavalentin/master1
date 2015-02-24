#lang racket
(require racket/date)
(require net/url)

(define days (hash "Monday," 0 "Tuesday," 1 "Wednesday," 2 "Thursday," 3 "Friday," 4 "Saturday," 5 "Sunday," 6))
(define subjects (hash "FMIN215\r" "SUMMARY:Algorithmique Géométrique\r"
                       "GMIN20A\r" "SUMMARY:Algorithmique d'exploration et de mouvement\r"
                       "GMIN212\r" "SUMMARY:Modélisation et programmation\r"
                       "GMIN215\r" "SUMMARY:Analyse et traitement d'images\r"
                       "GMIN21C\r" "SUMMARY:Conduite de projets\r"))

#|Proxy pour la fac|#
(current-proxy-servers '(("http" "162.38.218.204" 3128)))

(define (add-days-to-date d n)
  (date-display-format 'iso-8601)
  (date->string (seconds->date (+ (find-seconds 0 0 0 (caddr d) (cadr d) (car d)) (* n 86400))))) 

(define (dates-of-current-week)
  (date-display-format 'iso-8601)
  (let ([today (string-split (date->string (current-date)) "-")])
    (date-display-format 'american)
    (let ([today (map string->number today)]
          [elapsed (hash-ref days (car (string-split (date->string (current-date)) " ")))])
      `(,(add-days-to-date today (- elapsed))
        ,(add-days-to-date today (+ 6 (- elapsed)))))))

(define (make-url-from-bounds bounds)
  (string->url (string-join `("http://www.tom2ade.univ-montp2.fr/jsp/custom/modules/plannings/anonymous_cal.jsp?resources=2471,3161,3213,3216,3299&projectId=12&calType=ical&firstDate="
                              ,(car bounds)
                              "&lastDate="
                              ,(cadr bounds)) "")))

(define (create-new-schedule)
  (let ([p (get-pure-port (make-url-from-bounds (dates-of-current-week)))]
        [out (open-output-file "out.ics" #:mode 'binary #:exists 'replace)])
    (let f ()
      (let ([data (read-line p)])
        (if (eof-object? data)
            (close-output-port out)
            (begin
              (write-string
               (if (string=? (substring data 0 7) "SUMMARY")
                   (hash-ref subjects (cadr (string-split data ":")) data)
                   data)
               out)
              (f)))))))

(create-new-schedule)