//
// Created by lulas on 10/19/2022.
//

#include <algorithm>
#include "schedule_manag.h"
#include "utility/csv_reader.h"
#include "utility/bst.h"

ScheduleManag::ScheduleManag(std::string class_uc_file, std::string class_schedule_file, std::string student_file, int max_students_per_class, std::string class_uc_file_write, std::string class_schedule_file_write, std::string student_file_write) 
        : reader_class_schedule(class_schedule_file), reader_class_uc(class_uc_file), reader_student(student_file), cuf(class_uc_file), csf(class_schedule_file), sf(student_file), max_students(max_students_per_class),
        cuf_save(class_uc_file_write), csf_save(class_schedule_file_write), sf_save(student_file_write), reader_class_uc_save(class_uc_file_write), reader_class_schedule_save(class_schedule_file_write), reader_student_save(student_file_write) { }

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
    // populate students bst considering the same student
    // is in consecutive lines
    Student student;
    vector<string> parts = reader_student.readNextLine();
    if(parts.size() == 4) {
        student = Student(parts[0], parts[1]);
    }
    student.addclass(UCTurma(parts[2], parts[3]));
    while(!reader_student.eof()) {
        parts = reader_student.readNextLine();
        if(parts.size() == 4) {
            Student student2 = Student(parts[0], parts[1]);
            if(student == student2) {
                student.addclass(UCTurma(parts[2], parts[3]));
            } else {
                students_set.insert(student);
                student = Student(parts[0], parts[1]);
                student.addclass(UCTurma(parts[2], parts[3]));
            }
        }
    }
    students_set.insert(student);

}

void ScheduleManag::writeFiles() {
    // write single line with the headers to the save files
    reader_class_uc_save.writeLine(vector<string>{reader_class_uc.getHeader()[0], reader_class_uc.getHeader()[1]});
    reader_class_schedule_save.writeLine(vector<string>{reader_class_schedule.getHeader()[0], reader_class_schedule.getHeader()[1], reader_class_schedule.getHeader()[2], reader_class_schedule.getHeader()[3], reader_class_schedule.getHeader()[4], reader_class_schedule.getHeader()[5]});
    reader_student_save.writeLine(vector<string>{reader_student.getHeader()[0], reader_student.getHeader()[1], reader_student.getHeader()[2], reader_student.getHeader()[3]}); 

    // write the data in the same way the files were read
    for(auto it = class_uc_map_slots.begin(); it != class_uc_map_slots.end(); it++) {
        // write class_uc to the class_uc_save file
        reader_class_uc_save.writeLine(vector<string>{it->first.uc, it->first.turma});
        // write slots to the class_schedule_save file
        for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            // floats have to be converted to string
            reader_class_schedule_save.writeLine(vector<string>{it2->uct.turma, it2->uct.uc, it2->weekDay, to_string(it2->startHour), to_string(it2->duration), it2->type});
        }
    }

    // write students to the student_save file
    for(auto it = students_set.begin(); it != students_set.end(); it++) {
        for(auto it2 = it->classes.begin(); it2 != it->classes.end(); it2++) {
            reader_student_save.writeLine(vector<string>{it->code, it->name, it2->uc, it2->turma});
        }
    }
}

map<UCTurma, vector<Slot>> ScheduleManag::getClassUCMapSlots() {
    return this->class_uc_map_slots;
}

set<Student> ScheduleManag::getStudentsSet() {
    return this->students_set;
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
    for (auto const& student : this->students_set) {
        students.push_back(student);
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

vector<UCTurma> ScheduleManag::getUCTsByUC(std::string uc) {
    vector<UCTurma> ucs;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.uc == uc) {
            ucs.push_back(key);
        }
    }
    return ucs;
}
//
//////////////
//////////////
//////////////
//
vector<ClassSchedule> ScheduleManag::getClassSchedules() {
    vector<ClassSchedule> class_schedules;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        class_schedules.push_back(ClassSchedule(val, key));
    }
    return class_schedules;
}

vector<UCTurma> ScheduleManag::getUCTsByStudent(Student student) {
    // search students_set for student
    auto it = students_set.find(student);
    if(it != students_set.end()) {
        return it->classes;
    }
    return vector<UCTurma>();
}

vector<Student> ScheduleManag::getStudentsByClass(string turma) {
    vector<Student> students;
    for (auto const& student : this->students_set) {
        for (auto const& uct : student.classes) {
            if(uct.turma == turma) {
                students.push_back(student);
            }
        }
    }
    return students;
}

vector<Student> ScheduleManag::getStudentsByUC(string uc) {
    vector<Student> students;
    for (auto const& student : this->students_set) {
        for (auto const& uct : student.classes) {
            if(uct.uc == uc) {
                students.push_back(student);
            }
        }
    }
}

vector<Student> ScheduleManag::getStudentsByClassAndUC(UCTurma uct) {
    vector<Student> students;
    for (auto const& student : this->students_set) {
        for (auto const& uct2 : student.classes) {
            if(uct2.uc == uct.uc && uct2.turma == uct.turma) {
                students.push_back(student);
            }
        }
    }
    return students;
}

vector<Student> ScheduleManag::getStudentsWithMoreThanXUC(int x) {
    vector<Student> students;
    for (auto const& student : this->students_set) {
        if(student.classes.size() > x) {
            students.push_back(student);
        }
    }
    return students;
}

vector<Slot> ScheduleManag::getSlotsByStudent(Student student) {
    vector<Slot> slots;
    // complexity O(n^3)
    for (auto const& [key, val] : this->class_uc_map_slots) {
        for (auto const& uct : student.classes) {
            if(uct.turma == key.turma && uct.uc == key.uc) {
                for (auto const& slot : val) {
                    slots.push_back(slot);
                }
            }
        }
    } 
    return slots;
}

