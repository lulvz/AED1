#ifndef CLASS_SCHEDULE_H
#define CLASS_SCHEDULE_H

#include <string>
#include <vector>
#include "uc_turma.h"
#include "slot.h"

class ClassSchedule {
    public:
        ClassSchedule(std::vector <Slot> slots, UCTurma classUc) : class_uc(classUc), horaUcTurma(slots){ }

        UCTurma class_uc;
        std::vector<Slot> horaUcTurma;
};

#endif