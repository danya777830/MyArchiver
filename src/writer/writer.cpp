#include "writer.h"
#include "../my_exception.h"

Writer &Writer::GetElement() {
    static Writer result = Writer();
    return result;
}

void Writer::Print(unsigned char c) {
    stream_.put(c);
}

Writer::~Writer() {
    Close();
}

void Writer::Open(const std::string &name_archiver) {
    try {
        stream_ = std::ofstream(name_archiver, std::ios::binary);
    } catch (const std::exception &err) {
        throw CanNotOpenFile(name_archiver);
    }
    if (!stream_.is_open()) {
        throw CanNotOpenFile(name_archiver);
    }
}

void Writer::Close() {
    stream_.close();
}