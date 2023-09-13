
(cl:in-package :asdf)

(defsystem "turtle_driver-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "circle" :depends-on ("_package_circle"))
    (:file "_package_circle" :depends-on ("_package"))
    (:file "custom" :depends-on ("_package_custom"))
    (:file "_package_custom" :depends-on ("_package"))
    (:file "square" :depends-on ("_package_square"))
    (:file "_package_square" :depends-on ("_package"))
  ))