#ifndef CLASS_SCHEDULE_H
#define CLASS_SCHEDULE_H

#include <string>
#include <list>
#include "uc_turma.h"
#include "slot.h"
using namespace std;

class ClassSchedule {
    public:
        ClassSchedule(list <Slot> slots, UCTurma classUc) : class_uc(classUc), horaUcTurma(slots){ }

        UCTurma class_uc;
        std::list<Slot> horaUcTurma;
};

#endif