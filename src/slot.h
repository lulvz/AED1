//
// Created by lulas on 10/18/2022.
//

#ifndef AED_PROJETO_SLOT_H
#define AED_PROJETO_SLOT_H

#include <string>
#include "uc_turma.h"

/*! @brief Classe que representa um horário.
*   Um objeto Slot pode estar associado a outras classes (Student).
*/

class Slot {
    public:
        /*! @brief Construtor da classe Slot.
        *   Substitui os valores das variáveis internas á classe pelo valor das variáveis passadas como argumento.
        *
        *   @param[in] weekDay
        *   @param[in] startHour
        *   @param[in] duration
        *   @param[in] type
        *   @param[in] uct
        */

        Slot(std::string weekDay, float startHour, float duration, std::string type, UCTurma uct) : uct(uct){
            this->weekDay = weekDay;
            this->startHour = startHour;
            this->duration = duration;
            this->type = type;
        }
        
        /// @brief Dia da semana em que ocorre a aula.
        std::string weekDay;
        /// @brief Tipo de aula.
        std::string type;
        /// @brief Hora de começo da aula.
        float startHour;
        /// @brief Duração em horas da aula.
        float duration;
        /// @brief UCTurma associada à aula.
        UCTurma uct;
};

#endif //AED_PROJETO_SLOT_H
