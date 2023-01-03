#pragma once

#include "../consts.h"
#include "../writer/writer.h"

class ArchiveWriter {
public:
    static ArchiveWriter &GetElement();

    void Open(const std::string &name_archiver);
    void Close();

    void Print(bool b);
    void Print(char c);

    ~ArchiveWriter();

private:
    Writer &writer_;
    unsigned char ch_;
    unsigned int count_bits_ = 0;
    ArchiveWriter();
    ArchiveWriter(ArchiveWriter &other) = delete;
    ArchiveWriter &operator=(ArchiveWriter &other) = delete;
};