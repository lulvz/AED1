//
// Created by lulas on 10/15/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "./uc_turma.h"
#include "./class_schedule.h"
#include "./student.h"
#include "./schedule_manag.h"

#include "./csv_reader.h"

#define CLASS_UC_FILE "../schedule/classes_per_uc.csv"
#define CLASS_SCHEDULE_FILE "../schedule/classes.csv"
#define STUDENT_FILE "../schedule/students_classes.csv"

#define CLASS_LIMIT_STUDENTS 30

using namespace std;

int main() {

    // create schedule manager
    ScheduleManag sm(CLASS_UC_FILE, CLASS_SCHEDULE_FILE, STUDENT_FILE);

    // read files
    sm.readFiles();

    Student student = Student("202020302", "Carolina");

    // check if student is in the system
    if (find(sm.getStudents().begin(), sm.getStudents().end(), student) != sm.getStudents().end()) {
        cout << "Student is in the system" << endl;
    } else {
        cout << "Student is not in the system" << endl;
    }

    // get all classes of a student
    vector<UCTurma> ucts = sm.getUCTsByStudent(student);
    cout << "Student " << student.name << " is enrolled in the following classes:" << endl;
    for (auto &uct : ucts) {
        cout << "uc: " << uct.uc << " " << "turma: " << uct.turma << endl;
    }

    // // get turmas of all the students
    // map<Student, vector<UCTurma>> studentMapUCTs = sm.getStudentMapUCs();
    // cout << "All students and their classes:" << endl;
    // for (auto &studentUCTs : studentMapUCTs) {
    //     cout << "Student " << studentUCTs.first.name << " is enrolled in the following classes:" << endl;
    //     for (auto &uct : studentUCTs.second) {
    //         cout << "uc: " << uct.uc << " " << "turma: " << uct.turma << endl;
    //     }
    // }

    // remove student Carolina from turma 1LEIC10 and uc L.EIC001
    sm.removeStudentFromClassAndUC(student, UCTurma("L.EIC001", "1LEIC10"));
    
    // check turmas of Carolina
    ucts = sm.getUCTsByStudent(student);
    cout << "Student " << student.name << " is enrolled in the following classes:" << endl;
    for (auto &uct : ucts) {
        cout << "uc: " << uct.uc << " " << "turma: " << uct.turma << endl;
    }

    // check number of students in all the classes of uc "L.EIC001"
    vector<UCTurma> uctsL_EIC001 = sm.getUCTsByUC("L.EIC001");
    for (auto &uct : uctsL_EIC001) {
        cout << "Number of students in class " << uct.turma << " of uc " << uct.uc << " is " << sm.getStudentsByClassAndUC(uct).size() << endl;
    }

    return 0;
}

//    // iterate over lines of the file 
//    while (!reader_class_uc.eof()) {
//        vector<string> parts = reader_class_uc.readNextLine();
//        if(parts.size() == 2) {
//            UCTurma class_uc(parts[0], parts[1]);
//            // populate map of classes and ucs and slots with classes and ucs
//            class_uc_map_slots[class_uc] = vector<Slot>();
//        }
//    }
//
//    // populate slots vector
//    while (!reader_class_schedule.eof()) {
//        vector<string> parts = reader_class_schedule.readNextLine();
//        if(parts.size() == 6) {
//            Slot slot = Slot(parts[2], stof(parts[3]), stof(parts[4]), parts[5]);
//
//            // populate map of classes and ucs and slots
//            class_uc_map_slots[UCTurma(parts[1], parts[0])].push_back(slot);
//        }
//    }
//
//    while(!reader_student.eof()) {
//        vector<string> parts = reader_student.readNextLine();
//        if(parts.size() == 4) {
//            UCTurma class_uc(parts[2], parts[3]);
//            //populate map of students and ucs
//            student_map_ucs[Student(parts[0], parts[1])].push_back(class_uc);
//        }
//    }
//