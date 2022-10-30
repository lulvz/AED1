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
        src/student.h
        src/class_schedule.h
        src/schedule_manag.h
        src/uc_turma.h
        src/slot.h
        src/schedule_manag.cpp src/menu.h src/menu.cpp
        src/utility/bst.h
        src/utility/csv_reader.cpp
        src/utility/csv_reader.h
        src/utility/node.h)
