#ifndef CLASS_SCHEDULE_H
#define CLASS_SCHEDULE_H

#include <string>
#include "class_uc.h"
class ClassSchedule {
    public:
        ClassUc cuc;
        std::string weekDay, type;
        float startHour, duration;
};

#endif