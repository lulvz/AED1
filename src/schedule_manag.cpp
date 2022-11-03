//
// Created by lulas on 10/19/2022.
//

#include <algorithm>
#include "schedule_manag.h"
#include "utility/csv_reader.h"
#include "utility/bst.h"

map<string ,int> semana ={{"Monday",2},{"Tuesday",3},{"Wednesday",4},{"Thursday",5},{"Friday",6}};

bool cmp_day(const Slot &s1, const Slot &s2){
    if(semana[s1.weekDay] < semana[s2.weekDay]){
        return true;
    }
    else if(semana[s1.weekDay] == semana[s2.weekDay]){
        return s1.startHour < s2.startHour;
    }
    return false;
}

/*! @brief Construtor da classe ScheduleManag.
* Recebe todos os ficheiros necessários à leitura e escrita dos horários.
*
* @param class_uc_file 
* @param class_schedule_file 
* @param student_file 
* @param max_students_per_class 
* @param class_uc_file_write 
* @param class_schedule_file_write 
* @param student_file_write
*/
ScheduleManag::ScheduleManag(std::string class_uc_file, std::string class_schedule_file, std::string student_file, int max_students_per_class, std::string class_uc_file_write, std::string class_schedule_file_write, std::string student_file_write) 
        : reader_class_schedule(class_schedule_file), reader_class_uc(class_uc_file), reader_student(student_file), cuf(class_uc_file), csf(class_schedule_file), sf(student_file), max_students(max_students_per_class),
        cuf_save(class_uc_file_write), csf_save(class_schedule_file_write), sf_save(student_file_write), reader_class_uc_save(class_uc_file_write), reader_class_schedule_save(class_schedule_file_write), reader_student_save(student_file_write) { }

/// @brief Função que lê todos os ficheiros e preeche os maps associados.
/// Esta função tem complexidade de O(n).
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
                student = student2;
                student.addclass(UCTurma(parts[2], parts[3]));
            }
        }
    }
    students_set.insert(student);

}

/// @brief Função que escreve as alterações efetuadas para os respetivos Ficheiros.
/// Esta função tem complexidade de O(n²)
void ScheduleManag::writeFiles() {
    // clear the files before writing to them
    reader_class_uc_save.clearFile();
    reader_class_schedule_save.clearFile();
    reader_student_save.clearFile();

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

/// @brief Função Get.
/// @return Retorna um map com uma UCTurma e os horários associados a esta.
map<UCTurma, vector<Slot>> ScheduleManag::getClassUCMapSlots() {
    return this->class_uc_map_slots;
}

/// @brief Função Get.
/// @return Retorna um set de Estudantes.
set<Student> ScheduleManag::getStudentsSet() {
    return this->students_set;
}

/// @brief Função Get.
/// @return Retorna um vetor de UCTurmas.
vector<UCTurma> ScheduleManag::getUCTs() {
    vector<UCTurma> ucs;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        ucs.push_back(key);
    }
    return ucs;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n)
/// @return Retorna um set com códigos das várias ucs. 
set<string> ScheduleManag::getUCs() {
    set<string> ucs;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        ucs.insert(key.uc);
    }
    return ucs;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n).
/// @return Retorna um vetor de estudantes.
vector<Student> ScheduleManag::getStudents() {
    vector<Student> students;
    for (auto const& student : this->students_set) {
        students.push_back(student);
    }
    return students;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n).
/// @return Retorna um vetor de Slots.
vector<Slot> ScheduleManag::getSlots() {
    vector<Slot> slots;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        for (auto const& slot : val) {
            slots.push_back(slot);
        }
    }
    return slots;
}

/// @brief Função Get.
/// @return Retorna o número máximo de estudantes numa turma.
int ScheduleManag::getMaxStudents() {
    return this->max_students;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n).
/// @param uc 
/// @return Retorna um vetor com todas as turmas na uc passada como argumento.
vector<UCTurma> ScheduleManag::getUCTsByUC(std::string uc) {
    vector<UCTurma> ucs;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.uc == uc) {
            ucs.push_back(key);
        }
    }
    return ucs;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n).
/// @return Retorna um vetor com os horários de todas as turmas.
vector<ClassSchedule> ScheduleManag::getClassSchedules() {
    vector<ClassSchedule> class_schedules;
    for (auto const& [key, val] : this->class_uc_map_slots) {
        class_schedules.push_back(ClassSchedule(val, key));
    }
    return class_schedules;
}

