#include <chrono>
#include <random>
#include <string>

#include "../src/binary_tree.h"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char* argv[]) {
    int n = 10000;
    if (argc > 1) {
        n = std::stoi(argv[1]);
    }
    BinaryTree<int> tr;
    for (int i = 0; i < n; ++i) {
        tr.Insert(rng() % n);
    }
}
