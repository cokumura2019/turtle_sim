; Auto-generated. Do not edit!


(cl:in-package turtle_driver-srv)


;//! \htmlinclude custom-request.msg.html

(cl:defclass <custom-request> (roslisp-msg-protocol:ros-message)
  ((s
    :reader s
    :initarg :s
    :type cl:float
    :initform 0.0))
)

(cl:defclass custom-request (<custom-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <custom-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'custom-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name turtle_driver-srv:<custom-request> is deprecated: use turtle_driver-srv:custom-request instead.")))

(cl:ensure-generic-function 's-val :lambda-list '(m))
(cl:defmethod s-val ((m <custom-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader turtle_driver-srv:s-val is deprecated.  Use turtle_driver-srv:s instead.")
  (s m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <custom-request>) ostream)
  "Serializes a message object of type '<custom-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 's))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <custom-request>) istream)
  "Deserializes a message object of type '<custom-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 's) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<custom-request>)))
  "Returns string type for a service object of type '<custom-request>"
  "turtle_driver/customRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'custom-request)))
  "Returns string type for a service object of type 'custom-request"
  "turtle_driver/customRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<custom-request>)))
  "Returns md5sum for a message object of type '<custom-request>"
  "c14d551333fa66347a7669f2d8af65f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'custom-request)))
  "Returns md5sum for a message object of type 'custom-request"
  "c14d551333fa66347a7669f2d8af65f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<custom-request>)))
  "Returns full string definition for message of type '<custom-request>"
  (cl:format cl:nil "float64 s~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'custom-request)))
  "Returns full string definition for message of type 'custom-request"
  (cl:format cl:nil "float64 s~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <custom-request>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <custom-request>))
  "Converts a ROS message object to a list"
  (cl:list 'custom-request
    (cl:cons ':s (s msg))
))
;//! \htmlinclude custom-response.msg.html

(cl:defclass <custom-response> (roslisp-msg-protocol:ros-message)
  ((response
    :reader response
    :initarg :response
    :type cl:integer
    :initform 0))
)

(cl:defclass custom-response (<custom-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <custom-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'custom-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name turtle_driver-srv:<custom-response> is deprecated: use turtle_driver-srv:custom-response instead.")))

(cl:ensure-generic-function 'response-val :lambda-list '(m))
(cl:defmethod response-val ((m <custom-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader turtle_driver-srv:response-val is deprecated.  Use turtle_driver-srv:response instead.")
  (response m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <custom-response>) ostream)
  "Serializes a message object of type '<custom-response>"
  (cl:let* ((signed (cl:slot-value msg 'response)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <custom-response>) istream)
  "Deserializes a message object of type '<custom-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'response) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<custom-response>)))
  "Returns string type for a service object of type '<custom-response>"
  "turtle_driver/customResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'custom-response)))
  "Returns string type for a service object of type 'custom-response"
  "turtle_driver/customResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<custom-response>)))
  "Returns md5sum for a message object of type '<custom-response>"
  "c14d551333fa66347a7669f2d8af65f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'custom-response)))
  "Returns md5sum for a message object of type 'custom-response"
  "c14d551333fa66347a7669f2d8af65f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<custom-response>)))
  "Returns full string definition for message of type '<custom-response>"
  (cl:format cl:nil "int32 response~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'custom-response)))
  "Returns full string definition for message of type 'custom-response"
  (cl:format cl:nil "int32 response~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <custom-response>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <custom-response>))
  "Converts a ROS message object to a list"
  (cl:list 'custom-response
    (cl:cons ':response (response msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'custom)))
  'custom-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'custom)))
  'custom-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'custom)))
  "Returns string type for a service object of type '<custom>"
  "turtle_driver/custom")