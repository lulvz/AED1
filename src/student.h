#ifndef STUDENT_H
#define STUDENT_H

#include "uc_turma.h"
#include <string>
#include <list>

class Student {
    public:
        Student(std::string code, std::string name) {
            this->code = code;
            this->name = name;
        }
        
        bool operator< (const Student &s) {
            return code < s.code;
        }

        std::string name, code;
};

namespace std{
    template<>
    struct less<Student>{
    bool operator() (const Student &lhs, const Student &rhs) {
        return lhs.code < rhs.code;
    }};
}
#endif