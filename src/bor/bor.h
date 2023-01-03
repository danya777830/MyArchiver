#include <vector>
#include <utility>
#include <ostream>

#include "../archive_writer/writer.h"
#include "./vertex/vertex.h"
#include "../archive_reader/reader.h"
#include "../consts.h"

class Bor {
    std::shared_ptr<Vertex> main_vertex_;

public:
    explicit Bor(std::vector<std::pair<size_t, MyChar>> initialization_array);
    explicit Bor(ArchiveReader &reader);

    class Iterator {
        std::shared_ptr<const Vertex> vertex_ptr_;

    public:
        explicit Iterator(std::shared_ptr<const Vertex> el) : vertex_ptr_(el){};
        bool IsTerminate() const;
        MyChar operator*() const;
        void Next(const bool &bit);

        Iterator GetZero() const;
        Iterator GetOne() const;
    };
    MyChar GetChar(ArchiveReader &reader) const;
    Iterator Begin() const;

    std::vector<std::vector<bool>> GetData() const;
    std::vector<std::vector<bool>> GetDataAndWrite(ArchiveWriter &writer) const;

private:
    void SizeBorGenerate(std::vector<std::vector<std::shared_ptr<Vertex>>> &elements);
    static void CreateResult(std::vector<bool> &bits, Iterator iter, std::vector<std::vector<bool>> &result);
};