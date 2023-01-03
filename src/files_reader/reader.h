#include <vector>

#include "../consts.h"
#include "../reader/reader.h"

class FilesReader {
public:
    static FilesReader &GetElement();

    std::vector<std::pair<size_t, MyChar>> GetCountCharInFile();

    void MoveBegin();

    void SetFile(const std::vector<std::string> &files);

    MyChar Get();

private:
    bool reading_name_ = true;
    unsigned int nomber_file_ = 0;
    Reader &reader_;
    std::vector<std::string> files_;
    size_t nomber_char_ = 0;
    FilesReader();
    FilesReader(const FilesReader &other) = delete;
    FilesReader &operator=(const FilesReader &other) = delete;
};