cmake_minimum_required(VERSION 3.23)
project(AED_PROJETO)

set(CMAKE_CXX_STANDARD 14)

include_directories(schedule)
include_directories(src)

add_executable(AED_PROJETO
        schedule/classes.csv
        schedule/classes_per_uc.csv
        schedule/students_classes.csv
        src/main.cpp
        src/class_uc.h
        src/student.h
        src/class_schedule.h
        src/csv_reader.cpp
        src/csv_reader.h)
