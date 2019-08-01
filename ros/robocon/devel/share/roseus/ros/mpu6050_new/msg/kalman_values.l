;; Auto-generated. Do not edit!


(when (boundp 'mpu6050_new::kalman_values)
  (if (not (find-package "MPU6050_NEW"))
    (make-package "MPU6050_NEW"))
  (shadow 'kalman_values (find-package "MPU6050_NEW")))
(unless (find-package "MPU6050_NEW::KALMAN_VALUES")
  (make-package "MPU6050_NEW::KALMAN_VALUES"))

(in-package "ROS")
;;//! \htmlinclude kalman_values.msg.html


(defclass mpu6050_new::kalman_values
  :super ros::object
  :slots (_mpu_no _ax _ay _az ))

(defmethod mpu6050_new::kalman_values
  (:init
   (&key
    ((:mpu_no __mpu_no) 0)
    ((:ax __ax) 0.0)
    ((:ay __ay) 0.0)
    ((:az __az) 0.0)
    )
   (send-super :init)
   (setq _mpu_no (round __mpu_no))
   (setq _ax (float __ax))
   (setq _ay (float __ay))
   (setq _az (float __az))
   self)
  (:mpu_no
   (&optional __mpu_no)
   (if __mpu_no (setq _mpu_no __mpu_no)) _mpu_no)
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
    ;; uint8 _mpu_no
    1
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
     ;; uint8 _mpu_no
       (write-byte _mpu_no s)
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
   ;; uint8 _mpu_no
     (setq _mpu_no (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _ax
     (setq _ax (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ay
     (setq _ay (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _az
     (setq _az (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get mpu6050_new::kalman_values :md5sum-) "b85bc66545609800449b146da1841ce6")
(setf (get mpu6050_new::kalman_values :datatype-) "mpu6050_new/kalman_values")
(setf (get mpu6050_new::kalman_values :definition-)
      "uint8 mpu_no
float64 ax
float64 ay
float64 az

")



(provide :mpu6050_new/kalman_values "b85bc66545609800449b146da1841ce6")


