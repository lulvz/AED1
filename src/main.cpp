//
// Created by lulas on 10/15/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>  
#include <sstream>

#include "./class_uc.h"
#include "./class_schedule.h"
#include "./student.h"

#include "./csv_reader.h"

#define CLASS_UC_FILE "../schedule/classes_per_uc.csv"
#define CLASS_SCHEDULE_FILE "../schedule/classes.csv"
#define STUDENT_FILE "../schedule/students_classes.csv"

using namespace std;

int main() {
    
    // create the vectors for the structs
    vector<ClassUc> classes_ucs;
    vector<ClassSchedule> classes_schedules;
    vector<Student> students;

    // create readers for the csv files
    CsvReader reader_class_uc(CLASS_UC_FILE);
    CsvReader reader_class_schedule(CLASS_SCHEDULE_FILE);
    CsvReader reader_student(STUDENT_FILE);

    // iterate over lines of the file and populate the vector classes_ucs
    while (!reader_class_uc.eof()) {
        vector<string> parts = reader_class_uc.readNextLine();
        if(parts.size() == 2) {
            ClassUc class_uc;
            class_uc.uc_code = parts[0];
            class_uc.class_code = parts[1];
            classes_ucs.push_back(class_uc);
        }
    }

    // iterate over lines of the file and populate the vector classes_schedules
    while (!reader_class_schedule.eof()) {
        vector<string> parts = reader_class_schedule.readNextLine();
        if(parts.size() == 6) {
            ClassSchedule class_schedule;
            class_schedule.cuc.class_code= parts[0];
            class_schedule.cuc.uc_code = parts[1];
            class_schedule.weekDay = parts[2];
            class_schedule.startHour = atof(parts[3].c_str());
            class_schedule.duration = atof(parts[4].c_str());
            class_schedule.type = parts[5];
            classes_schedules.push_back(class_schedule);
        }
    }

    // iterate over lines of the file and populate the vector students
    while (!reader_student.eof()) {
        vector<string> parts = reader_student.readNextLine();
        if(parts.size() == 4) {
            Student student;
            student.code = parts[0];
            student.name = parts[1];
            student.cuc.uc_code = parts[2];
            student.cuc.class_code = parts[3];
            students.push_back(student);
        }
    }



    for(ClassUc cuc : classes_ucs) {
        cout << cuc.uc_code << " " << cuc.class_code << endl;
    }
    for(ClassSchedule c : classes_schedules) {
        cout << c.startHour << endl;
    }
    for(Student s : students) {
        cout << s.code << endl;
    }
    return 0;
}