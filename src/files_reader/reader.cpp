#include "reader.h"
#include <iostream>

FilesReader::FilesReader() : reader_(Reader::GetElement()) {
}

FilesReader &FilesReader::GetElement() {
    static FilesReader reader = FilesReader();
    return reader;
}

MyChar FilesReader::Get() {
    if (reading_name_) {
        if (nomber_char_ == files_[nomber_file_].size()) {
            reading_name_ = false;
            return FILENAME_END;
        } else {
            return files_[nomber_file_][nomber_char_++];
        }
    }
    unsigned char result = 0;
    result = reader_.Get();
    if (reader_.Eof()) {
        ++nomber_file_;
        if (nomber_file_ == files_.size()) {
            return ARCHIVE_END;
        } else {
            return ONE_MORE_FILE;
            reader_.Open(files_[nomber_file_]);
        }
    }
    return result;
}

void FilesReader::SetFile(const std::vector<std::string> &files) {
    nomber_file_ = 0;
    reader_.Open(files[0]);
    files_ = files;
    nomber_char_ = 0;
    reading_name_ = true;
}

void FilesReader::MoveBegin() {
    reader_.Open(files_[nomber_file_]);
    nomber_char_ = 0;
    reading_name_ = true;
}

std::vector<std::pair<size_t, MyChar>> FilesReader::GetCountCharInFile() {
    std::vector<size_t> count_char(COUNT_MY_CHAR);
    unsigned int nomber_file = nomber_file_;
    MoveBegin();
    MyChar el = 0;
    do {
        el = Get();
        ++count_char[el];
    } while (el != ARCHIVE_END && el != ONE_MORE_FILE);
    count_char[FILENAME_END] = 1;
    count_char[ONE_MORE_FILE] = 1;
    count_char[ARCHIVE_END] = 1;
    std::vector<std::pair<size_t, MyChar>> result;
    for (MyChar i = 0; i < COUNT_MY_CHAR; ++i) {
        if (count_char[i] != 0) {
            result.push_back({count_char[i], i});
        }
    }
    nomber_file_ = nomber_file;
    nomber_char_ = 0;
    reading_name_ = true;
    reader_.Open(files_[nomber_file_]);
    return result;
}