add_executable(
        archiver
        archiver.cpp
        bor/bor.cpp
        bor/vertex/vertex.cpp
        files_reader/reader.cpp
        archive_reader/reader.cpp
        writer/writer.cpp
        files_writer/writer.cpp
        archive_writer/writer.cpp
        reader/reader.cpp
        writer/writer.cpp
)

add_subdirectory(unit_tests)