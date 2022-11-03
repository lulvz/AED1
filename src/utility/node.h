#pragma once

/*! @brief Classe que cria um nó, podendo este conter um tipo arbitrário de variável.
*/
template <typename T>
class Node {
    public:
        /// @brief Variável armazenada no nó.
        T data;
        /// @brief Apontador para o filho direito do nó.
        Node<T> *right;
        /// @brief Apontador para o filho esquerdo do nó.
        Node<T> *left;

        /*! @brief Construtor da classe Node.
        *   Cria um novo nó com a informação passada em argumento e inicializa os respetivos apontadores para null.
        *
        *   @param[in] data
        */
        Node<T> (T data) : data(data) {
            //this->data = data;
            right = nullptr;
            left = nullptr;
        }
};