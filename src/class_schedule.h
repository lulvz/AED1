#ifndef CLASS_SCHEDULE_H
#define CLASS_SCHEDULE_H

#include <string>
#include <vector>
#include "uc_turma.h"
#include "slot.h"

/// @brief Classe que representa um hoŕario de uma UCTurma.
class ClassSchedule {
    public:
        /*! @brief Construtor de ClassSChedule.
        *   Cria um novo horário para uma UCTurma, segundo os argumentos passados.
        *   
        *   @param[in] slots
        *   @param[in] classUC
        */
        ClassSchedule(std::vector <Slot> slots, UCTurma classUc) : class_uc(classUc), horaUcTurma(slots){ }

        UCTurma class_uc;
        std::vector<Slot> horaUcTurma;
};

#endif