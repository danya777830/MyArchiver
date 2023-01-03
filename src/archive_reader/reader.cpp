#include "reader.h"

#include <iostream>

#include "../my_exception.h"

ArchiveReader::ArchiveReader() : reader_(Reader::GetElement()) {
}

ArchiveReader &ArchiveReader::GetElement() {
    static ArchiveReader result = ArchiveReader();
    return result;
}

void ArchiveReader::SetArchive(const std::string &archive_name) {
    reader_.Open(archive_name);
    bits_read_count_ = COUNT_BITS_IN_BYTE;
}

bool ArchiveReader::Get() {
    if (bits_read_count_ == COUNT_BITS_IN_BYTE) {
        bits_read_count_ = 0;
        if (reader_.Eof()) {
            throw BadArchive();
        }
        ch_ = reader_.Get();
    }
    ++bits_read_count_;
    return (0 != (ch_ & (1 << (COUNT_BITS_IN_BYTE - bits_read_count_))));
}