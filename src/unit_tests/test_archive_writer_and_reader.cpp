#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../archive_writer/writer.h"
#include "../archive_reader/reader.h"
#include "../my_exception.h"

TEST_CASE("READER_AND_WRITER") {
    ArchiveWriter &writer = ArchiveWriter::GetElement();
    writer.Open("a");
    writer.Print(true);
    writer.Print(false);
    writer.Print(true);
    writer.Print(true);
    writer.Close();

    ArchiveReader &read = ArchiveReader::GetElement();
    read.SetArchive("a");
    REQUIRE(read.Get() == true);
    REQUIRE(read.Get() == false);
    REQUIRE(read.Get() == true);
    REQUIRE(read.Get() == true);
}

TEST_CASE("BAD_ARCHIVE") {
    Writer &writer = Writer::GetElement();
    writer.Print('a');
    writer.Print('b');

    bool is_exception = false;

    ArchiveReader &reader = ArchiveReader::GetElement();

    try {
        while (true) {
            reader.Get();
        }
    } catch (BadArchive &err) {
        is_exception = true;
    }

    REQUIRE(is_exception);
}

TEST_CASE("CAN_NOT_OPEN") {
    bool is_exception = false;

    try {
        ArchiveReader &reader = ArchiveReader::GetElement();
        reader.SetArchive({"luke_i_am_you_father", "nooooooooooo"});
    } catch (const CanNotOpenFile &err) {
        is_exception = true;
    }

    REQUIRE(is_exception);
}