#pragma once

#include <fstream>

#include "../consts.h"

class Writer {
public:
    static Writer &GetElement();

    void Open(const std::string &name_archiver);
    void Close();

    void Print(unsigned char c);

    ~Writer();

private:
    std::ofstream stream_;
    Writer() = default;
    Writer(const Writer &other) = delete;
    Writer &operator=(const Writer &other) = delete;
};