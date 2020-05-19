
(cl:in-package :asdf)

(defsystem "mpu6050_new-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "mpu_values" :depends-on ("_package_mpu_values"))
    (:file "_package_mpu_values" :depends-on ("_package"))
  ))