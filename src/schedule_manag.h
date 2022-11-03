//
// Created by lulas on 10/18/2022.
//

#ifndef SCHEDULE_MANAG_H
#define SCHEDULE_MANAG_H

#include "student.h"
#include "class_schedule.h"
#include "utility/csv_reader.h"
#include "utility/bst.h"

//#include "utility/bst.h"

#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

/// @brief Classe responsável pela implementaação de todas as funcionalidades do programa.
class ScheduleManag {
    public:
        //class constructor takes in the names of the files to read
        ScheduleManag(std::string class_uc_file, std::string class_schedule_file, std::string student_file, int max_students_per_class,
        std::string class_uc_file_write, std::string class_schedule_file_write, std::string student_file_write);
        // read files and populate maps
        void readFiles();
        // write files the same way they were read
        void writeFiles();
        //getters for the maps
        map<UCTurma, vector<Slot>> getClassUCMapSlots();
        // menu 1-1
        map<Student, vector<UCTurma>> getStudentMapUCs();
        // getter for the binary tree
        set<Student> getStudentsSet();

        //getters for the vectors
        vector<UCTurma> getUCTs();
        set<string> getUCs();
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
        set<Student> getStudentsByClass(string clss);
        //menu 1-4
        set<Student> getStudentsByUC(string uc);
        //menu 1-1
        

        set<Student> getStudentsByClassAndUC(UCTurma uct);

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

        // deprecated //
        void addStudentToClass(Student student, string clss);
        void removeStudentFromClass(Student student, string clss);
        // deprecated //

        bool addStudentToUC(Student student, string uc);
        void addStudentToUCQ(Student student, string uc);

        bool addStudentToClassAndUC(Student student, UCTurma uct);
        void addStudentToClassAndUCQ(Student student, UCTurma uct);

        void removeStudentFromUC(Student student, string uc);
        void removeStudentFromUCQ(Student student, string uc);

        void removeStudentFromClassAndUC(Student student, UCTurma uct);
        void removeStudentFromClassAndUCQ(Student student, UCTurma uct);

        void modifyStudentsClassAndUCQ(Student student, UCTurma uct, UCTurma new_uct);

        // write the state of the schedule to the files
        void endDay();

    private:
        //variables for the readers and the files
        std::string cuf, csf, sf;
        CsvReader reader_class_uc, reader_class_schedule, reader_student;

        // variables for the writers of the save files
        std::string cuf_save, csf_save, sf_save;
        CsvReader reader_class_uc_save, reader_class_schedule_save, reader_student_save;
        
        // max number of students per class
        int max_students;

        // map with ucs and slots
        map<UCTurma, vector<Slot>> class_uc_map_slots;

        // binary tree with students
        set<Student> students_set;
                
        struct StudentQ {
            Student student;
            UCTurma uct;
        };

        struct StudentQModify {
            Student student;
            UCTurma old_uct;
            UCTurma new_uct;
        };

        // queue structures
        queue<StudentQ> class_add_queue;
        queue<StudentQ> class_remove_queue;
        queue<StudentQModify> class_modify_queue;

        deque<StudentQ> not_executed_requests_add;
        deque<StudentQModify> not_executed_requests_modify;

};

#endif //SCHEDULE_MANAG_H