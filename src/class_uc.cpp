//
// Created by lulas on 10/15/2022.
//
#include "class_uc.h"

void cuc_sort_code(std::vector<ClassUc> &cuc) {
    std::sort(cuc.begin(), cuc.end(), [](ClassUc a, ClassUc b) {
        return a.uc_code < b.uc_code;
    });
}