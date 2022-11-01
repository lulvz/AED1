//
// Created by lulas on 10/19/2022.
//

#include "./menu.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "./uc_turma.h"
#include "./class_schedule.h"
#include "./student.h"
#include "./schedule_manag.h"

#include "utility/csv_reader.h"

#include "utility/bst.h"
#include "student.h"

using namespace std;

Menu::Menu(string cuf, string csf, string scf, int students_max, string cufw, string csfw, string scfw) : sm(cuf, csf, scf, students_max, cufw, csfw, scfw) {
        sm.readFiles();
    }

void Menu::printBaseMenu() {
    cout << "Menu" << endl;
    cout << "0 - Sair" << endl;
    cout << "1 - Informações gerais" << endl;	    // 1 - Informações sobre o horário
    cout << "2 - Informações sobre o horário" << endl;	// 2 - Informações sobre o horário
    cout << "3 - Efetuar pedidos de alteração gerais" << endl;	    // 3 - Pedidos de alteração
    cout << "4 - Acabar dia" << endl;        // 4 - Acabar dia
    cout << "exit - Sair" << endl;
}

void Menu::printMenu1() {
    bool running = true;
    while(running) {
        cout << "0 - Voltar" << endl;
        cout << "1 - Ocupação das turmas" << endl;	    // 1 - Ocupação das turmas
        cout << "2 - Estudantes numa determinada turma" << endl;	    // 2 - Estudantes na turma x
        cout << "3 - Estudantes com mais de x unidades curriculares" << endl;	    // 3 - Estudantes com mais de x unidades curriculares
        cout << "4 - Estudantes por unidade curricular" << endl;	    // 4 - Estudantes por unidade curricular
        cout << "5 - Turmas e UCs de um estudante" << endl;        // 5 - Turmas e UCs de um estudante
        cout << "6 - Estudantes por turma" << endl;        // 6 - Estudantes por turma

        cout << "Opção pretendida: ";
        int opt1 = 0;
        cin >> opt1; cout << endl;

        switch(opt1) {
            case 0:
                running = false;
                break;
            case 1:
                // mostrar alunos em cada turma de cada uc
                // go over each uc
                for(auto uc : sm.getUCs()) {
                    // go over each class
                    for(auto c : sm.getStudentsByUC(uc)) {
                        //
                    }
                }
                
                break;
            case 2:
                {
                cout << "Turma a consultar: ";
                string turma = "";
                cin >> turma; cout << endl;
                set<Student> stByclss = sm.getStudentsByClass(turma);
                if (stByclss.size() == 0) { 
                    cout << "Turma inválida." << endl;
                }
                else {
                    cout << "Estudantes na turma " << turma << ":" << endl;
                    for (Student i : stByclss) {
                        cout << i.code << ", " << i.name << endl;
                    }
                }
                cout << endl;
                break;
                }
            case 3:
                {
                cout << "Número de unidades curriculares: ";
                int n_ucs = 0;
                cin >> n_ucs; cout << endl;

                vector<Student> stXuc = sm.getStudentsWithMoreThanXUC(n_ucs);
                if (stXuc.size() == 0) { 
                    cout << "Não existem estudantes com mais do que " << n_ucs << " ucs." << endl;
                }
                else {
                    cout << "Estudantes com mais que " << n_ucs << " ucs:" << endl;
                    for (Student i: stXuc) {
                        cout << i.code << ", " << i.name << endl;
                    }
                }
                cout << endl;
                break;
                }
            case 4:
                {
                cout << "UC pretendida: ";
                string uc_ = "";
                cin >> uc_; cout << "\n";
                set<Student> stByuc = sm.getStudentsByUC(uc_);
                if (stByuc.size() == 0) {
                    cout << "Não existem estudantes associados a esta UC." << endl;
                }
                else {
                    cout << "Estudantes na unidade curricular " << uc_ << ":" << endl;
                    for (Student i: stByuc) {
                        cout << i.code << ", " << i.name << endl;
                    }
                }
                cout << endl;
                break;
                }
            case 5:
                {
                string n_std = "", st_code = "";
                cout << "Nome de estudante: " << endl;
                getline(cin >> std::ws, n_std); cout << endl;
                cout << "Código de estudante: " << endl;
                cin >> st_code; 
                cout << endl << endl;

                vector<UCTurma> UCTbySt = sm.getUCTsByStudent(Student(st_code, n_std));

                if(UCTbySt.size() == 0){
                    cout << "Não existem turmas/ucs associadas a este estudante." << endl;
                }
                else {
                    cout << "Turmas e UCs de " << n_std << ":" << endl;
                    for (UCTurma i: UCTbySt) {
                        cout << i.uc << ", " << i.turma << endl;
                    }
                }

                break;
                }
            case 6:
                {
                cout << "Turma a consultar: ";
                string turma = "";
                cin >> turma; cout << endl;
                set<Student> stByclss = sm.getStudentsByClass(turma);
                if (stByclss.size() == 0) { 
                    cout << "Turma inválida ou sem estudantes." << endl;
                }
                else {
                    cout << "Estudantes na turma " << turma << ":" << endl;
                    for (Student i : stByclss) {
                        cout << i.code << ", " << i.name << endl;
                    }
                }

                break;
                }
            default:
                {
                cout << "Número de opção inválido." << endl;
                break;
                }
        } 
    }
}

