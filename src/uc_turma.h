//
// Created by lulas on 10/18/2022.
//

#ifndef AED_PROJETO_UC_TURMA_H
#define AED_PROJETO_UC_TURMA_H

#include <string>

/*! @brief Classe que associa uma uc e uma turma.
*/

class UCTurma {
    public:
        /*! @brief Variáveis interna publica (do tipo string), representando uma uc. 
        */
        std::string uc;
        /*! @brief Variáveis interna publica (do tipo string), representando uma turma.
        */
        std::string turma;

        /*! @brief Construtor de UCTurma.
        *   
        *   @param[in] uc
        *   @param[in] turma
        */
        UCTurma(std::string uc, std::string turma) {
            this->uc = uc;
            this->turma = turma; 
        }

        /*! @brief Overload do operador ==.
        *   @param[in] ucTurma
        *   
        *   @return Retorna True caso ambas as variáveis (uc e turma) dos dois objetos UCTurma a serem comparados tenham o mesmo conteúdo.
        */
        bool operator== (const UCTurma &ucTurma) {
            return uc == ucTurma.uc && turma == ucTurma.turma;
        }
};


namespace std{
    template<>
    /// @brief Operador less com objetos UCTurma.
    struct less<UCTurma>{
    /*! @brief Overload do operador less.
    *   Função de ultilidade para construir sets com objetos UCTurma.
    *   
    *   @param[in] lhs
    *   @param[in] rhs
    * 
    *   @return Retorna True se o resultado da concatenação das strings uc e turma de lhs, for menor que o resultado da concatenação
    *           das strings uc e turma de rhs.
    */
    bool operator() (const UCTurma &lhs,const UCTurma &rhs) {
        return (lhs.uc+lhs.turma) < (rhs.uc+rhs.turma);
    }};
}
#endif //AED_PROJETO_UC_TURMA_H
