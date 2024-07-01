#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include "AVL.h"
#include "Red-Black-Tree.h"

using namespace std;
using namespace std::chrono;

// Define the different sizes of vectors to benchmark
const vector<int> SIZES = {10000, 100000, 1000000, 10000000};
const int RANGE = 1000000;

void benchmarkAVL(const vector<int>& valuesToInsert, const vector<int>& valuesToDelete) {
    AVL<int> avl;

    // Insert elements
    auto start = high_resolution_clock::now();
    for (int value : valuesToInsert) {
        avl.insert(value);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "AVL insert duration (" << valuesToInsert.size() << " elements): " << duration.count() << " ms" << endl;

    // Search elements
    start = high_resolution_clock::now();
    for (int value : valuesToInsert) {
        avl.search(value);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "AVL search duration (" << valuesToInsert.size() << " elements): " << duration.count() << " ms" << endl;

    // Delete elements
    start = high_resolution_clock::now();
    for (int value : valuesToDelete) {
        avl.deleteNode(value);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "AVL delete duration (" << valuesToDelete.size() << " elements): " << duration.count() << " ms" << endl;
}

void benchmarkRBT(const vector<int>& valuesToInsert, const vector<int>& valuesToDelete) {
    RBT<int> rbt;

    // Insert elements
    auto start = high_resolution_clock::now();
    for (int value : valuesToInsert) {
        rbt.insert(value);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "RBT insert duration (" << valuesToInsert.size() << " elements): " << duration.count() << " ms" << endl;

    // Search elements
    start = high_resolution_clock::now();
    for (int value : valuesToInsert) {
        rbt.search(value);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "RBT search duration (" << valuesToInsert.size() << " elements): " << duration.count() << " ms" << endl;

    // Delete elements
    start = high_resolution_clock::now();
    for (int value : valuesToDelete) {
        rbt.deleteNode(value);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "RBT delete duration (" << valuesToDelete.size() << " elements): " << duration.count() << " ms" << endl;
}

int main() {
    srand(time(0));

    for (int size : SIZES) {
        vector<int> valuesToInsert(size);
        vector<int> valuesToDelete(size);

        // Generate random values to insert
        for (int i = 0; i < size; ++i) {
            valuesToInsert[i] = rand() % RANGE;
        }

        // Generate random values to delete (using the same range)
        for (int i = 0; i < size; ++i) {
            valuesToDelete[i] = rand() % RANGE;
        }

        cout << "Benchmarking with " << size << " elements..." << endl;
        cout << "--------------------------------------" << endl;

        cout << "Benchmarking AVL Tree..." << endl;
        benchmarkAVL(valuesToInsert, valuesToDelete);

        cout << "Benchmarking Red-Black Tree..." << endl;
        benchmarkRBT(valuesToInsert, valuesToDelete);

        cout << "--------------------------------------" << endl;
        cout << endl;
    }

    return 0;
}
