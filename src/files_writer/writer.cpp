#include "writer.h"

FileWriter::FileWriter() : writer_(Writer::GetElement()) {
}

FileWriter &FileWriter::GetElement() {
    static FileWriter result = FileWriter();
    return result;
}

void FileWriter::Print(MyChar ch) {
    if (ch == ARCHIVE_END) {
        writer_.Close();
        return;
    }
    if (ch == ONE_MORE_FILE) {
        writer_.Close();
        name_file_ = "";
        print_name_ = true;
        return;
    }
    if (ch == FILENAME_END) {
        print_name_ = false;
        writer_.Open(name_file_);
        return;
    }
    if (print_name_) {
        name_file_ += ch;
    } else {
        writer_.Print(static_cast<char>(ch));
    }
}

void FileWriter::Print(const std::vector<MyChar> &ch) {
    for (auto iter = ch.begin(); iter != ch.end(); ++iter) {
        Print(*iter);
    }
}