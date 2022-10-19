#ifndef CLASS_SCHEDULE_H
#define CLASS_SCHEDULE_H

#include <string>
#include <list>
#include "uc_turma.h"
#include "slot.h"
class ClassSchedule {
    public:
        std::string uc, turma;
        std::list<Slot> horaUcTurma;
};

#endif