//
// Created by lulas on 10/18/2022.
//

#ifndef AED_PROJETO_UC_TURMA_H
#define AED_PROJETO_UC_TURMA_H

#include <string>

class UCTurma {
    public:
        std::string uc, turma;
        UCTurma(std::string uc, std::string turma) {
            this->uc = uc;
            this->turma = turma; 
        }

        bool operator== (const UCTurma &ucTurma) {
            return uc == ucTurma.uc && turma == ucTurma.turma;
        }
};

namespace std{
    template<>
    struct less<UCTurma>{
    bool operator() (const UCTurma &lhs,const UCTurma &rhs) {
        return (lhs.uc+lhs.turma) < (rhs.uc+rhs.turma);
    }};
}
#endif //AED_PROJETO_UC_TURMA_H
