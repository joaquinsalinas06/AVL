#ifndef AVL_H
#define AVL_H

#include <iostream>

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
public:
    Node* root;

    AVL() : root(nullptr) {}

    ~AVL() {
        destroyTree(root);
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else
            return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1) {
            if (key < node->left->key) {
                return rotateRight(node);
            } else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (balanceFactor < -1) {
            if (key > node->right->key) {
                return rotateLeft(node);
            } else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {

            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;

                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }

                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) return root;

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        int balanceFactor = getBalanceFactor(root);

        if (balanceFactor > 1) {
            if (getBalanceFactor(root->left) >= 0) {
                return rotateRight(root);
            } else {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }

        if (balanceFactor < -1) {
            if (getBalanceFactor(root->right) <= 0) {
                return rotateLeft(root);
            } else {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }

        return root;
    }

    Node* search(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key < key)
            return search(root->right, key);

        return search(root->left, key);
    }

    void printInOrder(Node* root) {
        if (root != nullptr) {
            printInOrder(root->left);
            std::cout << root->key << " ";
            printInOrder(root->right);
        }
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    Node* search(int key) {
        return search(root, key);
    }

    void printInOrder() {
        std::cout << "In-order traversal: ";
        printInOrder(root);
        std::cout << std::endl;
    }
};

#endif // AVL_H
