#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

#include "../bor/bor.h"

TEST_CASE("Bor") {
    std::vector<std::pair<size_t, MyChar>> vec({{5, 'a'}, {1, 'b'}, {1, 'c'}});
    std::vector<std::vector<bool>> result = Bor(vec).GetData();

    REQUIRE(result['a'].size() == 1);
    REQUIRE(result['b'].size() == 2);

    vec = {{5, 'a'}, {5, 'b'}, {5, 'c'}};

    std::vector<std::vector<bool>> result_a = Bor(vec).GetData();
    std::vector<std::vector<bool>> result_b = Bor(vec).GetData();

    REQUIRE(result_a['a'] == result_b['a']);

    ArchiveWriter &writer = ArchiveWriter::GetElement();
    writer.Open("test");

    std::vector<std::vector<bool>> data = Bor(vec).GetDataAndWrite(writer);

    REQUIRE(data['c'][0] == 0);
    REQUIRE(data['a'][1] == 0);

    writer.Close();

    std::ifstream stream("test");

    char c = 0;

    stream >> c;

    REQUIRE(c == 1);
}