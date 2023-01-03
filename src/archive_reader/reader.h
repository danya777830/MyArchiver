#pragma once

#include "../consts.h"
#include "../reader/reader.h"

class ArchiveReader {
public:
    static ArchiveReader &GetElement();

    void SetArchive(const std::string &archive_name);
    bool Get();

private:
    Reader &reader_;
    int bits_read_count_ = 8;
    unsigned char ch_;

    ArchiveReader();
    ArchiveReader &operator=(const ArchiveReader &other) = delete;
    ArchiveReader(const ArchiveReader &other) = delete;
};