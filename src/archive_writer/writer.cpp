#include "writer.h"
#include <iostream>

ArchiveWriter::ArchiveWriter() : writer_(Writer::GetElement()) {
}

ArchiveWriter &ArchiveWriter::GetElement() {
    static ArchiveWriter result = ArchiveWriter();
    return result;
}

void ArchiveWriter::Print(bool b) {
    ch_ <<= 1;
    ch_ += b;
    ++count_bits_;
    if (count_bits_ == COUNT_BITS_IN_BYTE) {
        writer_.Print(ch_);
        count_bits_ = 0;
    }
}

ArchiveWriter::~ArchiveWriter() {
    Close();
}

void ArchiveWriter::Open(const std::string &name_archiver) {
    writer_.Open(name_archiver);
}

void ArchiveWriter::Close() {
    if (count_bits_ == 0) {
        writer_.Close();
        return;
    }
    ch_ <<= COUNT_BITS_IN_BYTE - count_bits_;
    writer_.Print(ch_);
    writer_.Close();
}