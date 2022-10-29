//
// Created by lulas on 10/19/2022.
//

#include <iostream>

#include "menu.h"

using namespace std;

Menu::Menu() {};

void Menu::printBaseMenu() {
    cout << "Menu" << endl;
    cout << "1 - Informações gerais" << endl;	    // 1 - Informações sobre o horário
    cout << "2 - Informações sobre o horário" << endl;	// 2 - Informações sobre o horário
    cout << "3 - Efetuar um pedido de alteração gerais" << endl;	    // 3 - Pedidos de alteração
    cout << "3 - Acabar dia" << endl;        // 4 - Acabar dia
    cout << "exit - Sair" << endl;
}

void Menu::printMenu1() {
    cout << "1 - Ocupação das turmas" << endl;	    // 1 - Ocupação das turmas
    cout << "2 - Estudantes numa determinada turma" << endl;	    // 2 - Estudantes na turma x
    cout << "3 - Estudantes com mais de x unidades curriculares" << endl;	    // 3 - Estudantes com mais de x unidades curriculares
    cout << "4 - Estudantes por unidade curricular" << endl;	    // 4 - Estudantes por unidade curricular
}

void Menu::printMenu2() {
    cout << "1 - Horário de um estudante" << endl;	    // 1 - Horário de um estudante
    cout << "2 - Horário de uma turma" << endl;	    // 2 - Horário de uma turma
    cout << "3 - Horário de uma unidade curricular" << endl;	    // 3 - Horário de uma unidade curricular
    cout << "4 - Horário de uma turma numa determinada unidade curricular" << endl;	    // 4 - Horário de uma turma e unidade curricular
}

void Menu::printMenu3() {
    cout << "1 - Adicionar estudante a Unidade Curricular" << endl;	    // 1 - Adicionar estudante a Unidade Curricular
    cout << "2 - Remove estudante de Unidade Curricular" << endl;	    // 2 - Remove estudante de Unidade Curricular
    cout << "3 - Alterar a turma de um estudante" << endl;	    // Alterar horário de uma turma
    cout << "4 - Alterar várias turmas de um estudante" << endl;	    // Alterar horário de um estudante
}

//ocupacao, tipo, dia, hora, duracao, uc, turma, alunos
//estudantes numa turma
//estudantes com mais de x unidades curriculares
//mostrar horario de um estudante
//mudar horario
//editar uc de um estudante
//acabar o dia
//sair