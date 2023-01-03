#include <set>
#include <algorithm>

#include "bor.h"
#include "./priorety_tree/priorety_tree.h"
#include "../archive_reader/reader.h"

struct PrioretyTreeElement {
    size_t count;
    std::shared_ptr<Vertex> ptr;
    MyChar min_el;
};

bool operator<(const PrioretyTreeElement &a, const PrioretyTreeElement &b) {
    if (a.count == b.count) {
        return a.min_el < b.min_el;
    }
    return a.count < b.count;
}

Bor::Bor(ArchiveReader &reader) {
    std::vector<MyChar> initialization_array;
    size_t count_char = 0;
    for (size_t i = 0; i < COUNT_BITS_IN_MY_CHAR; ++i) {
        count_char = count_char << 1;
        count_char += reader.Get();
    }
    for (size_t i = 0; i < count_char; ++i) {
        MyChar ch = 0;
        for (size_t j = 0; j < COUNT_BITS_IN_MY_CHAR; ++j) {
            ch = ch << 1;
            ch += reader.Get();
        }
        initialization_array.push_back(ch);
    }
    size_t uk = 0;
    std::vector<std::vector<std::shared_ptr<Vertex>>> elements;
    for (size_t l = 0; uk < count_char; ++l) {
        size_t count_len = 0;
        for (size_t j = 0; j < COUNT_BITS_IN_MY_CHAR; ++j) {
            count_len = count_len << 1;
            count_len += reader.Get();
        }
        elements.push_back(std::vector<std::shared_ptr<Vertex>>());
        for (size_t i = 0; i < count_len; ++i) {
            elements[l].push_back(std::shared_ptr<Vertex>(new Vertex(initialization_array[uk])));
            ++uk;
        }
    }
    SizeBorGenerate(elements);
}

Bor::Bor(std::vector<std::pair<size_t, MyChar>> initialization_array) {
    std::sort(initialization_array.begin(), initialization_array.end());
    MyPrioretyTree<PrioretyTreeElement> vertexs;
    for (const auto &[count, ch] : initialization_array) {
        vertexs.Add({.count = count, .ptr = std::shared_ptr<Vertex>(new Vertex(ch)), .min_el = ch});
    }
    while (vertexs.Size() > 1) {
        auto a = vertexs.GetMin();
        vertexs.DeleteMin();
        auto b = vertexs.GetMin();
        vertexs.DeleteMin();
        vertexs.Add({.count = a.count + b.count,
                     .ptr = std::shared_ptr<Vertex>(new Vertex(a.ptr, b.ptr)),
                     .min_el = std::min(a.min_el, b.min_el)});
    }
    main_vertex_ = vertexs.GetMin().ptr;
    std::vector<std::vector<bool>> size = GetData();
    size_t max_size = 0;
    for (MyChar i = 0; i < size.size(); ++i) {
        if (size[i].size() > max_size) {
            max_size = size[i].size();
        }
    }
    if (max_size == 1) {
        return;
    }
    std::vector<std::vector<std::shared_ptr<Vertex>>> elements(max_size);
    for (MyChar i = 0; i < size.size(); ++i) {
        if (!size[i].empty()) {
            elements[size[i].size() - 1].push_back(std::shared_ptr<Vertex>(new Vertex(i)));
        }
    }
    SizeBorGenerate(elements);
}

Bor::Iterator Bor::Begin() const {
    return Iterator(main_vertex_);
}

bool Bor::Iterator::IsTerminate() const {
    return vertex_ptr_->GetTerminate();
}

MyChar Bor::Iterator::operator*() const {
    return vertex_ptr_->GetChar();
}

void Bor::Iterator::Next(const bool &bit) {
    if (bit) {
        vertex_ptr_ = vertex_ptr_->GetOne();
    } else {
        vertex_ptr_ = vertex_ptr_->GetZero();
    }
}

std::vector<std::vector<bool>> Bor::GetDataAndWrite(ArchiveWriter &writer) const {
    std::vector<std::vector<bool>> result = GetData();
    std::vector<std::pair<std::vector<bool>, MyChar>> chars;
    for (MyChar i = 0; i < result.size(); ++i) {
        if (!result[i].empty()) {
            chars.push_back({result[i], i});
        }
    }
    std::sort(chars.begin(), chars.end());
    for (unsigned int i = 0; i < COUNT_BITS_IN_MY_CHAR; ++i) {
        writer.Print(0 != (chars.size() & (1 << (8 - i))));
    }
    for (const auto &[bits, Char] : chars) {
        for (unsigned int i = 0; i < COUNT_BITS_IN_MY_CHAR; ++i) {
            writer.Print(0 != (Char & (1 << (8 - i))));
        }
    }
    size_t uk = 0;
    for (size_t length = 1; uk < chars.size(); ++length) {
        int count = 0;
        while (uk < chars.size() && chars[uk].first.size() == length) {
            ++count;
            ++uk;
        }
        for (unsigned int i = 0; i < COUNT_BITS_IN_MY_CHAR; ++i) {
            writer.Print(0 != (count & (1 << (COUNT_BITS_IN_MY_CHAR - 1 - i))));
        }
    }
    return result;
}

std::vector<std::vector<bool>> Bor::GetData() const {
    //раз рекурсию можно, то тут наверное все ок
    std::vector<std::vector<bool>> result(300);
    std::vector<bool> bits;
    CreateResult(bits, Begin(), result);
    return result;
}

void Bor::CreateResult(std::vector<bool> &bits, Iterator iter, std::vector<std::vector<bool>> &result) {
    if (iter.IsTerminate()) {
        result[*iter] = bits;
    } else {
        bits.push_back(false);
        CreateResult(bits, iter.GetZero(), result);
        bits.pop_back();
        bits.push_back(true);
        CreateResult(bits, iter.GetOne(), result);
        bits.pop_back();
    }
}

Bor::Iterator Bor::Iterator::GetZero() const {
    return Iterator(vertex_ptr_->GetZero());
}

Bor::Iterator Bor::Iterator::GetOne() const {
    return Iterator(vertex_ptr_->GetOne());
}

MyChar Bor::GetChar(ArchiveReader &reader) const {
    Iterator iter = Begin();
    while (!iter.IsTerminate()) {
        bool b = reader.Get();
        if (b) {
            iter = iter.GetOne();
        } else {
            iter = iter.GetZero();
        }
    }
    return *iter;
}

void Bor::SizeBorGenerate(std::vector<std::vector<std::shared_ptr<Vertex>>> &elements) {
    for (ssize_t i = elements.size() - 1; i > 0; --i) {
        for (size_t j = 0; j < elements[i].size(); j += 2) {
            elements[i - 1].push_back(std::shared_ptr<Vertex>(new Vertex(elements[i][j], elements[i][j + 1])));
        }
    }
    main_vertex_ = std::shared_ptr<Vertex>(new Vertex(elements[0][0], elements[0][1]));
}