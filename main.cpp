#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <map>
#include "AVL.h"

using namespace std;

// Generar una lista dinámica de enteros aleatorios
vector<int> generateRandomList(int size, int min, int max) {
    vector<int> list(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);

    for (int& num : list) {
        num = dis(gen);
    }

    return list;
}

// Medir el tiempo de ejecución de una función
template<typename Func>
auto measureExecutionTime(Func&& func) {
    auto start = chrono::high_resolution_clock::now();
    forward<Func>(func)();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

// Función para convertir números a palabras (solo para los tamaños utilizados en este ejemplo)
string numberToWords(int number) {
    static map<int, string> numberMap = {
            {100000, "cien mil"},
            {1000000, "un millon"},
            {10000000, "diez millones"},
            {100000000, "cien millones"},
            {1000000000, "mil millones"}
    };
    return numberMap[number];
}

int main() {
    vector<int> sizes = {100000, 1000000, 10000000, 100000000};
    int min = 10;
    int max = 1000;

    for (int size : sizes) {
        cout << "Pruebas con " << numberToWords(size) << " elementos." << endl;

        // Generar lista dinámica de enteros aleatorios
        vector<int> randomList = generateRandomList(size, min, max);

        AVL tree;

        // Medir el tiempo de inserción
        auto insertTime = measureExecutionTime([&](){
            for (int key : randomList) {
                tree.insert(key);
            }
        });

        // Medir el tiempo de búsqueda del 10% de los elementos
        auto searchTime = measureExecutionTime([&](){
            for (int i = 0; i < size / 10; ++i) {
                tree.search(randomList[i]);
            }
        });

        // Medir el tiempo de eliminación del 20% de los elementos
        auto deleteTime = measureExecutionTime([&](){
            for (int i = 0; i < size / 5; ++i) {
                tree.deleteNode(randomList[i]);
            }
        });

        // Medir el tiempo de búsqueda del 10% de los elementos despes de la eliminación
        auto searchTimeAfterDelete = measureExecutionTime([&](){
            for (int i = 0; i < size / 10; ++i) {
                tree.search(randomList[i]);
            }
        });

        cout << "Tamano: " << size << " (" << numberToWords(size) << ")" << endl;
        cout << "Tiempo de insercion: " << insertTime << " microseconds" << endl;
        cout << "Tiempo de busqueda: " << searchTime << " microseconds" << endl;
        cout << "Tiempo de eliminacion: " << deleteTime << " microseconds" << endl;
        cout << "Tiempo de busqueda despues de la eliminacion: " << searchTimeAfterDelete << " microseconds" << endl;
        cout << "--------------------------" << endl;
    }

    return 0;
}
