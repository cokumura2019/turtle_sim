;; Auto-generated. Do not edit!


(when (boundp 'turtle_driver::circle)
  (if (not (find-package "TURTLE_DRIVER"))
    (make-package "TURTLE_DRIVER"))
  (shadow 'circle (find-package "TURTLE_DRIVER")))
(unless (find-package "TURTLE_DRIVER::CIRCLE")
  (make-package "TURTLE_DRIVER::CIRCLE"))
(unless (find-package "TURTLE_DRIVER::CIRCLEREQUEST")
  (make-package "TURTLE_DRIVER::CIRCLEREQUEST"))
(unless (find-package "TURTLE_DRIVER::CIRCLERESPONSE")
  (make-package "TURTLE_DRIVER::CIRCLERESPONSE"))

(in-package "ROS")





(defclass turtle_driver::circleRequest
  :super ros::object
  :slots (_r ))

(defmethod turtle_driver::circleRequest
  (:init
   (&key
    ((:r __r) 0.0)
    )
   (send-super :init)
   (setq _r (float __r))
   self)
  (:r
   (&optional __r)
   (if __r (setq _r __r)) _r)
  (:serialization-length
   ()
   (+
    ;; float64 _r
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _r
       (sys::poke _r (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _r
     (setq _r (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass turtle_driver::circleResponse
  :super ros::object
  :slots (_response ))

(defmethod turtle_driver::circleResponse
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

(defclass turtle_driver::circle
  :super ros::object
  :slots ())

(setf (get turtle_driver::circle :md5sum-) "8440676eb34de7b6e7477a0986292872")
(setf (get turtle_driver::circle :datatype-) "turtle_driver/circle")
(setf (get turtle_driver::circle :request) turtle_driver::circleRequest)
(setf (get turtle_driver::circle :response) turtle_driver::circleResponse)

(defmethod turtle_driver::circleRequest
  (:response () (instance turtle_driver::circleResponse :init)))

(setf (get turtle_driver::circleRequest :md5sum-) "8440676eb34de7b6e7477a0986292872")
(setf (get turtle_driver::circleRequest :datatype-) "turtle_driver/circleRequest")
(setf (get turtle_driver::circleRequest :definition-)
      "float64 r
---
int32 response
")

(setf (get turtle_driver::circleResponse :md5sum-) "8440676eb34de7b6e7477a0986292872")
(setf (get turtle_driver::circleResponse :datatype-) "turtle_driver/circleResponse")
(setf (get turtle_driver::circleResponse :definition-)
      "float64 r
---
int32 response
")



(provide :turtle_driver/circle "8440676eb34de7b6e7477a0986292872")


