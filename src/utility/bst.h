#pragma once

#include "node.h"
#include <iostream>

template <typename T>
class BinaryTree {
    public:
        Node<T> *root;
        // constructor
        BinaryTree<T> () {
            root = nullptr;
        }
        // destructor
        ~BinaryTree<T> () {
            deleteTree(this->root);
        }

        // insert a node in the tree in the optimal location, complexity of O(log n)
        void insert(T data) {
            Node<T> *newNode = new Node<T>(data);
            // if there is nothing in the tree yet, make the new node the root
            if (root == nullptr) {
                root = newNode;
            } else {
                Node<T> *current = root;
                while (true) {
                    // if data is smaller than current node data
                    if (data < current->data) {
                        // if there is no node to the left, then insert data there
                        if (current->left == nullptr) {
                            current->left = newNode;
                            break;
                        } // else go to the left node
                        else {
                            current = current->left;
                        }
                    } // else, data is greater than current data
                    else {
                        // if there is no node to the right, then insert data there
                        if (current->right == nullptr) {
                            current->right = newNode;
                            break;
                        } // else go to the right node
                        else {
                            current = current->right;
                        }
                    }
                }
            }
        }

        /*
            if we want to remoe a leaf simply delete the node from the tree
                    50                            50
                /     \         delete(20)      /   \
                30      70       --------->    30     70 
                /  \    /  \                     \    /  \ 
            20   40  60   80                   40  60   80
        */

        /*
            if the node we want to delete only has one child, then we have to copy the
            child to the node and delete the child
                    50                            50
                /     \         delete(30)      /   \
                30      70       --------->    40     70 
                    \    /  \                          /  \ 
                    40  60   80                       60   80
        */

        /*
            if the node we want to delete has two children, then we have to find the 
            inorder successor of the node, copy the contents of the inorder 
            successor of the node to the node and delete the inorder successor
                    50                            60
                /     \         delete(50)      /   \
                40      70       --------->    40    70 
                        /  \                            \ 
                        60   80                           80
        */
        /*
        // remove a node from the tree, complexity of O(log n)
        void remove(T data) {
            // declare the parent and current nodes for future use
            Node<T> *current = root;
            Node<T> *parent = nullptr;
            // while there is a node at the current location
            // search the tree for the node that we want
            while (current != nullptr) {
                // if the data matches the passed data, then we found the node we wnat to delete
                if (current->data == data) {
                    // first case as showed above, the node has no children, so its a leaf
                    // in this case, we simply delete the node
                    if (current->left == nullptr && current->right == nullptr) {
                        // if the parent is a nullptr then that means we are deleting the root of the binary tree
                        if (parent == nullptr) {
                            root = nullptr;
                        } else {
                            // remove the node from the parent
                            if (parent->left == current) {
                                parent->left = nullptr;
                            } else {
                                parent->right = nullptr;
                            }
                        }
                    } 
                    // second case as showed above, the node only has one child in the right position
                    // in this case we have to copy the child to the node and delete the child
                    else if (current->left == nullptr && current->right != nullptr) {
                        // if the node is the root, then we make the right child the root of the tree
                        if (parent == nullptr) {
                            root = current->right;
                        } 
                        // copy the right child to the correct child of the parent node
                        else {
                            if (parent->left == current) {
                                parent->left = current->right;
                            } else {
                                parent->right = current->right;
                            }
                        }
                    } 
                    // also the second case as showed above, the node only has one child in the left position
                    // in this case we have to copy the child to the node and delete the child
                    else if (current->left != nullptr && current->right == nullptr) {
                        // if the node is the root, then we make the left child the root of the tree
                        if (parent == nullptr) {
                            root = current->left;
                        } 
                        // copy the left child to the correct child of the parent node
                        else {
                            if (parent->left == current) {
                                parent->left = current->left;
                            } else {
                                parent->right = current->left;
                            }
                        }
                    } 
                    // third case as showed above, the node has two children
                    // in this case we have to find the inorder successor of the node, 
                    // copy the contents of the inorder successor of the node to the node 
                    // and delete the inorder successor
                    else {
                        // make a new temporary node pointing to the right child of the current node
                        Node<T> *temp = current->right;
                        // search for the leftmost child of that node, which is the inorder successor
                        // of the node we want to delete
                        while (temp->left != nullptr) {
                            temp = temp->left;
                        }
                        // copy the data of the inorder successor node to the node we want to delete
                        current->data = temp->data;
                        // finally call the remove function recursively to remove the inorder successor
                        remove(temp->data);
                    }
                    // finally break, after the removal has been completed
                    break;
                } // go to the left node
                else if (data < current->data) {
                    parent = current;
                    current = current->left;
                } // go to the right node 
                else {
                    parent = current;
                    current = current->right;
                }
            }
        }
        */
        // remove a node from the tree, complexity of O(log n)
        void remove(T data) {
            removeNode(root, data);
        }

        Node<T>* removeNode(Node<T>* node, T data) {
            if (node == nullptr) {
                return nullptr;
            }
            if (data < node->data) {
                node->left = removeNode(node->left, data);
            } else if (data > node->data) {
                node->right = removeNode(node->right, data);
            } else {
                if (node->left == nullptr && node->right == nullptr) {
                    delete node;
                    node = nullptr;
                } else if (node->left == nullptr) {
                    Node<T> *temp = node;
                    node = node->right;
                    delete temp;
                } else if (node->right == nullptr) {
                    Node<T> *temp = node;
                    node = node->left;
                    delete temp;
                } else {
                    Node<T> *temp = getInorderSuccessor(node->right);
                    node->data = temp->data;
                    node->right = removeNode(node->right, temp->data);
                }
            }
            return node;
        }

        // get the inorder successor of a node
        Node<T>* getInorderSuccessor(Node<T> *node) {
            Node<T> *current = node;
            while (current->left != nullptr) {
                current = current->left;
            }
            return current;
        }

        // return a pointer to the node with the given data, complexity of O(log n)
        Node<T> *search(T data) {
            Node<T> *current = root;
            while (current != nullptr) {
                if (current->data == data) {
                    return current;
                } else if (data < current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return nullptr;
        }

        // print the tree in order, complexity of O(n)
        void printInOrder() {
            printInOrder(root);
            std::cout << std::endl;
        }

        // print binary tree showing nodes and branches
        void printTreeInTreeShape() {
            printTreeInTreeShape(root, 0);
        }
        // prints the tree in a tree shape complexity of O(tree)
        void printTreeInTreeShape(Node<T> *node, int level) {
            if (node != nullptr) {
                printTreeInTreeShape(node->right, level + 1);
                for (int i = 0; i < level; i++) {
                    std::cout << "    ";
                }
                std::cout << node->data << std::endl;
                printTreeInTreeShape(node->left, level + 1);
            }
        }
        
        void deleteTree(Node<T> *node) {
            if (node != nullptr) {
                deleteTree(node->left);
                deleteTree(node->right);
                delete node;
            }
        }
};


































//(tree)