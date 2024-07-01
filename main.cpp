#include <iostream>
#include <chrono>
#include <cstdlib>
#include "AVL.h"
#include "Red-Black-Tree.h"

using namespace std;
using namespace std::chrono;

const int NUM_ELEMENTS = 10000;
const int RANGE = 1000000;

void benchmarkAVL() {
    AVL<int> avl;
    int values[NUM_ELEMENTS];

    // Generate random values
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        values[i] = rand() % RANGE;
    }

    // Insert elements
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        avl.insert(values[i]);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "AVL insert duration: " << duration.count() << " ms" << endl;

    // Search elements
    start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        avl.search(values[i]);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "AVL search duration: " << duration.count() << " ms" << endl;

    // Delete elements
    start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        avl.deleteNode(values[i]);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "AVL delete duration: " << duration.count() << " ms" << endl;
}

void benchmarkRBT() {
    RBT<int> rbt;
    int values[NUM_ELEMENTS];

    // Generate random values
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        values[i] = rand() % RANGE;
    }

    // Insert elements
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        rbt.insert(values[i]);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "RBT insert duration: " << duration.count() << " ms" << endl;

    // Search elements
    start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        rbt.search(values[i]);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "RBT search duration: " << duration.count() << " ms" << endl;

    // Delete elements
    start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        rbt.deleteNode(values[i]);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "RBT delete duration: " << duration.count() << " ms" << endl;
}

int main() {
    srand(time(0));

    cout << "Benchmarking AVL Tree..." << endl;
    benchmarkAVL();

    cout << "Benchmarking Red-Black Tree..." << endl;
    benchmarkRBT();

    return 0;
}
