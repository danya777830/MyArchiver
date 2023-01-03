#include "reader.h"
#include "../my_exception.h"

Reader &Reader::GetElement() {
    static Reader result = Reader();
    return result;
}

void Reader::Open(const std::string &file_name) {
    try {
        stream_ = std::ifstream(file_name, std::ios::binary);
    } catch (const std::exception &err) {
        throw CanNotOpenFile(file_name);
    }
    if (!stream_.is_open()) {
        throw CanNotOpenFile(file_name);
    }
}

char Reader::Get() {
    if (!stream_.is_open()) {
        throw NotSetFile();
    }
    return stream_.get();
}

void Reader::Close() {
    stream_.close();
}

bool Reader::Eof() const {
    return stream_.eof();
}