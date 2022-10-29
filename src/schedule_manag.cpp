//
// Created by lulas on 10/19/2022.
//

#include <algorithm>
#include "schedule_manag.h"

ScheduleManag::ScheduleManag(std::string class_uc_file, std::string class_schedule_file, std::string student_file, int max_students_per_class)
        : reader_class_schedule(class_schedule_file), reader_class_uc(class_uc_file), reader_student(student_file), cuf(class_uc_file), csf(class_schedule_file), sf(student_file), max_students(max_students_per_class) { }

void ScheduleManag::readFiles() {    // iterate over lines of the file 
    while (!reader_class_uc.eof()) {
        vector<string> parts = reader_class_uc.readNextLine();
        if(parts.size() == 2) {
            UCTurma class_uc(parts[0], parts[1]);
            // populate map of classes and ucs and slots with classes and ucs
            class_uc_map_slots[class_uc] = vector<Slot>();
        }
    }

    // populate slots vector
    while (!reader_class_schedule.eof()) {
        vector<string> parts = reader_class_schedule.readNextLine();
        if(parts.size() == 6) {
            Slot slot = Slot(parts[2], stof(parts[3]), stof(parts[4]), parts[5], UCTurma(parts[1], parts[0]));

            // populate map of classes and ucs and slots
            class_uc_map_slots[UCTurma(parts[1], parts[0])].push_back(slot);
        }
    }

    while(!reader_student.eof()) {
        vector<string> parts = reader_student.readNextLine();
        if(parts.size() == 4) {
            UCTurma class_uc(parts[2], parts[3]);
            //populate map of students and ucs
            student_map_ucs[Student(parts[0], parts[1])].push_back(class_uc);
        }
    }
}

map<UCTurma, vector<Slot>> ScheduleManag::getClassUCMapSlots() {
    return this->class_uc_map_slots;
}

map<Student, vector<UCTurma>> ScheduleManag::getStudentMapUCs() {
    return this->student_map_ucs;
}

vector<UCTurma> ScheduleManag::getUCTs() {
    vector<UCTurma> ucs;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        ucs.push_back(key);
    }
    return ucs;
}

vector<Student> ScheduleManag::getStudents() {
    vector<Student> students;
    for (auto const& [key, val] : this->student_map_ucs) {
        students.push_back(key);
    }
    return students;
}

vector<Slot> ScheduleManag::getSlots() {
    vector<Slot> slots;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        for (auto const& slot : val) {
            slots.push_back(slot);
        }
    }
    return slots;
}

int ScheduleManag::getMaxStudents() {
    return this->max_students;
}

////////////

vector<UCTurma> ScheduleManag::getUCTsByUC(std::string uc) {
    vector<UCTurma> ucs;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.uc == uc) {
            ucs.push_back(key);
        }
    }
    return ucs;
}

////////////
////////////
////////////

vector<ClassSchedule> ScheduleManag::getClassSchedules() {
    vector<ClassSchedule> class_schedules;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        class_schedules.push_back(ClassSchedule(val, key));
    }
    return class_schedules;
}

vector<UCTurma> ScheduleManag::getUCTsByStudent(Student student) {
    vector<UCTurma> ucs;
    for (auto const& uc : this->student_map_ucs[student]) {
        ucs.push_back(uc);
    }
    return ucs;
}

vector<Student> ScheduleManag::getStudentsByClass(string clss) {
    vector<Student> students;
    for (auto const& [key, val] : this->student_map_ucs) {
        for (auto const& uc : val) {
            if (uc.turma == clss) {
                students.push_back(key);
            }
        }
    }
    return students;
}

vector<Student> ScheduleManag::getStudentsByUC(string uc) {
    vector<Student> students;
    for(auto const& [key, val] : this->student_map_ucs) {
        for(auto const& uct : val) {
            if(uct.uc == uc) {
                students.push_back(key);
            }
        }
    }
}

vector<Student> ScheduleManag::getStudentsByClassAndUC(UCTurma uct) {
    vector<Student> students;
    for(auto const& [key, val] : this->student_map_ucs) {
        for(auto const& uct2 : val) {
            if(uct2.uc == uct.uc && uct2.turma == uct.turma) {
                students.push_back(key);
            }
        }
    }
    return students;
}

vector<Student> ScheduleManag::getStudentsWithMoreThanXUC(int x) {
    vector<Student> students;
    for(auto const& [key, val] : this->student_map_ucs) {
        if(val.size() > x) {
            students.push_back(key);
        }
    }
    return students;
}

vector<Slot> ScheduleManag::getSlotsByStudent(Student student) {
    vector<Slot> slots;
    for(auto const& uc : this->student_map_ucs[student]) {
        for(auto const& slot : this->class_uc_map_slots[uc]) {
            slots.push_back(slot);
        }
    }
    return slots;
}

vector<Slot> ScheduleManag::getSlotsByUC(string uc) {
    vector<Slot> slots;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.uc == uc) {
            for (auto const& slot : val) {
                slots.push_back(slot);
            }
        }
    }
    return slots;
}

vector<Slot> ScheduleManag::getSlotsByClass(string clss) {
    vector<Slot> slots;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.turma == clss) {
            for (auto const& slot : val) {
                slots.push_back(slot);
            }
        }
    }
    return slots;
}

vector<Slot> ScheduleManag::getSlotsByClassAndUC(UCTurma uct) {
    vector<Slot> slots;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.turma == uct.turma && key.uc == uct.uc) {
            for (auto const& slot : val) {
                slots.push_back(slot);
            }
        }
    }
    return slots;
}

// literally just adds a UCTurma to the vector in the student map
// doesnt check if there is already a UCTurma with the same uc and class
void ScheduleManag::addStudentToClass(Student student, string clss) {
    // iterate over ucs and check one that has less than max_students variable
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.turma == clss) {
            if(getStudentsByClass(clss).size() < max_students) {
                this->student_map_ucs[student].push_back(key);
            }
        }
    }
}

void ScheduleManag::addStudentToUC(Student student, string uc) {
    // check the classes for the first one in the uc that has less than max_students
    string clss = "";
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.uc == uc) {
            if(getStudentsByClass(key.turma).size() < max_students) {
                clss = key.turma;
                break;
            }
        }
    }
    student_map_ucs[student].push_back(UCTurma(uc, clss));
}


// THIS ONE WORKS
void ScheduleManag::addStudentToClassAndUC(Student student, UCTurma uct) {
    // check if the class has less than max_students
    if(getStudentsByClass(uct.turma).size() < max_students) {
        student_map_ucs[student].push_back(uct);
    }
}

// ADDS 5 TIMES EVERYTIME
void ScheduleManag::removeStudentFromClass(Student student, string clss) {
    student_map_ucs[student].erase(remove_if(student_map_ucs[student].begin(), student_map_ucs[student].end(), [clss](UCTurma uct) { return uct.turma == clss; }), student_map_ucs[student].end());
}

// WORKS
void ScheduleManag::removeStudentFromUC(Student student, string uc) {
    student_map_ucs[student].erase(remove_if(student_map_ucs[student].begin(), student_map_ucs[student].end(), [uc](UCTurma uct) { return uct.uc == uc; }), student_map_ucs[student].end());
}

// WORKS
void ScheduleManag::removeStudentFromClassAndUC(Student student, UCTurma uct) {
    student_map_ucs[student].erase(remove_if(student_map_ucs[student].begin(), student_map_ucs[student].end(), [uct](UCTurma uct2) { return uct2.uc == uct.uc && uct2.turma == uct.turma; }), student_map_ucs[student].end());
}