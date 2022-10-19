//
// Created by lulas on 10/19/2022.
//

#include <iostream>

#include "menu.h"

using namespace std;

menu::menu() {};

void menu::printBaseMenu() {
    cout << "Menu" << endl;
    cout << "1 - Informações gerais" << endl;	    // 1 - Informações sobre o horário
    cout << "2 - Efetuar um pedido de alteração gerais" << endl;	    // 2 - Pedidos de alteração
    cout << "3 - Acabar dia" << endl;        // 3 - Acabar dia
}

void menu::printMenu1() {
    cout << "1 - Ocupação das turmas" << endl;	    // 1 - Ocupação das turmas
    cout << "2 - Estudantes numa determinada turma" << endl;	    // 2 - Estudantes na turma x
    cout << "3 - Estudantes com mais de x unidades curriculares" << endl;	    // 3 - Estudantes com mais de x unidades curriculares
    cout << "4 - Estudantes por unidade curricular" << endl;	    // 4 - Estudantes por unidade curricular
}

void menu::printMenu2() {
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