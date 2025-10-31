(defparameter *board* (make-array 10 :initial-element 2)) ; indices 1–9: 2=blank, 3=X, 5=O
(defparameter *turn* 0)

(defun is-blank (pos)
  (and (>= pos 1) (<= pos 9) (= (aref *board* pos) 2)))

(defun any-blank ()
  (loop for i from 1 to 9
        when (is-blank i)
        do (return i)
        finally (return 0)))

(defun make2 ()
  (let ((noncorners '(2 4 6 8)))
    (if (is-blank 5)
        5
        (loop for n in noncorners
              when (is-blank n)
              do (return n)
              finally (return 0)))))

(defun posswin (player-val)
  (let ((winoption '((1 2 3) (4 5 6) (7 8 9)
                     (1 4 7) (2 5 8) (3 6 9)
                     (1 5 9) (3 5 7)))
        (target (* player-val player-val 2)))
    (loop for line in winoption
          for a = (first line)
          for b = (second line)
          for c = (third line)
          for prod = (* (aref *board* a)
                        (aref *board* b)
                        (aref *board* c))
          when (= prod target)
          do (cond ((= (aref *board* a) 2) (return a))
                   ((= (aref *board* b) 2) (return b))
                   ((= (aref *board* c) 2) (return c)))
          finally (return 0))))

(defun make-move (pos)
  (unless (is-blank pos)
    (setf pos (any-blank)))
  (when (/= pos 0)
    (let ((player-val (if (oddp *turn*) 3 5)))
      (setf (aref *board* pos) player-val))))

(defun display-board ()
  (format t "~%Board:~%")
  (loop for i from 1 to 9
        for val = (aref *board* i)
        for ch = (cond ((= val 3) #\X)
                       ((= val 5) #\O)
                       (t #\.))
        do (format t "~A " ch)
        when (= (mod i 3) 0)
        do (terpri))
  (terpri))

(defun user-move ()
  (let ((pos 0))
    (loop
      (format t "Enter your move (1-9): ")
      (finish-output)
      (setf pos (parse-integer (read-line) :junk-allowed t))
      (if (and pos (is-blank pos))
          (progn
            (setf (aref *board* pos) 5)
            (return))
          (format t "Invalid move, try again.~%")))))

(defun check-win ()
  (let ((winoption '((1 2 3) (4 5 6) (7 8 9)
                     (1 4 7) (2 5 8) (3 6 9)
                     (1 5 9) (3 5 7))))
    (loop for line in winoption
          for a = (first line)
          for b = (second line)
          for c = (third line)
          when (and (/= (aref *board* a) 2)
                    (= (aref *board* a) (aref *board* b))
                    (= (aref *board* b) (aref *board* c)))
          do (return (aref *board* a))
          finally (return 0))))

(defun main ()
  (format t "You are O, computer is X.~%")
  (display-board)
  (loop for turn from 1 to 9
        do (setf *turn* turn)
        (let ((move 0))
          (if (oddp turn) ; computer's turn
              (cond ((= turn 1) (make-move 1))
                    ((= turn 3)
                     (if (is-blank 9) (make-move 9) (make-move 3)))
                    ((= turn 5)
                     (setf move (posswin 3))
                     (if (/= move 0) (make-move move)
                         (progn
                           (setf move (posswin 5))
                           (if (/= move 0) (make-move move)
                               (if (is-blank 7) (make-move 7) (make-move 3))))))
                    ((= turn 7)
                     (setf move (posswin 3))
                     (if (/= move 0) (make-move move)
                         (progn
                           (setf move (posswin 5))
                           (if (/= move 0) (make-move move)
                               (make-move (any-blank))))))
                    ((= turn 9)
                     (setf move (posswin 3))
                     (if (/= move 0) (make-move move)
                         (progn
                           (setf move (posswin 5))
                           (if (/= move 0) (make-move move)
                               (make-move (any-blank)))))))
              (user-move))) ; user's turn
        (display-board)
        (let ((winner (check-win)))
          (cond ((= winner 3) (format t "Computer (X) wins!~%") (return))
                ((= winner 5) (format t "You (O) win!~%") (return))))))

(main)
