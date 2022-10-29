//
// Created by lulas on 10/18/2022.
//

#ifndef AED_PROJETO_SLOT_H
#define AED_PROJETO_SLOT_H

#include <string>

class Slot {
    public:
        Slot(std::string weekDay, float startHour, float duration, std::string type, UCTurma uct) : uct(uct){
            this->weekDay = weekDay;
            this->startHour = startHour;
            this->duration = duration;
            this->type = type;
        }
        
        std::string weekDay, type;
        float startHour, duration;

        UCTurma uct;
};

#endif //AED_PROJETO_SLOT_H
