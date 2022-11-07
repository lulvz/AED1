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
struct cmp_name{
    bool operator() (const Student &lhs,const Student &rhs) const {
        return lhs.name < rhs.name;
    }};

/*! @brief Construtor da classe Menu.
*   
*   @param[in] cuf
*   @param[in] csf
*   @param[in] scf
*   @param[in] students_max
*   @param[in] cufw
*   @param[in] csfw
*   @param[in] scfw
*/
Menu::Menu(string cuf, string csf, string scf, int students_max, string cufw, string csfw, string scfw) : sm(cuf, csf, scf, students_max, cufw, csfw, scfw) {
        sm.readFiles();
    }

/// @brief Imprime para a consola o Menu inicial.
void Menu::printBaseMenu() {
    cout << "Menu" << endl;
    cout << "0 - Sair e gravar" << endl;
    cout << "1 - Informações gerais" << endl;	    // 1 - Informações sobre o horário
    cout << "2 - Informações sobre o horário" << endl;	// 2 - Informações sobre o horário
    cout << "3 - Efetuar pedidos de alteração gerais" << endl;	    // 3 - Pedidos de alteração
    cout << "4 - Acabar dia" << endl;        // 4 - Acabar dia
}

/*! @brief Imprime para a consola o Menu da opção 1.
*   Esta função serve de interface para a opção 1 do menu anterior.
*   Responsável pela chamada de todas as funções das outras classes para realizar as várias opções que pertencem á secção 1 do printBaseMenu().
*/
void Menu::printMenu1() {
    bool running = true;
    while(running) {
        cout << "0 - Voltar" << endl;
        cout << "1 - Ocupação das turmas" << endl;	    // 1 - Ocupação das turmas
        cout << "2 - Estudantes numa determinada turma" << endl;	    // 2 - Estudantes na turma x
        cout << "3 - Estudantes com mais de x unidades curriculares" << endl;	    // 3 - Estudantes com mais de x unidades curriculares
        cout << "4 - Estudantes por unidade curricular" << endl;	    // 4 - Estudantes por unidade curricular
        cout << "5 - Turmas e UCs de um estudante" << endl;        // 5 - Turmas e UCs de um estudante
        cout << "6 - UCs por ano" << endl;        // 6 - Estudantes por turma
        cout << "7 - Número de estudantes por turma em determinada UC" << endl; // 7- Número de estudantes por turma em determinada UC

        cout << "Opção pretendida: ";
        int opt1 = 0;
        cin >> opt1; cout << endl;

        switch(opt1) {
            case 0:
                running = false;
                break;
            case 1:
                {
                cout << "Ordenar por código de estudante ou por nome(c/n):";
                char p1;
                cin >> p1; cout << endl;
                if(p1 == 'n'){
                    // ocupaçao das turmas
                    for(auto [key, value] : sm.getClassUCMapSlots()) {
                        set<Student> s = sm.getStudentsByClassAndUC(key);
                        set<Student, cmp_name> s2;
                        for(Student h : s){
                            s2.insert(h);
                        }
                        cout << key.uc << " " << key.turma << " " << s2.size() << "/" << sm.getMaxStudents() << endl;

                        // print students
                        for(auto it = s2.begin(); it != s2.end(); it++) {
                            cout << it->code << " " << it->name << endl;
                        }
                        cout << endl;                   
                    }
                }
                else{
                    for(auto [key, value] : sm.getClassUCMapSlots()) {
                        set<Student> s = sm.getStudentsByClassAndUC(key);
                        cout << key.uc << " " << key.turma << " " << s.size() << "/" << sm.getMaxStudents() << endl;

                        // print students
                        for(auto it = s.begin(); it != s.end(); it++) {
                            cout << it->code << " " << it->name << endl;
                        }
                        cout << endl;                   
                    }

                }
                break;
                }
            case 2:
                {
                cout << "Turma a consultar: ";
                string turma = "";
                cin >> turma; cout << endl;
                cout << "Ordenar por código de estudante ou por nome(c/n):";
                char p2;
                cin >> p2; cout << endl; 
                if(p2 == 'n'){
                    set<Student> stByclss = sm.getStudentsByClass(turma);
                    set<Student, cmp_name> stByclssName;
                        for(Student h : stByclss){
                            stByclssName.insert(h);
                        }
                    if (stByclssName.size() == 0) { 
                        cout << "Turma inválida." << endl;
                    }
                    else {
                        cout << "Estudantes na turma " << turma << ":" << endl;
                        for (Student i : stByclssName) {
                            cout << i.code << ", " << i.name << endl;
                        }
                    }
                }
                else{
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
                }
                cout << endl;            
                break;
                }
            case 3:
                {
                cout << "Número de unidades curriculares: ";
                int n_ucs = 0;
                cin >> n_ucs; cout << endl;
                cout << "Ordenar por código de estudante ou por nome(c/n):";
                char p3;
                cin >> p3; cout << endl;

                if(p3 == 'n'){
                vector<Student> stXuc = sm.getStudentsWithMoreThanXUC(n_ucs);
                set<Student, cmp_name> stXucName;
                    for(Student h : stXuc){
                        stXucName.insert(h);
                    }
                if (stXucName.size() == 0) { 
                    cout << "Não existem estudantes com mais do que " << n_ucs << " ucs." << endl;
                }
                else {
                    cout << "Estudantes com mais que " << n_ucs << " ucs:" << endl;
                    for (Student i: stXucName) {
                        cout << i.code << ", " << i.name << endl;
                    }
                }
                }
                else{
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

                }
                cout << endl;
                break;
                }
            case 4:
                {
                cout << "UC pretendida: ";
                string uc_ = "";
                cin >> uc_; cout << "\n";
                cout << "Ordenar por código de estudante ou por nome(c/n):";
                char p4;
                cin >> p4; cout << endl;
                if(p4 == 'n'){
                    set<Student> stByuc = sm.getStudentsByUC(uc_);
                    set<Student, cmp_name> stByucName;
                    for(Student h : stByuc){
                        stByucName.insert(h);
                    }
                    if (stByucName.size() == 0) {
                        cout << "Não existem estudantes associados a esta UC." << endl;
                    }
                    else {
                        cout << "Estudantes na unidade curricular " << uc_ << ":" << endl;
                        for (Student i: stByucName) {
                            cout << i.code << ", " << i.name << endl;
                        }
                    }
                }
                else{
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
                cout << "Ano:";
                char a;
                cin >> a;
                set<string> res;
                vector<UCTurma> nt = sm.getUCTs();
                if (a == '1' || a == '2' || a == '3') {
                    for (UCTurma tmp: nt) {
                        if (tmp.turma[0] == a) {
                            res.insert(tmp.uc);
                        }
                    }
                    cout << a << "º ano UCs" << endl;
                    for (string i: res) {
                        cout << i << endl;
                    }
                    cout << endl;
                }
                else{
                    cout << "Ano inválido" << endl << endl;
                }

                break;
                }
            case 7: {
                cout << "Unidade Curricular:";
                string uc;
                cin >> uc;
                map<string, int> map1 = sm.numberUCperClass(uc);
                for (auto kv: map1) {
                    cout << kv.first << ' ' << kv.second << endl;
                }
                cout << endl;
                if (map1.empty()) {
                    cout << "UC inválida";
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

/*! @brief Imprime para a consola o Menu da opção 2.
*   Esta função serve de interface para a opção 2 do menu anterior.
*   Responsável pela chamada de todas as funções das outras classes para realizar as várias opções que pertencem á secção 2 do printBaseMenu().
*/
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
                    cout << "UC/Turma: Dia\tHora de começo\tDuração\tTipo de aula" << endl;
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
                    cout << "UC/Turma: Dia\tHora de começo\tDuração\tTipo de aula" << endl;
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
                    cout << "UC/Turma: Dia\tHora de começo\tDuração\tTipo de aula" << endl;
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

/*! @brief Imprime para a consola o Menu da opção 3.
*   Esta função serve de interface para a opção 3 do menu anterior.
*   Responsável pela chamada de todas as funções das outras classes para realizar as várias opções que pertencem á secção 3 do printBaseMenu().
*/
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
            
            // add to the queue
            sm.addStudentToUCQ(Student(st_code, n_std), uc_);
            cout << "Alteração adicionada à fila de espera." << endl;
            
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
            
            // add to the queue
            sm.removeStudentFromUCQ(Student(st_code, n_std), uc_);
            cout << "Alteração adicionada à fila de espera." << endl;

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
            
            // add to the queue
            sm.modifyStudentsClassAndUCQ(Student(st_code, n_std), UCTurma(uc_, turma), UCTurma(uc_, turma_n));
            cout << "Alteração adicionada à fila de espera." << endl;
            
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

            cout << "Turmas e UCs a alterar (escrever 0 em qualquer campo para voltar) \n";
            while (true) {
                cout << "UC pretendida: "; cin >> uc_; cout << endl;
                if (uc_ == "0") break;
                cout << "Turma anterior: "; cin >> turma; cout << endl;
                if (turma == "0") break;
                cout << "Nova turma: "; cin >> turma_n; cout << endl;
                if (turma_n == "0") break;
                else {
                    // add to the queue
                    sm.modifyStudentsClassAndUCQ(Student(st_code, n_std), UCTurma(uc_, turma), UCTurma(uc_, turma_n));
                    cout << "Alteração adicionada à fila de espera." << endl;
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

/*! @brief Função responsável por manter o programa a correr até que o utilizador o termine voluntariamente.
*   É também responsável pela chamada de algumas opções do Menu inicial (como a finalização do dia, opção que escreve as alterações para os ficheiros dos 
    horários).
*/
int Menu::baseMenuLoop() {
    bool running = true;
    while (running) {
        printBaseMenu();
        cout << "Opção pretendida: ";
        int opt = 0;
        cin >> opt; cout << endl;
        switch(opt) {
            case 0:
                sm.writeFiles();
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
                cout << "Executando alterações em espera..." << endl;	
                sm.endDay();
                cout << "Alterações executadas." << endl;
                break;
            default:
                cout << "Número de opção inválido." << endl;
                break;
        }
    }
    return 0;
} 
