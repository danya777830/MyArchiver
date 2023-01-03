add_executable(
    test_bor
    test_bor.cpp
    ../bor/bor.cpp
    ../reader/reader.cpp
    ../writer/writer.cpp
    ../archive_writer/writer.cpp
    ../archive_reader/reader.cpp
    ../bor/vertex/vertex.cpp
)

add_executable(
    test_reader_writer
    test_reader_writer.cpp
    ../writer/writer.cpp
    ../reader/reader.cpp
)

add_executable(
    test_priorety_tree
    test_priorety_tree.cpp
)

add_executable(
    test_vertex
    test_vertex.cpp
    ../bor/vertex/vertex.cpp
)

add_executable(
    test_archive_writer_and_reader
    test_archive_writer_and_reader.cpp
    ../archive_writer/writer.cpp
    ../archive_reader/reader.cpp
    ../writer/writer.cpp
    ../reader/reader.cpp
)

add_executable(
    test_files_reader_and_writer
    test_files_reader_and_writer.cpp
    ../files_reader/reader.cpp
    ../files_writer/writer.cpp
    ../reader/reader.cpp
    ../writer/writer.cpp
)