/// @brief Função Get.
/// @param student 
/// @return Retorna um vetor de UCTurmas do estudante passado como argumento.
vector<UCTurma> ScheduleManag::getUCTsByStudent(Student student) {
    // search students_set for student
    auto it = students_set.find(student);
    if(it != students_set.end()) {
        return it->classes;
    }
    return vector<UCTurma>();
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n²).
/// @param turma 
/// @return Retorna todos os estudantes na turma passada como argumento.
set<Student> ScheduleManag::getStudentsByClass(string turma) {
    set<Student> students;
    for (auto const& student : this->students_set) {
        for (auto const& uct : student.classes) {
            if(uct.turma == turma) {
                students.insert(student);
            }
        }
    }
    return students;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n²).
/// @param uc 
/// @return Retorna um set dos estudantes na UC passada como argumento.
set<Student> ScheduleManag::getStudentsByUC(string uc) {
    set<Student> students;
    for (auto const& student : this->students_set) {
        for (auto const& uct : student.classes) {
            if(uct.uc == uc) {
                students.insert(student);
            }
        }
    }
    return students;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n²).
/// @param uct 
/// @return Retorna um set dos estudantes na UCTurma passada como argumento.
set<Student> ScheduleManag::getStudentsByClassAndUC(UCTurma uct) {
    set<Student> students;
    for (auto const& student : this->students_set) {
        for (auto const& uct2 : student.classes) {
            if(uct2.uc == uct.uc && uct2.turma == uct.turma) {
                students.insert(student);
            }
        }
    }
    return students;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n).
/// @param x 
/// @return Retorna um vetor dos estudantes com mais do que x ucs, sendo x um inteiro passado como argumento.
vector<Student> ScheduleManag::getStudentsWithMoreThanXUC(int x) {
    vector<Student> students;
    for (auto const& student : this->students_set) {
        if(student.classes.size() > x) {
            students.push_back(student);
        }
    }
    return students;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n²).
/// @param student 
/// @return Retorna um vetor de Slots do estudante passado como argumento.
vector<Slot> ScheduleManag::getSlotsByStudent(Student student) {
    vector<Slot> slots;
    for(auto s : students_set.find(student)->classes) {
        for(auto uct : getSlotsByClassAndUC(s)) {
            slots.push_back(uct);
        }
    }
    sort(slots.begin(), slots.end(), cmp_day);
    return slots;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n).
/// @param uc 
/// @return Retorna um vetor de Slots da UC passada como argumento.
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
    sort(slots.begin(), slots.end(), cmp_day);
    return slots;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n).
/// @param clss 
/// @return Retorna um vetor de Slots da turma passada como argumento.
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
    sort(slots.begin(), slots.end(), cmp_day);
    return slots;
}

/// @brief Função Get.
/// Esta função tem complexidade de O(n).
/// @param uct 
/// @return Retorna um vetor de Slots da UCTurma passada como argumento.
vector<Slot> ScheduleManag::getSlotsByClassAndUC(UCTurma uct) {
    vector<Slot> slots;
    // complexity O(n)
    for(auto slot : class_uc_map_slots[uct]) {
        slots.push_back(slot);
    }
    sort(slots.begin(), slots.end(), cmp_day);
    return slots;
}

/// @brief Função que adiciona o estudante a uma UC, caso não existam confiltos.
/// Esta função verifica se o número de estudante e UC são válidos, se a UC passada em argumento tem vagas, se o estudante já se encontra na turma passada como argumento,
/// e se não existe overlapping entre o horário anterior do estudante e a nova UC à qual este será inscrito.
/// Esta função tem complexidade de O(n³)
/// @param student 
/// @param uc 
/// @return Retorna True se o estudante for adicionado à UC, False caso contrário.
bool ScheduleManag::addStudentToUC(Student student, string uc) {
    bool can_add = false;

    // check if student exists in students_set
    auto it = students_set.find(student);
    if(it != students_set.end()) {
        // check if the student is already in the uc
        for(auto uct : it->classes) {
            if(uct.uc == uc) {
                cout << "Student already in uc" << endl;
                return false;
            }
        }
    } else {
        // if studet doenst exist, cout error
        cout << "Student doesn't exist" << endl;
        return false;
    }

    //check for the first class of the uc that has less than max_students
    for (auto const& [key, val] : this->class_uc_map_slots) {
        if(key.uc == uc) {
            // check if the slots that are PL or TP dont overlap with the student's slots
            // for the UCs that the student is already in
            vector<Slot> student_slots = this->getSlotsByStudent(student);
            for(auto const& slot : val) {
                if(slot.type == "PL" || slot.type == "TP") {
                    // check if the student has a slot that overlaps with this slot
                    for(auto const& student_slot : student_slots) {
                        if(student_slot.type == "PL" || student_slot.type == "TP") {
                            // check if the slots overlap in any way
                            if(!((student_slot.startHour <= slot.startHour + slot.duration) && (slot.startHour <= student_slot.startHour + student_slot.duration))) {
                                // if it overlaps, dont add the student to this class
                                can_add = true;
                                break;
                            }
                        }
                    }
                }
            }
            if(!can_add) {
                cout << "The slots of type PL/TP of the class overlap with the ones already in the student or the uc/class doesn't exist" << endl;
                return false;
            }
            // check if class has less than max_students
            if(getStudentsByClassAndUC(key).size() < this->max_students && can_add) {
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
                return true;
            }
        }
    }
    // all the classes are full, so print an error
    cout << "All classes are full" << endl;
    return false;
}

