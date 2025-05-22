cmake_minimum_required(VERSION 3.15)
project(YadroTest)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

find_package(OpenCV REQUIRED)

add_executable(smart_pointer_test tests/smart_pointer_test.cpp)
target_include_directories(smart_pointer_test PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(face_detection_test src/face_detection.cpp)
target_link_libraries(face_detection_test ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_test(NAME SmartPointerTest COMMAND smart_pointer_test)
add_test(
    NAME FaceDetectionTest
    COMMAND face_detection_test faces/face.jpg faces/face_detected.jpg
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)