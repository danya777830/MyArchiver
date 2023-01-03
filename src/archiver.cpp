#include <iostream>
#include <vector>
#include <fstream>

#include "bor/bor.h"
#include "files_reader/reader.h"
#include "archive_writer/writer.h"
#include "files_writer/writer.h"
#include "consts.h"

void FlagC(int argc, char **argv) {
    std::string name_archive = argv[2];
    FilesReader &reader = FilesReader::GetElement();
    ArchiveWriter &writer = ArchiveWriter::GetElement();
    writer.Open(name_archive);
    std::vector<std::string> files;
    for (int i = 3; i < argc; ++i) {
        files.push_back(argv[i]);
    }
    reader.SetFile(files);
    MyChar ch = 0;
    std::vector<std::pair<size_t, MyChar>> count = reader.GetCountCharInFile();
    Bor bor(count);
    std::vector<std::vector<bool>> cods = bor.GetDataAndWrite(writer);
    do {
        ch = reader.Get();
        for (size_t i = 0; i < cods[ch].size(); ++i) {
            writer.Print(cods[ch][i]);
        }
        if (ch == ONE_MORE_FILE) {
            count = reader.GetCountCharInFile();
            bor = Bor(count);
            cods = bor.GetDataAndWrite(writer);
        }
    } while (ch != ARCHIVE_END);
}

void FlagD(int argc, char **argv) {
    std::string name_archive = argv[2];
    ArchiveReader &reader = ArchiveReader::GetElement();
    reader.SetArchive(name_archive);
    Bor bor(reader);
    FileWriter &writer = FileWriter::GetElement();
    MyChar ch = 0;
    do {
        ch = bor.GetChar(reader);
        writer.Print(ch);
        if (ch == ONE_MORE_FILE) {
            bor = Bor(reader);
        }
    } while (ch != ARCHIVE_END);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        return 111;
    }
    if (std::string(argv[1]) == "-h") {
        std::cout << "чтоба разорхивировать используйте флаг -d\n";
        std::cout << "Чтобы разорхивировать используйте флаг -с\n";
        return 0;
    }
    if (std::string(argv[1]) == "-c") {
        FlagC(argc, argv);
        return 0;
    }
    if (std::string(argv[1]) == "-d") {
        FlagD(argc, argv);
        return 0;
    }
    return 111;
}