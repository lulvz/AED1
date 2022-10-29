//
// Created by lulas on 10/18/2022.
//

#ifndef SCHEDULE_MANAG_H
#define SCHEDULE_MANAG_H

#include "student.h"
#include "class_schedule.h"
#include "csv_reader.h"
#include <vector>
#include <set>
#include <map>

using namespace std;

class ScheduleManag {
    public:
        ScheduleManag(std::string class_uc_file, std::string class_schedule_file, std::string student_file);
        void readFiles();
        map<UCTurma, list<Slot>> getClassUCMapSlots();
        map<Student, list<UCTurma>> getStudentMapUCs();
        vector<UCTurma> getUCTs();
        vector<Student> getStudents();
        vector<Slot> getSlots();
        vector<ClassSchedule> getClassSchedules();
        vector<UCTurma> getUCsByStudent(Student student);
        vector<Slot> getSlotsByUC(UCTurma uc);

    private:
        std::string cuf, csf, sf;
        CsvReader reader_class_uc, reader_class_schedule, reader_student;

        // map with ucs and slots
        map<UCTurma, list<Slot>> class_uc_map_slots;

        // map with students and ucs
        map<Student, list<UCTurma>> student_map_ucs;
};

#endif //SCHEDULE_MANAG_H