/// @brief Cria uma struct com os argumentos da função addStudentToUC que é passada para a queue de pedidos.
/// @param student 
/// @param uc 
void ScheduleManag::addStudentToUCQ(Student student, string uc) {
    // create variable of type StudentQ with the arguments
    // UCTurma is takes an empty turma because it is not used in the addStudentToUC function
    // and will be used to differentiate between addStudentToUC and addStudentToClassAndUC
    StudentQ sq {student, UCTurma(uc, "")};
    // add the variable to the queue
    this->class_add_queue.push(sq);
}

/// @brief Função que adiciona um estudante a uma UCTurma, caso não existam conflitos.
/// Esta função verifica se o número de estudante e UCTurma são válidos, se a UCTurma passada em argumento tem vagas, se o estudante já se encontra na uct passada como argumento,
/// e se não existe overlapping entre o horário anterior do estudante e a nova UCTurma onde será colocado.
/// Esta função tem complexidade de O(n²)
/// @param student 
/// @param uct 
/// @return 
bool ScheduleManag::addStudentToClassAndUC(Student student, UCTurma uct) {
    bool can_add = false;

    // check if student exists in students_set
    auto it = students_set.find(student);
    if(it != students_set.end()) {
        // check if the student is already in the uc
        for(auto ucturma : it->classes) {
            if(ucturma.uc == uct.uc) {
                cout << "Student already in uc" << endl;
                return false;
            }
        }
    } else {
        // if studet doenst exist, cout error
        cout << "Student doesn't exist" << endl;
        return false;
    }

    // check if the slots that are PL or TP dont overlap with the student's slots
    // for the UCs that the student is already in
    vector<Slot> student_slots = this->getSlotsByStudent(student);
    for(auto const& slot : this->getSlotsByClassAndUC(uct)) {
        if(slot.type == "PL" || slot.type == "TP") {
            // check if the student has a slot that overlaps with this slot
            for(auto const& student_slot : student_slots) {
                if(student_slot.type == "PL" || student_slot.type == "TP") {
                    if(!((student_slot.startHour <= slot.startHour + slot.duration) && (slot.startHour <= student_slot.startHour + student_slot.duration))) {
                        // if it overlaps, dont add the student to this class
                        can_add = true;
                        break;
                    }
                }
            }
        }
    }
    if (!can_add) {
        cout << "The slots of type PL/TP of the class overlap with the ones already in the student or the uc/class doesn't exist" << endl;
        return false;
    }
    // check if the class has less than max_students
    if(getStudentsByClassAndUC(uct).size() < max_students) {
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
        return true;
    }
    // all the classes are full, so print an error
    cout << "All classes are full" << endl;
    return false;
}

/// @brief Cria uma struct com os argumentos da função addStudentToClassAndUC que é passada para a queue de pedidos.
/// @param student 
/// @param uc 
void ScheduleManag::addStudentToClassAndUCQ(Student student, UCTurma uct) {
    // create variable of type StudentQ with the arguments
    StudentQ sq {student, uct};
    // add the variable to the queue
    this->class_add_queue.push(sq);
}

/// @brief Remove um estudante de uma determinada turma.
/// @param student 
/// @param clss 
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

/// @brief Remove um estudante de uma UC.
/// O estudante é também removido de todas as UCTurmas associadas a essa UC.
/// Esta função tem complexidade de O(n).
/// @param student 
/// @param uc 
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

