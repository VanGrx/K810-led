cmake_minimum_required(VERSION 3.0)
project(k810-led)

find_package(KF5IdleTime)

set(REQUIRED_QT_VERSION 5.15.2)
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Gui)


set(src_files
    src/main.cpp
    src/KeyboardIdle.cpp)

add_executable(k810-led ${src_files}) 

set_target_properties(k810-led PROPERTIES AUTOMOC ON)
target_compile_options(k810-led PRIVATE -Wall -Wextra -pedantic -Werror)

target_link_libraries(k810-led KF5::IdleTime Qt5::Gui g810-led)
