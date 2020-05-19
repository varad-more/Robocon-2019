;; Auto-generated. Do not edit!


(when (boundp 'mpu6050_new::mpu_values)
  (if (not (find-package "MPU6050_NEW"))
    (make-package "MPU6050_NEW"))
  (shadow 'mpu_values (find-package "MPU6050_NEW")))
(unless (find-package "MPU6050_NEW::MPU_VALUES")
  (make-package "MPU6050_NEW::MPU_VALUES"))
(unless (find-package "MPU6050_NEW::MPU_VALUESREQUEST")
  (make-package "MPU6050_NEW::MPU_VALUESREQUEST"))
(unless (find-package "MPU6050_NEW::MPU_VALUESRESPONSE")
  (make-package "MPU6050_NEW::MPU_VALUESRESPONSE"))

(in-package "ROS")





(defclass mpu6050_new::mpu_valuesRequest
  :super ros::object
  :slots (_no ))

(defmethod mpu6050_new::mpu_valuesRequest
  (:init
   (&key
    ((:no __no) 0)
    )
   (send-super :init)
   (setq _no (round __no))
   self)
  (:no
   (&optional __no)
   (if __no (setq _no __no)) _no)
  (:serialization-length
   ()
   (+
    ;; int64 _no
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _no
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _no (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _no) (= (length (_no . bv)) 2)) ;; bignum
              (write-long (ash (elt (_no . bv) 0) 0) s)
              (write-long (ash (elt (_no . bv) 1) -1) s))
             ((and (class _no) (= (length (_no . bv)) 1)) ;; big1
              (write-long (elt (_no . bv) 0) s)
              (write-long (if (>= _no 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _no s)(write-long (if (>= _no 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _no
#+(or :alpha :irix6 :x86_64)
      (setf _no (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _no (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(defclass mpu6050_new::mpu_valuesResponse
  :super ros::object
  :slots (_ax _ay _az ))

(defmethod mpu6050_new::mpu_valuesResponse
  (:init
   (&key
    ((:ax __ax) 0.0)
    ((:ay __ay) 0.0)
    ((:az __az) 0.0)
    )
   (send-super :init)
   (setq _ax (float __ax))
   (setq _ay (float __ay))
   (setq _az (float __az))
   self)
  (:ax
   (&optional __ax)
   (if __ax (setq _ax __ax)) _ax)
  (:ay
   (&optional __ay)
   (if __ay (setq _ay __ay)) _ay)
  (:az
   (&optional __az)
   (if __az (setq _az __az)) _az)
  (:serialization-length
   ()
   (+
    ;; float64 _ax
    8
    ;; float64 _ay
    8
    ;; float64 _az
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _ax
       (sys::poke _ax (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ay
       (sys::poke _ay (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _az
       (sys::poke _az (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _ax
     (setq _ax (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ay
     (setq _ay (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _az
     (setq _az (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass mpu6050_new::mpu_values
  :super ros::object
  :slots ())

(setf (get mpu6050_new::mpu_values :md5sum-) "9d07d6506a1d6f140e4337bd15bb5dec")
(setf (get mpu6050_new::mpu_values :datatype-) "mpu6050_new/mpu_values")
(setf (get mpu6050_new::mpu_values :request) mpu6050_new::mpu_valuesRequest)
(setf (get mpu6050_new::mpu_values :response) mpu6050_new::mpu_valuesResponse)

(defmethod mpu6050_new::mpu_valuesRequest
  (:response () (instance mpu6050_new::mpu_valuesResponse :init)))

(setf (get mpu6050_new::mpu_valuesRequest :md5sum-) "9d07d6506a1d6f140e4337bd15bb5dec")
(setf (get mpu6050_new::mpu_valuesRequest :datatype-) "mpu6050_new/mpu_valuesRequest")
(setf (get mpu6050_new::mpu_valuesRequest :definition-)
      "int64 no
---
float64 ax
float64 ay
float64 az

")

(setf (get mpu6050_new::mpu_valuesResponse :md5sum-) "9d07d6506a1d6f140e4337bd15bb5dec")
(setf (get mpu6050_new::mpu_valuesResponse :datatype-) "mpu6050_new/mpu_valuesResponse")
(setf (get mpu6050_new::mpu_valuesResponse :definition-)
      "int64 no
---
float64 ax
float64 ay
float64 az

")



(provide :mpu6050_new/mpu_values "9d07d6506a1d6f140e4337bd15bb5dec")


