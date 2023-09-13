;; Auto-generated. Do not edit!


(when (boundp 'turtle_driver::custom)
  (if (not (find-package "TURTLE_DRIVER"))
    (make-package "TURTLE_DRIVER"))
  (shadow 'custom (find-package "TURTLE_DRIVER")))
(unless (find-package "TURTLE_DRIVER::CUSTOM")
  (make-package "TURTLE_DRIVER::CUSTOM"))
(unless (find-package "TURTLE_DRIVER::CUSTOMREQUEST")
  (make-package "TURTLE_DRIVER::CUSTOMREQUEST"))
(unless (find-package "TURTLE_DRIVER::CUSTOMRESPONSE")
  (make-package "TURTLE_DRIVER::CUSTOMRESPONSE"))

(in-package "ROS")





(defclass turtle_driver::customRequest
  :super ros::object
  :slots (_s ))

(defmethod turtle_driver::customRequest
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

(defclass turtle_driver::customResponse
  :super ros::object
  :slots (_response ))

(defmethod turtle_driver::customResponse
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

(defclass turtle_driver::custom
  :super ros::object
  :slots ())

(setf (get turtle_driver::custom :md5sum-) "c14d551333fa66347a7669f2d8af65f7")
(setf (get turtle_driver::custom :datatype-) "turtle_driver/custom")
(setf (get turtle_driver::custom :request) turtle_driver::customRequest)
(setf (get turtle_driver::custom :response) turtle_driver::customResponse)

(defmethod turtle_driver::customRequest
  (:response () (instance turtle_driver::customResponse :init)))

(setf (get turtle_driver::customRequest :md5sum-) "c14d551333fa66347a7669f2d8af65f7")
(setf (get turtle_driver::customRequest :datatype-) "turtle_driver/customRequest")
(setf (get turtle_driver::customRequest :definition-)
      "float64 s
---
int32 response
")

(setf (get turtle_driver::customResponse :md5sum-) "c14d551333fa66347a7669f2d8af65f7")
(setf (get turtle_driver::customResponse :datatype-) "turtle_driver/customResponse")
(setf (get turtle_driver::customResponse :definition-)
      "float64 s
---
int32 response
")



(provide :turtle_driver/custom "c14d551333fa66347a7669f2d8af65f7")


