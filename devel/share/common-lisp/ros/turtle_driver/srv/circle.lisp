; Auto-generated. Do not edit!


(cl:in-package turtle_driver-srv)


;//! \htmlinclude circle-request.msg.html

(cl:defclass <circle-request> (roslisp-msg-protocol:ros-message)
  ((r
    :reader r
    :initarg :r
    :type cl:float
    :initform 0.0))
)

(cl:defclass circle-request (<circle-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <circle-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'circle-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name turtle_driver-srv:<circle-request> is deprecated: use turtle_driver-srv:circle-request instead.")))

(cl:ensure-generic-function 'r-val :lambda-list '(m))
(cl:defmethod r-val ((m <circle-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader turtle_driver-srv:r-val is deprecated.  Use turtle_driver-srv:r instead.")
  (r m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <circle-request>) ostream)
  "Serializes a message object of type '<circle-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'r))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <circle-request>) istream)
  "Deserializes a message object of type '<circle-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'r) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<circle-request>)))
  "Returns string type for a service object of type '<circle-request>"
  "turtle_driver/circleRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'circle-request)))
  "Returns string type for a service object of type 'circle-request"
  "turtle_driver/circleRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<circle-request>)))
  "Returns md5sum for a message object of type '<circle-request>"
  "8440676eb34de7b6e7477a0986292872")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'circle-request)))
  "Returns md5sum for a message object of type 'circle-request"
  "8440676eb34de7b6e7477a0986292872")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<circle-request>)))
  "Returns full string definition for message of type '<circle-request>"
  (cl:format cl:nil "float64 r~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'circle-request)))
  "Returns full string definition for message of type 'circle-request"
  (cl:format cl:nil "float64 r~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <circle-request>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <circle-request>))
  "Converts a ROS message object to a list"
  (cl:list 'circle-request
    (cl:cons ':r (r msg))
))
;//! \htmlinclude circle-response.msg.html

(cl:defclass <circle-response> (roslisp-msg-protocol:ros-message)
  ((response
    :reader response
    :initarg :response
    :type cl:integer
    :initform 0))
)

(cl:defclass circle-response (<circle-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <circle-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'circle-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name turtle_driver-srv:<circle-response> is deprecated: use turtle_driver-srv:circle-response instead.")))

(cl:ensure-generic-function 'response-val :lambda-list '(m))
(cl:defmethod response-val ((m <circle-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader turtle_driver-srv:response-val is deprecated.  Use turtle_driver-srv:response instead.")
  (response m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <circle-response>) ostream)
  "Serializes a message object of type '<circle-response>"
  (cl:let* ((signed (cl:slot-value msg 'response)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <circle-response>) istream)
  "Deserializes a message object of type '<circle-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'response) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<circle-response>)))
  "Returns string type for a service object of type '<circle-response>"
  "turtle_driver/circleResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'circle-response)))
  "Returns string type for a service object of type 'circle-response"
  "turtle_driver/circleResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<circle-response>)))
  "Returns md5sum for a message object of type '<circle-response>"
  "8440676eb34de7b6e7477a0986292872")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'circle-response)))
  "Returns md5sum for a message object of type 'circle-response"
  "8440676eb34de7b6e7477a0986292872")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<circle-response>)))
  "Returns full string definition for message of type '<circle-response>"
  (cl:format cl:nil "int32 response~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'circle-response)))
  "Returns full string definition for message of type 'circle-response"
  (cl:format cl:nil "int32 response~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <circle-response>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <circle-response>))
  "Converts a ROS message object to a list"
  (cl:list 'circle-response
    (cl:cons ':response (response msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'circle)))
  'circle-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'circle)))
  'circle-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'circle)))
  "Returns string type for a service object of type '<circle>"
  "turtle_driver/circle")