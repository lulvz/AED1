#pragma once

template <typename T>
class Node {
    public:
        T data;
        Node<T> *right;
        Node<T> *left;

        Node<T> (T data) : data(data) {
            //this->data = data;
            right = nullptr;
            left = nullptr;
        }
};