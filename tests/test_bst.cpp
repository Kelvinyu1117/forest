#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "bst.h"
#include <iostream>
#include <vector>
#include <set>

template <typename T>
using LinkedBinarySearchTree = forest::LinkedBinarySearchTree<T>;

TEST_CASE("LinkedBinarySearchTree basic insert and find", "[bst]") {
    LinkedBinarySearchTree<int> tree;
    REQUIRE(tree.empty());

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    REQUIRE(tree.find(10) != tree.end());
    REQUIRE(tree.find(5) != tree.end());
    REQUIRE(tree.find(15) != tree.end());
    REQUIRE(tree.find(20) == tree.end());
}

TEST_CASE("LinkedBinarySearchTree iterator traversal", "[bst]") {
    LinkedBinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);

    std::vector<int> expected_order = {3, 5, 7, 10, 12, 15, 18};
    std::vector<int> actual_order;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        actual_order.push_back(*it);
    }

    REQUIRE(actual_order == expected_order);
}

TEST_CASE("LinkedBinarySearchTree duplicate insertions", "[bst]") {
    LinkedBinarySearchTree<int> tree;
    auto [it1, inserted1] = tree.insert(10);
    auto [it2, inserted2] = tree.insert(10); // Duplicate insertion

    REQUIRE(inserted1 == true);
    REQUIRE(inserted2 == false); // Should not insert duplicate
    REQUIRE(*it1 == 10);
    REQUIRE(it1 == it2); // Both iterators should point to the same node
}
