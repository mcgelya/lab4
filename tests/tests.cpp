#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>

#include "../src/binary_tree.h"

TEST_CASE("Insert erase search") {
    BinaryTree<int> t;
    t.Insert(3);
    t.Insert(4);
    t.Insert(1);
    REQUIRE(t.Search(1));
    REQUIRE(t.Search(3));
    REQUIRE(t.Search(4));
    REQUIRE(!t.Search(5));
    t.Erase(3);
    REQUIRE(!t.Search(3));
}

TEST_CASE("Map where reduce") {
    BinaryTree<int> t;
    t.Insert(3);
    t.Insert(4);
    t.Insert(1);
    BinaryTree<int> mp = t.Map([](int x) {
        return x - 1;
    });
    REQUIRE(mp.Search(0));
    REQUIRE(mp.Search(2));
    REQUIRE(mp.Search(3));
    BinaryTree<int> whr = mp.Where([](int x) {
        return x % 2 == 0;
    });
    REQUIRE(whr.Search(0));
    REQUIRE(whr.Search(2));
    REQUIRE(!whr.Search(3));
    int rdc = t.Reduce(
        [](int x, int acc) {
            return x + acc;
        },
        0);
    REQUIRE(rdc == 8);
}

TEST_CASE("ToString") {
    BinaryTree<int> t;
    t.Insert(3);
    t.Insert(4);
    t.Insert(1);
    std::cout << t.ToString() << std::endl;
}

TEST_CASE("Build from val-par") {
    std::vector<std::pair<int, int>> v{{1, 3}, {4, 3}};
    BinaryTree<int> t = BinaryTree<int>::FromPairs(v);
    std::cout << t.ToString() << std::endl;
    v.push_back({1, 4});
    REQUIRE_THROWS(BinaryTree<int>::FromPairs(v));
}
