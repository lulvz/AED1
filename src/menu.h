//
// Created by lulas on 10/19/2022.
//

#ifndef AED_PROJETO_MENU_H
#define AED_PROJETO_MENU_H

#include <string>
#include "schedule_manag.h"

using namespace std;

/// @brief Classe responável pela interface da aplicação.
class Menu {
    public:
        Menu(string cuf, string csf, string scf, int students_max, string cufw, string csfw, string scfw);
        void printBaseMenu();
        void printMenu1();
        void printMenu2();
        void printMenu3();

        int baseMenuLoop();
    
    private:
        ScheduleManag sm;
};

#endif //AED_PROJETO_MENU_H
