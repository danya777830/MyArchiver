#pragma once

#include <vector>

#include "../consts.h"
#include "../writer/writer.h"

using MyChar = unsigned int;

class FileWriter {
public:
    static FileWriter &GetElement();

    void Print(MyChar ch);
    void Print(const std::vector<MyChar> &ch);

private:
    Writer &writer_;
    std::string name_file_;
    bool print_name_ = true;
    FileWriter &operator=(const FileWriter &other) = delete;
    FileWriter(const FileWriter &other) = delete;
    FileWriter();
};