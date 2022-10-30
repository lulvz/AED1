#ifndef STUDENT_H
#define STUDENT_H

#include "uc_turma.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

class Student {
    public:
        Student(std::string code, std::string name) {
            this->code = code;
            this->name = name;
        }
        Student() {
            this->code = "";
            this->name = "";
        }
        
        bool operator< (const Student &s) {
            return code < s.code;
        }

        bool operator== (const Student &s)  {
            return code == s.code;
        }

        friend std::ostream& operator<<(std::ostream& os, const Student& student) {
            os << student.code;
            return os;
        }

        void addclass(UCTurma ucTurma) {
            classes.push_back(ucTurma);
        }
        void removeclass(UCTurma ucTurma) {
            classes.erase(std::remove(classes.begin(), classes.end(), ucTurma), classes.end());
        }

        std::string name, code;
        std::vector<UCTurma> classes; // classes that the student is enrolled in
};

namespace std{
    template<>
    struct less<Student>{
    bool operator() (const Student &lhs, const Student &rhs) {
        return lhs.code < rhs.code;
    }};
}
#endif