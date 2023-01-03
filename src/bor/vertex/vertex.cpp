#include "vertex.h"

Vertex::Vertex(const MyChar &ch) {
    terminate_ = true;
    v_char_ = ch;
}

Vertex::Vertex(std::shared_ptr<Vertex> &left_ptr, std::shared_ptr<Vertex> &right_ptr) {
    terminate_ = false;
    left_ptr_ = left_ptr;
    right_ptr_ = right_ptr;
}

std::shared_ptr<const Vertex> Vertex::GetZero() const {
    return left_ptr_;
}

std::shared_ptr<const Vertex> Vertex::GetOne() const {
    return right_ptr_;
}

bool Vertex::GetTerminate() const {
    return terminate_;
}

const MyChar &Vertex::GetChar() const {
    return v_char_;
}