// TOTALMENTE FEITO
void Menu::printMenu2() {
    bool running = true;
    while (running) {
        cout << "0 - Voltar" << endl;
        cout << "1 - Horário de um estudante" << endl;	    // 1 - Horário de um estudante
        cout << "2 - Horário de uma turma" << endl;	    // 2 - Horário de uma turma
        cout << "3 - Horário de uma unidade curricular" << endl;	    // 3 - Horário de uma unidade curricular
        cout << "4 - Horário de uma turma numa determinada unidade curricular" << endl;	    // 4 - Horário de uma turma e unidade curricular

        cout << "Opção pretendida: ";
        int opt2 = 0;
        cin >> opt2; cout << endl;
        switch(opt2) {
            case 0:
                {
                running = false;
                break;
                }
            case 1:
                {
                string n_std = "", st_code = "";
                cout << "Nome de estudante: " << endl;
                getline(cin >> std::ws, n_std); cout << endl;
                cout << "Código de estudante: " << endl;
                cin >> st_code; 
                cout << endl << endl;

                vector<Slot> SlotByst = sm.getSlotsByStudent(Student(st_code, n_std));
                if (SlotByst.size() == 0) {
                    cout << "O Estudante não tem horário atribuídos.";
                    break;
                }
                else {
                    cout << "Horário do estudante " << n_std << " (" << st_code << "):" << endl;
                    cout << "UC/Turma: Dia\tHora de começo\tDuração\tTipo de aula" << endl;
                    for (Slot i: SlotByst) {
                        cout << i.uct.uc << "/" << i.uct.turma << "\t" << i.weekDay << "\t" << i.startHour << "\t" << i.duration << "\t" << i.type << endl;
                    }
                }
                cout << endl;
                break;
                }
            case 2:
                {
                cout << "Código de turma: ";
                string c_turma = "";
                cin >> c_turma; cout << "\n";
                vector<Slot> SlotByclss = sm.getSlotsByClass(c_turma);
                if (SlotByclss.size() == 0) {
                    cout << "Esta turma não tem horários definidos." << endl;
                }
                else {
                    for (Slot i: SlotByclss) {
                        cout << i.uct.uc << "/" << i.uct.turma << "\t" << i.weekDay << "\t" << i.startHour << "\t" << i.duration << "\t" << i.type << endl;
                    }
                }
                cout << endl;
                break;
                }
            case 3:
                {
                cout << "UC pretendida: ";
                string uc_ = "";
                cin >> uc_; cout << "\n";
                vector<Slot> SlotByuc = sm.getSlotsByUC(uc_);
                if (SlotByuc.size() == 0) {
                    cout << "Esta UC não tem horários definidos." << endl;
                }
                else {
                    for (Slot i: SlotByuc) {
                        cout << i.uct.uc << "/" << i.uct.turma << "\t" << i.weekDay << "\t" << i.startHour << "\t" << i.duration << "\t" << i.type << endl;
                    }
                }
                cout << endl;
                break;
                }
            case 4:
                {
                cout << "UC pretendida: ";
                string uc_ = "";
                cin >> uc_; cout << "\n";
                cout << "Código de turma: ";
                string c_turma = "";
                cin >> c_turma; cout << "\n";
                vector<Slot> SlotByclssuc = sm.getSlotsByClassAndUC(UCTurma(uc_, c_turma));
                if (SlotByclssuc.size() == 0) {
                    cout << "Esta turma não tem horários definidos para esta UC." << endl;
                }
                else {
                    for (Slot i: SlotByclssuc) {
                        cout << i.uct.uc << "/" << i.uct.turma << "\t" << i.weekDay << "\t" << i.startHour << "\t" << i.duration << "\t" << i.type << endl;
                    }
                }
                cout << endl;
                break;
                }
            default:
                {
                cout << "Número de opção inválido." << endl;
                break;
                }
        }
    }
}

