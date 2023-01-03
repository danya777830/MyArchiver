#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../bor/vertex/vertex.h"

TEST_CASE("Vertex") {
    std::shared_ptr<Vertex> a(new Vertex('a'));
    std::shared_ptr<Vertex> b(new Vertex('b'));
    std::shared_ptr<Vertex> mn(new Vertex(a, b));
    REQUIRE(a->GetChar() == 'a');
    REQUIRE(b->GetChar() == 'b');
    REQUIRE(mn->GetOne()->GetChar() == 'b');
}