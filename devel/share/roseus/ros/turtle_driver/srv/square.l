;; Auto-generated. Do not edit!


(when (boundp 'turtle_driver::square)
  (if (not (find-package "TURTLE_DRIVER"))
    (make-package "TURTLE_DRIVER"))
  (shadow 'square (find-package "TURTLE_DRIVER")))
(unless (find-package "TURTLE_DRIVER::SQUARE")
  (make-package "TURTLE_DRIVER::SQUARE"))
(unless (find-package "TURTLE_DRIVER::SQUAREREQUEST")
  (make-package "TURTLE_DRIVER::SQUAREREQUEST"))
(unless (find-package "TURTLE_DRIVER::SQUARERESPONSE")
  (make-package "TURTLE_DRIVER::SQUARERESPONSE"))

(in-package "ROS")





(defclass turtle_driver::squareRequest
  :super ros::object
  :slots (_s ))

(defmethod turtle_driver::squareRequest
  (:init
   (&key
    ((:s __s) 0.0)
    )
   (send-super :init)
   (setq _s (float __s))
   self)
  (:s
   (&optional __s)
   (if __s (setq _s __s)) _s)
  (:serialization-length
   ()
   (+
    ;; float64 _s
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _s
       (sys::poke _s (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _s
     (setq _s (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass turtle_driver::squareResponse
  :super ros::object
  :slots (_response ))

(defmethod turtle_driver::squareResponse
  (:init
   (&key
    ((:response __response) 0)
    )
   (send-super :init)
   (setq _response (round __response))
   self)
  (:response
   (&optional __response)
   (if __response (setq _response __response)) _response)
  (:serialization-length
   ()
   (+
    ;; int32 _response
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _response
       (write-long _response s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _response
     (setq _response (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass turtle_driver::square
  :super ros::object
  :slots ())

(setf (get turtle_driver::square :md5sum-) "c14d551333fa66347a7669f2d8af65f7")
(setf (get turtle_driver::square :datatype-) "turtle_driver/square")
(setf (get turtle_driver::square :request) turtle_driver::squareRequest)
(setf (get turtle_driver::square :response) turtle_driver::squareResponse)

(defmethod turtle_driver::squareRequest
  (:response () (instance turtle_driver::squareResponse :init)))

(setf (get turtle_driver::squareRequest :md5sum-) "c14d551333fa66347a7669f2d8af65f7")
(setf (get turtle_driver::squareRequest :datatype-) "turtle_driver/squareRequest")
(setf (get turtle_driver::squareRequest :definition-)
      "float64 s
---
int32 response
")

(setf (get turtle_driver::squareResponse :md5sum-) "c14d551333fa66347a7669f2d8af65f7")
(setf (get turtle_driver::squareResponse :datatype-) "turtle_driver/squareResponse")
(setf (get turtle_driver::squareResponse :definition-)
      "float64 s
---
int32 response
")



(provide :turtle_driver/square "c14d551333fa66347a7669f2d8af65f7")