void Menu::printMenu3() {
    bool running = true;
    while(running) {
        cout << "0 - Voltar" << endl;
        cout << "1 - Adicionar estudante a Unidade Curricular" << endl;	    // 1 - Adicionar estudante a Unidade Curricular
        cout << "2 - Remove estudante de Unidade Curricular" << endl;	    // 2 - Remove estudante de Unidade Curricular
        cout << "3 - Alterar a turma de um estudante" << endl;	    // Alterar horário de uma turma
        cout << "4 - Alterar várias turmas de um estudante" << endl;	    // Alterar horário de um estudante

        cout << "Opção pretendida: ";
        int opt3 = 0;
        cin >> opt3; cout << "\n";
        switch(opt3) {
        case 0:
            {
            running = false;
            break;
            }
        case 1:
            {
            string n_std = "", st_code = "", uc_ = "";
            cout << "Nome de estudante: " << endl;
            getline(cin >> std::ws, n_std); cout << endl;
            cout << "Código de estudante: " << endl;
            cin >> st_code; 
            cout << endl << endl;

            cout << "UC pretendida: "; cin >> uc_; cout << endl;
            sm.addStudentToUC(Student(st_code, n_std), uc_);
            break;
            }
        case 2:
            {
            string n_std = "", st_code = "", uc_ = "";
            cout << "Nome de estudante: " << endl;
            getline(cin >> std::ws, n_std); cout << endl;
            cout << "Código de estudante: " << endl;
            cin >> st_code; 
            cout << endl << endl;

            cout << "UC pretendida: "; cin >> uc_; cout << endl;
            sm.removeStudentFromUC(Student(st_code, n_std), uc_);
            break;
            }
        case 3:
            {
            string n_std = "", st_code = "", uc_ = "", turma = "", turma_n = "";
            cout << "Nome de estudante: " << endl;
            getline(cin >> std::ws, n_std); cout << endl;
            cout << "Código de estudante: " << endl;
            cin >> st_code; 
            cout << endl << endl;

            cout << "UC pretendida: "; cin >> uc_; cout << endl;
            cout << "Turma anterior: "; cin >> turma; cout << endl;
            cout << "Nova turma: "; cin >> turma_n; cout << endl;
            sm.removeStudentFromClassAndUC(Student(st_code, n_std), UCTurma(uc_, turma));
            sm.addStudentToClassAndUC(Student(st_code, n_std), UCTurma(uc_, turma_n));
            break;
            }
        case 4:
            {
            string n_std = "", st_code = "", uc_ = "", turma = "", turma_n = "";
            cout << "Nome de estudante: " << endl;
            getline(cin >> std::ws, n_std); cout << endl;
            cout << "Código de estudante: " << endl;
            cin >> st_code; 
            cout << endl << endl;

            cout << "UC pretendida: "; cin >> uc_; cout << endl;
            
            cout << "Turmas a alterar (Deixar ambos os campos em branco para terminar): ";
            while (true) {
                cout << "Turma anterior: "; cin >> turma; cout << endl;
                cout << "Nova turma: "; cin >> turma_n; cout << endl;
                if (turma == "" || turma_n == "") { break; }
                else {
                    sm.removeStudentFromClassAndUC(Student(st_code, n_std), UCTurma(uc_, turma));
                    sm.addStudentToClassAndUC(Student(st_code, n_std), UCTurma(uc_, turma_n));
                }
            }
            break;
            }
        default:
            {
            cout << "Número de opção inválido."; cout << endl;
            break;
            }
        }
    }
}

int Menu::baseMenuLoop() {
    bool running = true;
    while (running) {
        printBaseMenu();
        cout << "Opção pretendida: ";
        int opt = 0;
        cin >> opt; cout << endl;
        switch(opt) {
            case 0:
                running = false;
                break;
            case 1:
                printMenu1();
                break;
            case 2:
                printMenu2();
                break;
            case 3:
                printMenu3();
                break;
            case 4:
                //...//
                break;
            default:
                cout << "Número de opção inválido." << endl;
                break;
        }
    }
    return 0;
} 


//ocupacao, tipo, dia, hora, duracao, uc, turma, alunos
//estudantes numa turma
//estudantes com mais de x unidades curriculares
//mostrar horario de um estudante
//mudar horario
//editar uc de um estudante
//acabar o dia
//sair