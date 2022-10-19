#ifndef STUDENT_H
#define STUDENT_H

#include "uc_turma.h"
#include <string>
#include <list>

class Student {
    public:
        std::string name, code;
        std::list<UCTurma> turmas;
        bool operator< (const Student &s) {
            return code < s.code;
        }
};
#endif