/// @brief Cria uma struct com os argumentos da função removeStudentFromUC que é passada para a queue de pedidos.
/// @param student 
/// @param uc 
void ScheduleManag::removeStudentFromUCQ(Student student, string uc) {
    // create variable of type StudentQ with the arguments
    // UCTurma is takes an empty turma because it is not used in the removeStudentFromUC function
    // and will be used to differentiate between removeStudentFromUC and removeStudentFromClassAndUC
    StudentQ sq {student, UCTurma(uc, "")};
    // add the variable to the queue
    this->class_remove_queue.push(sq);
}

/// @brief Função que remove um estudante de uma UCTurma.
/// Esta função tem complexidade de O(n).
/// @param student 
/// @param uct 
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

/// @brief Cria uma struct com os argumentos da função removeStudentFromClassAndUC que é passada para a queue de pedidos.
/// @param student 
/// @param uct 
void ScheduleManag::removeStudentFromClassAndUCQ(Student student, UCTurma uct) {
    // create variable of type StudentQ with the arguments
    StudentQ sq {student, uct};
    // add the variable to the queue
    this->class_remove_queue.push(sq);
}

/// @brief Cria uma struct com os argumentos das funções addStudentToClassAndUC e removeStudentFromClassAndUC que é passada para a queue de pedidos.
/// @param student 
/// @param old_uct 
/// @param new_uct 
void ScheduleManag::modifyStudentsClassAndUCQ(Student student, UCTurma old_uct, UCTurma new_uct) {
    // create variable of type StudentQModify with the arguments
    StudentQModify sq {student, old_uct, new_uct};
    // add the variable to the modify queue
    this->class_modify_queue.push(sq);
}

/// @brief Função que processa sequencialmente, todos os pedidos armazenados na queue.
/// Esta função tem complexidade de O(n).
void ScheduleManag::endDay() {
    // go over each queue and execute the actions

    // queue of students to be added to a class
    while(!class_add_queue.empty()) {
        // get the first element of the queue
        StudentQ sq = class_add_queue.front();
        cout << "[*] Adding student " << sq.student.name << " to class " << sq.uct.turma << " of UC " << sq.uct.uc << endl;
        // remove the first element of the queue
        class_add_queue.pop();
        // check if the queue is for addStudentToClassAndUC or addStudentToUC
        if(sq.uct.turma == "") {
            // addStudentToUC if turma is empty
            if (!addStudentToUC(sq.student, sq.uct.uc)) {
                // if the student could not be added to the uc, add the request to not_executed_requests_add
                not_executed_requests_add.push_back(sq);
            }
        } else {
            // addStudentToClassAndUC if we have a full UCTurma object
            if (!addStudentToClassAndUC(sq.student, sq.uct)) {
                // if the student could not be added to the class, add the request to not_executed_requests_add
                not_executed_requests_add.push_back(sq);
            }
        }
    }

    // queue of students to be removed from a class
    while(!class_remove_queue.empty()) {
        // get the first element of the queue
        StudentQ sq = class_remove_queue.front();
        cout << "[*] Removing student " << sq.student.name << " from class " << sq.uct.turma << " of UC " << sq.uct.uc << endl;
        // remove the first element of the queue
        class_remove_queue.pop();
        // check if the queue is for removeStudentFromClassAndUC or removeStudentFromUC
        if(sq.uct.turma == "") {
            // removeStudentFromUC if turma is empty
            removeStudentFromUC(sq.student, sq.uct.uc);
        } else {
            // removeStudentFromClassAndUC if we have a full UCTurma object
            removeStudentFromClassAndUC(sq.student, sq.uct);
        }
    }

    // queue of students to be modified
    while(!class_modify_queue.empty()) {
        // get the first element of the queue
        StudentQModify sq = class_modify_queue.front();
        cout << "[*] Modifying student " << sq.student.name << " from class " << sq.old_uct.turma << " of UC " << sq.old_uct.uc << " to class " << sq.new_uct.turma << " of UC " << sq.new_uct.uc << endl;
        // remove the first element of the queue
        class_modify_queue.pop();
        // remove the student from the old class
        removeStudentFromClassAndUC(sq.student, sq.old_uct);
        // add the student to the new class
        if (!addStudentToClassAndUC(sq.student, sq.new_uct)) {
            // if the student could not be added to the new class, add them back to the old class
            addStudentToClassAndUC(sq.student, sq.old_uct);

            // add to the not_executed queue
            not_executed_requests_modify.push_back(sq);
        }
    }

}