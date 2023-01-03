#pragma once

#include <fstream>

class Reader {
public:
    static Reader &GetElement();

    void Open(const std::string &file_name);
    char Get();
    void Close();

    bool Eof() const;

private:
    std::ifstream stream_;
    Reader() = default;
    Reader(const Reader &other) = delete;
    Reader &operator=(const Reader &other) = delete;
};