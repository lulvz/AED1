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

#include "./csv_reader.h"

#define CLASS_UC_FILE "../schedule/classes_per_uc.csv"
#define CLASS_SCHEDULE_FILE "../schedule/classes.csv"
#define STUDENT_FILE "../schedule/students_classes.csv"

using namespace std;

int main() {
    // create readers for the csv files
    CsvReader reader_class_uc(CLASS_UC_FILE);
    CsvReader reader_class_schedule(CLASS_SCHEDULE_FILE);
    CsvReader reader_student(STUDENT_FILE);

    CsvReader reader_writer("../schedule/test.csv");

    // map with ucs and slots
    map<UCTurma, list<Slot>> class_uc_map_slots;

    // iterate over lines of the file 
    while (!reader_class_uc.eof()) {
        vector<string> parts = reader_class_uc.readNextLine();
        if(parts.size() == 2) {
            UCTurma class_uc(parts[0], parts[1]);
            // populate map of classes and ucs and slots with classes and ucs
            class_uc_map_slots[class_uc] = list<Slot>();
        }
    }

    // populate slots vector
    while (!reader_class_schedule.eof()) {
        vector<string> parts = reader_class_schedule.readNextLine();
        if(parts.size() == 2) {
            Slot slot = Slot(parts[2], stof(parts[3]), stof(parts[4]), parts[5]);

            // populate map of classes and ucs and slots
            class_uc_map_slots[UCTurma(parts[0], parts[2])].push_back(slot);
        }
    }

    return 0;
}