#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../bor/priorety_tree/priorety_tree.h"

TEST_CASE("PrioretyTree") {
    MyPrioretyTree<int> tree;
    tree.Add(1);
    tree.Add(2);
    tree.Add(3);

    REQUIRE(1 == tree.GetMin());

    tree.DeleteMin();

    REQUIRE(2 == tree.GetMin());

    tree.Add(1);
    tree.Add(1);

    REQUIRE(1 == tree.GetMin());

    tree.DeleteMin();

    REQUIRE(1 == tree.GetMin());

    tree.DeleteMin();
    tree.DeleteMin();
    tree.DeleteMin();
    tree.DeleteMin();
}