vector<Slot> ScheduleManag::getSlotsByUC(string uc) {
    vector<Slot> slots;
    //complexity O(n)
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
    //complexity O(n)
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
    // complexity O(n)
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.turma == uct.turma && key.uc == uct.uc) {
            for (auto const& slot : val) {
                slots.push_back(slot);
            }
        }
    }
    return slots;
}

//// literally just adds a UCTurma to the vector in the student map
//// doesnt check if there is already a UCTurma with the same uc and class
//void ScheduleManag::addStudentToClass(Student student, string clss) {
//    // search students_set for student
//    auto it = students_set.find(student);
//    if(it != students_set.end()) {
//        UCTurma uct = UCTurma(student., clss);
//        it->classes.push_back(uct);
//    }
//}

// THIS ONE WORKS, now checks for overlapping slots
void ScheduleManag::addStudentToUC(Student student, string uc) {
    //check for the first class of the uc that has less than max_students
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.uc == uc) {
            // check if the slots that are PL or P dont overlap with the student's slots
            // for the UCs that the student is already in
            bool can_add = true;
            for(auto const& slot : val) {
                if(slot.type == "PL" || slot.type == "P") {
                    // check if the student has a slot that overlaps with this slot
                    for(auto const& student_slot : this->getSlotsByStudent(student)) {
                        if(student_slot.type == "PL" || student_slot.type == "P") {
                            if(slot.startHour + slot.duration > student_slot.startHour && slot.startHour < student_slot.startHour + student_slot.duration) {
                                // if it overlaps, dont add the student to this class
                                can_add = false;
                                break;
                            }
                        }
                    }
                }
            }

            // check if class has less than max_students
            if(val.size() < this->max_students && can_add) {
                // search students_set for student
                auto it = students_set.find(student);
                if(it != students_set.end()) {
                    UCTurma uct = UCTurma(uc, key.turma);
                    // remove the student from the set and store in found
                    Student found = *it;
                    students_set.erase(it);
                    // add the new UCTurma to the student
                    found.classes.push_back(uct);
                    // add the student back to the set
                    students_set.insert(found);
                } else {
                    // if the student is not in the set, add it
                    UCTurma uct = UCTurma(uc, key.turma);
                    student.classes.push_back(uct);
                    students_set.insert(student);
                }
                return;
            }
        }
    }
    // all the classes are full, so print an error
    cout << "All classes are full, or the ones that are open have slots of type P/PL that overlap with the ones already in the student" << endl;
}

// THIS ONE WORKS, now checks for overlapping slots
void ScheduleManag::addStudentToClassAndUC(Student student, UCTurma uct) {
    // check if the slots that are PL or P dont overlap with the student's slots
    // for the UCs that the student is already in
    bool can_add = true;
    for(auto const& slot : this->getSlotsByClassAndUC(uct)) {
        if(slot.type == "PL" || slot.type == "P") {
            // check if the student has a slot that overlaps with this slot
            for(auto const& student_slot : this->getSlotsByStudent(student)) {
                if(student_slot.type == "PL" || student_slot.type == "P") {
                    if(slot.startHour + slot.duration > student_slot.startHour && slot.startHour < student_slot.startHour + student_slot.duration) {
                        // if it overlaps, dont add the student to this class
                        can_add = false;
                        break;
                    }
                }
            }
        }
    }
    // check if the class has less than max_students
    if(getStudentsByClass(uct.turma).size() < max_students) {
        // search students_set for student
        auto it = students_set.find(student);
        if(it != students_set.end()) {
            // remove the student from the set and store in found
            Student found = *it;
            students_set.erase(it);
            // add the new UCTurma to the student
            found.classes.push_back(uct);
            // add the student back to the set
            students_set.insert(found);
        } else {
            // add student to students_set
            student.classes.push_back(uct);
            students_set.insert(student);
        }
    }
}

// THIS ONE WORKs?
void ScheduleManag::removeStudentFromClass(Student student, string clss) {
    // search students_set for student
    auto it = students_set.find(student);
    if(it != students_set.end()) {
        // remove the student from the set and store in found
        Student found = *it;
        students_set.erase(it);
        // remove the UCTurma from the student
        for (auto it = found.classes.begin(); it != found.classes.end(); ++it) {
            if(it->turma == clss) {
                found.classes.erase(it);
                break;
            }
        }
        // add the student back to the set
        students_set.insert(found);
    }
}

// WORKS
void ScheduleManag::removeStudentFromUC(Student student, string uc) {
    // search students_set for student
    auto it = students_set.find(student);
    if(it != students_set.end()) {
        // remove the student from the set and store in found
        Student found = *it;
        students_set.erase(it);
        // remove the UCTurma from the student
        for (auto it = found.classes.begin(); it != found.classes.end(); ++it) {
            if(it->uc == uc) {
                found.classes.erase(it);
                break;
            }
        }
        // add the student back to the set
        students_set.insert(found);
    }
}

// WORKS
void ScheduleManag::removeStudentFromClassAndUC(Student student, UCTurma uct) {
    // search students_set for student
    auto it = students_set.find(student);
    if(it != students_set.end()) {
        // remove the student from the set and store in found
        Student found = *it;
        students_set.erase(it);
        // remove the UCTurma from the student
        for (auto it = found.classes.begin(); it != found.classes.end(); ++it) {
            if(it->uc == uct.uc && it->turma == uct.turma) {
                found.classes.erase(it);
                break;
            }
        }
        // add the student back to the set
        students_set.insert(found);
    }
}