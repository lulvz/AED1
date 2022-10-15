#ifndef STUDENT_H
#define STUDENT_H
#include "class_uc.h"
#include <string>

struct Student {
    ClassUc cuc;
    std::string name, code;   
};
#endif