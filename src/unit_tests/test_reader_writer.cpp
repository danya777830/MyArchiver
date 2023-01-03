#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../reader/reader.h"
#include "../writer/writer.h"

TEST_CASE("reader_writer") {
    Writer &writer = Writer::GetElement();
    Reader &reader = Reader::GetElement();

    writer.Open("file");
    writer.Print('a');
    writer.Print('b');
    writer.Print('c');
    writer.Close();

    reader.Open("file");
    REQUIRE(reader.Get() == 'a');
    REQUIRE(reader.Get() == 'b');
    REQUIRE(!reader.Eof());
    REQUIRE(reader.Get() == 'c');
    reader.Get();
    REQUIRE(reader.Eof());
}