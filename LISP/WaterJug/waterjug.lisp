(defvar x)
(defvar y)
(defvar z)

(defun solve-gcd (a b)
  (if (= b 0)
      a
      (solve-gcd b (mod a b))))

(defun reached-goal (z curx cury)
  (or (= curx z) (= cury z)))

(defun fill-x (x curx)
  x)

(defun fill-y (y cury)
  y)

(defun empty-x ()
  0)

(defun empty-y ()
  0)

(defun pour-x-to-y (x y curx cury)
  (let* ((transfer (min curx (- y cury)))
         (newx (- curx transfer))
         (newy (+ cury transfer)))
    (values newx newy)))

(defun water-jug (x y z)
  (if (or (> z (max x y)) (/= (mod z (solve-gcd x y)) 0))
      (format t "Goal not achievable with given jug sizes.~%")
      (let ((curx 0)
            (cury 0))
        (format t "Initial state: (~A, ~A)~%" curx cury)
        (loop while (not (reached-goal z curx cury))
              do (cond
                   ((= curx 0)
                    (setf curx (fill-x x curx))
                    (format t "Fill X: (~A, ~A)~%" curx cury))
                   ((and (> curx 0) (< cury y))
                    (multiple-value-setq (curx cury) (pour-x-to-y x y curx cury))
                    (format t "Pour X->Y: (~A, ~A)~%" curx cury))
                   ((= cury y)
                    (setf cury (empty-y))
                    (format t "Empty Y: (~A, ~A)~%" curx cury))))
        (format t "Goal reached! Final state: (~A, ~A)~%" curx cury))))

(water-jug 4 3 2)
