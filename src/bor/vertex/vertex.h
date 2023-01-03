#include <memory>

using MyChar = unsigned int;

class Vertex {
    bool terminate_ = false;
    MyChar v_char_;
    std::shared_ptr<Vertex> left_ptr_;
    std::shared_ptr<Vertex> right_ptr_;

public:
    Vertex();
    explicit Vertex(const MyChar &ch);
    Vertex(std::shared_ptr<Vertex> &left_ptr, std::shared_ptr<Vertex> &right_ptr);

    std::shared_ptr<const Vertex> GetZero() const;
    std::shared_ptr<const Vertex> GetOne() const;
    const MyChar &GetChar() const;
    bool GetTerminate() const;
};