
(cl:in-package :asdf)

(defsystem "mpu6050_new-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "accl_values" :depends-on ("_package_accl_values"))
    (:file "_package_accl_values" :depends-on ("_package"))
  ))