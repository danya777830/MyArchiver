#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../files_reader/reader.h"
#include "../files_writer/writer.h"
#include "../consts.h"

TEST_CASE("ReaderAndWriter") {
    FilesReader &reader = FilesReader::GetElement();
    FileWriter &writer = FileWriter::GetElement();
    writer.Print('d');
    writer.Print('o');
    writer.Print('c');
    writer.Print(FILENAME_END);
    writer.Print('H');
    writer.Print('e');
    writer.Print('!');
    writer.Print(ARCHIVE_END);

    reader.SetFile({"doc"});
    REQUIRE(reader.Get() == 'd');
    REQUIRE(reader.Get() == 'o');
    REQUIRE(reader.Get() == 'c');
    REQUIRE(reader.Get() == FILENAME_END);
    REQUIRE(reader.Get() == 'H');
    REQUIRE(reader.Get() == 'e');
    REQUIRE(reader.Get() == '!');
    REQUIRE(reader.Get() == ARCHIVE_END);

    reader.SetFile({"doc"});

    std::vector<std::pair<size_t, MyChar>> count = reader.GetCountCharInFile();

    for (size_t i = 0; i < count.size(); ++i) {
        if (count[i].second == 258) {
            REQUIRE(count[i].first == 1);
        }
    }
}