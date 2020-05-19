# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "mpu6050_new: 2 messages, 1 services")

set(MSG_I_FLAGS "-Impu6050_new:/home/pi/robocon/src/mpu6050_new/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(mpu6050_new_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg" NAME_WE)
add_custom_target(_mpu6050_new_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mpu6050_new" "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg" ""
)

get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg" NAME_WE)
add_custom_target(_mpu6050_new_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mpu6050_new" "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg" ""
)

get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv" NAME_WE)
add_custom_target(_mpu6050_new_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mpu6050_new" "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mpu6050_new
)
_generate_msg_cpp(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mpu6050_new
)

### Generating Services
_generate_srv_cpp(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mpu6050_new
)

### Generating Module File
_generate_module_cpp(mpu6050_new
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mpu6050_new
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(mpu6050_new_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(mpu6050_new_generate_messages mpu6050_new_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_cpp _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_cpp _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_cpp _mpu6050_new_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mpu6050_new_gencpp)
add_dependencies(mpu6050_new_gencpp mpu6050_new_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mpu6050_new_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/mpu6050_new
)
_generate_msg_eus(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/mpu6050_new
)

### Generating Services
_generate_srv_eus(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/mpu6050_new
)

### Generating Module File
_generate_module_eus(mpu6050_new
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/mpu6050_new
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(mpu6050_new_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(mpu6050_new_generate_messages mpu6050_new_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_eus _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_eus _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_eus _mpu6050_new_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mpu6050_new_geneus)
add_dependencies(mpu6050_new_geneus mpu6050_new_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mpu6050_new_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mpu6050_new
)
_generate_msg_lisp(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mpu6050_new
)

### Generating Services
_generate_srv_lisp(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mpu6050_new
)

### Generating Module File
_generate_module_lisp(mpu6050_new
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mpu6050_new
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(mpu6050_new_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(mpu6050_new_generate_messages mpu6050_new_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_lisp _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_lisp _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_lisp _mpu6050_new_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mpu6050_new_genlisp)
add_dependencies(mpu6050_new_genlisp mpu6050_new_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mpu6050_new_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/mpu6050_new
)
_generate_msg_nodejs(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/mpu6050_new
)

### Generating Services
_generate_srv_nodejs(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/mpu6050_new
)

### Generating Module File
_generate_module_nodejs(mpu6050_new
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/mpu6050_new
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(mpu6050_new_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(mpu6050_new_generate_messages mpu6050_new_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_nodejs _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_nodejs _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_nodejs _mpu6050_new_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mpu6050_new_gennodejs)
add_dependencies(mpu6050_new_gennodejs mpu6050_new_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mpu6050_new_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mpu6050_new
)
_generate_msg_py(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mpu6050_new
)

### Generating Services
_generate_srv_py(mpu6050_new
  "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mpu6050_new
)

### Generating Module File
_generate_module_py(mpu6050_new
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mpu6050_new
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(mpu6050_new_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(mpu6050_new_generate_messages mpu6050_new_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/accl_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_py _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/msg/kalman_values.msg" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_py _mpu6050_new_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pi/robocon/src/mpu6050_new/srv/mpu_values.srv" NAME_WE)
add_dependencies(mpu6050_new_generate_messages_py _mpu6050_new_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mpu6050_new_genpy)
add_dependencies(mpu6050_new_genpy mpu6050_new_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mpu6050_new_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mpu6050_new)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mpu6050_new
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(mpu6050_new_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/mpu6050_new)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/mpu6050_new
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(mpu6050_new_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mpu6050_new)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mpu6050_new
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(mpu6050_new_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/mpu6050_new)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/mpu6050_new
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(mpu6050_new_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mpu6050_new)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mpu6050_new\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mpu6050_new
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(mpu6050_new_generate_messages_py std_msgs_generate_messages_py)
endif()
