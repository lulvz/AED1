//
// Created by lulas on 10/18/2022.
//

#ifndef SCHEDULE_MANAG_H
#define SCHEDULE_MANAG_H

#include "student.h"
#include "class_schedule.h"
#include <vector>
#include <set>

class ScheduleManag {
    public:
        ScheduleManag(std::set<Student> students, std::vector<ClassSchedule> schedules) {
            this->students = students;
            this->schedules = schedules;
        }
        
    private:
        std::set<Student> students;
        std::vector<ClassSchedule> schedules;


};

#endif //SCHEDULE_MANAG_H
