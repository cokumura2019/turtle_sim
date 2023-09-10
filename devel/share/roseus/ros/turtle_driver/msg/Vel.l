;; Auto-generated. Do not edit!


(when (boundp 'turtle_driver::Vel)
  (if (not (find-package "TURTLE_DRIVER"))
    (make-package "TURTLE_DRIVER"))
  (shadow 'Vel (find-package "TURTLE_DRIVER")))
(unless (find-package "TURTLE_DRIVER::VEL")
  (make-package "TURTLE_DRIVER::VEL"))

(in-package "ROS")
;;//! \htmlinclude Vel.msg.html


(defclass turtle_driver::Vel
  :super ros::object
  :slots ())

(defmethod turtle_driver::Vel
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(setf (get turtle_driver::Vel :md5sum-) "d41d8cd98f00b204e9800998ecf8427e")
(setf (get turtle_driver::Vel :datatype-) "turtle_driver/Vel")
(setf (get turtle_driver::Vel :definition-)
      "
")



(provide :turtle_driver/Vel "d41d8cd98f00b204e9800998ecf8427e")


