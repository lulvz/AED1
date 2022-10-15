#ifndef CLASS_SCHEDULE_H
#define CLASS_SCHEDULE_H

#include <string>
#include "class_uc.h"
struct ClassSchedule {
    ClassUc cuc;
    std::string weekDay, type;
    int startHour, duration; 
};

#endif