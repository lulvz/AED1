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

using namespace std;

int main() {

    // create schedule manager
    ScheduleManag sm(CLASS_UC_FILE, CLASS_SCHEDULE_FILE, STUDENT_FILE);

    // read files
    sm.readFiles();

    //get slots
    vector<Slot> slots = sm.getSlots();

    //print slots
    for (Slot slot : slots) {
        cout << slot.weekDay << " " << slot.startHour << " " << slot.duration << " " << slot.type << endl;;
    }


    return 0;
}

//    // iterate over lines of the file 
//    while (!reader_class_uc.eof()) {
//        vector<string> parts = reader_class_uc.readNextLine();
//        if(parts.size() == 2) {
//            UCTurma class_uc(parts[0], parts[1]);
//            // populate map of classes and ucs and slots with classes and ucs
//            class_uc_map_slots[class_uc] = list<Slot>();
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