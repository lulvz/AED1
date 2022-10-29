//
// Created by lulas on 10/18/2022.
//

#ifndef SCHEDULE_MANAG_H
#define SCHEDULE_MANAG_H

#include "student.h"
#include "class_schedule.h"
#include "csv_reader.h"
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class ScheduleManag {
    public:
        //class constructor takes in the names of the files to read
        ScheduleManag(std::string class_uc_file, std::string class_schedule_file, std::string student_file, int max_students_per_class = 30);
        // read files and populate maps
        void readFiles();
        //getters for the maps
        map<UCTurma, vector<Slot>> getClassUCMapSlots();
        // menu 1-1
        map<Student, vector<UCTurma>> getStudentMapUCs();
        

        //getters for the vectors
        vector<UCTurma> getUCTs();
        vector<Student> getStudents();
        vector<Slot> getSlots(); 
        int getMaxStudents();

        // simple getters
        vector<UCTurma> getUCTsByUC(std::string uc);

        /////////////////////////////
        //complex getters
        ////////////////////////////
        vector<ClassSchedule> getClassSchedules();
        vector<UCTurma> getUCTsByStudent(Student student);

        // menu 1-2
        vector<Student> getStudentsByClass(string clss);
        //menu 1-4
        vector<Student> getStudentsByUC(string uc);

        vector<Student> getStudentsByClassAndUC(UCTurma uct);

        //menu 1-3
        vector<Student> getStudentsWithMoreThanXUC(int x);

        //menu 2-1
        vector<Slot> getSlotsByStudent(Student student);
        //menu 2-2
        vector<Slot> getSlotsByClass(string clss);
        //menu 2-3
        vector<Slot> getSlotsByUC(string uc);
        //menu 2-4
        vector<Slot> getSlotsByClassAndUC(UCTurma uct);

        //queue editors for adding and removing stude nts from classes/ucs
        void addStudentToClass(Student student, string clss);
        void addStudentToUC(Student student, string uc);
        void addStudentToClassAndUC(Student student, UCTurma uct);
        void removeStudentFromClass(Student student, string clss);
        void removeStudentFromUC(Student student, string uc);
        void removeStudentFromClassAndUC(Student student, UCTurma uct);

    private:
        //variables for the readers and the files
        std::string cuf, csf, sf;
        CsvReader reader_class_uc, reader_class_schedule, reader_student;

        int max_students;

        // map with ucs and slots
        map<UCTurma, vector<Slot>> class_uc_map_slots;

        // map with students and ucs
        map<Student, vector<UCTurma>> student_map_ucs;

        // queue structures

};

#endif //SCHEDULE_MANAG_H