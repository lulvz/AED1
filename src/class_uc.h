#ifndef CLASS_UC_H
#define CLASS_UC_H

#include <string>
#include <algorithm>
#include <vector>

class ClassUc {
    public:
        std::string uc_code, class_code;
        int sort();
};

void cuc_sort_code(std::vector<ClassUc> &cuc);

#endif