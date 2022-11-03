#ifndef STUDENT_H
#define STUDENT_H

#include "uc_turma.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

/*! @brief Classe que representa um estudante.
*
*   Cada estudante tem um nome e um código, e pode estar em várias UCTurmas.
*/

class Student {
    public:
        /*! @brief Construtor da classe Student.
        *   Substituí os valores das variáveis da classe pelos valores passados em argumento.
        *   
        *   @param[in] code
        *   @param[in] name
        */

        Student(std::string code, std::string name) {
            this->code = code;
            this->name = name;
        }

        /*! @brief Construtor por omissão da classe Student.
        *   Substituí os valores das variáveis da classe pela string vazia ("").
        */

        Student() {
            this->code = "";
            this->name = "";
        }
        
        /*! @brief Overload do operador menor (<).
        *   
        *   @return Retorna True se o código do Student à esquerda do operador for menor do que está à direita deste.
        */

        bool operator< (const Student &s) {
            return code < s.code;
        }

        /*! @brief Overload do operador ==.
        *   
        *   @return Retorna True se o código dos dois objetos Student a serem comparados for igual.
        */

        bool operator== (const Student &s)  {
            return code == s.code;
        }

        /*! @brief Overload do operador <<.
        *   @param[in] os
        *   @param[in] student
        *   
        *   @return Retorna um objeto ostream, contendo o código do estudante.
        */

        friend std::ostream& operator<<(std::ostream& os, const Student& student) {
            os << student.code;
            return os;
        }
        
        /*! @brief Adiciona uma uma nova UCTurma ao estudante.
        *   @param[in] ucTurma
        */

        void addclass(UCTurma ucTurma) {
            classes.push_back(ucTurma);
        }

        /*! @brief Remove um estudante da UCTurma especificada.
        *   @param[in] ucTurma
        */

        void removeclass(UCTurma ucTurma) {
            classes.erase(std::remove(classes.begin(), classes.end(), ucTurma), classes.end());
        }

        /// @brief Nome do estudante.
        std::string name;
        /// @brief Código do estudante.
        std::string code;
        /// @brief Vetor das UCTurmas onde o estudante está inserido.
        std::vector<UCTurma> classes;
};

/// @brief Namespace contendo overload da função less (usada em sets).
namespace std{
    template<>
    /// @brief Operador less com objetos Student.
    struct less<Student>{
    /*! @brief Overload do operador less.
    *   Função de ultilidade para construir sets com objetos Student.
    *   
    *   @param[in] lhs
    *   @param[in] rhs
    * 
    *   @return Retorna True se o código do estudante lhs for menor que o código do estudante rhs.
    */
    bool operator() (const Student &lhs, const Student &rhs) {
        return lhs.code < rhs.code;
    }};
}
#endif