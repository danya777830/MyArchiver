#include <memory>

template <typename T>
class MyPrioretyTree {
public:
    MyPrioretyTree() {
        size_ = 0;
        reserve_ = 0;
    }

    MyPrioretyTree(const MyPrioretyTree<T> &other) {
        reserve_ = other.reserve_;
        elements_array_ = std::make_unique(new T[reserve_]);
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            &elements_array_[i] = &other.elements_array_[i];
        }
    }

    MyPrioretyTree(MyPrioretyTree<T> &&other) {
        std::swap(size_, other.size_);
        std::swap(reserve_, other.reserve_);
        std::swap(elements_array_, other.elements_array_);
    }

    MyPrioretyTree &operator=(const MyPrioretyTree &other) {
        reserve_ = other.reserve_;
        elements_array_ = std::make_unique(new T[reserve_]);
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            &elements_array_[i] = &other.elements_array_[i];
        }
        return *this;
    }

    MyPrioretyTree &operator=(MyPrioretyTree &&other) {
        std::swap(size_, other.size_);
        std::swap(reserve_, other.reserve_);
        std::swap(elements_array_, other.elements_array_);
        return *this;
    }

    void Reserve(size_t size) {
        if (size <= reserve_) {
            return;
        }
        reserve_ = size;
        std::unique_ptr<T[]> new_ptr(new T[reserve_]);
        for (size_t i = 0; i < size_; ++i) {
            new_ptr[i] = elements_array_[i];
        }
        elements_array_ = std::move(new_ptr);
    }

    void Add(const T &ell) {
        if (size_ == reserve_) {
            if (reserve_ == 0) {
                Reserve(1);
            } else {
                Reserve(reserve_ * 2);
            }
        }

        elements_array_[size_] = ell;
        size_t new_el = size_;
        ++size_;

        while (new_el != 0) {
            if (elements_array_[(new_el + 1) / 2 - 1] < elements_array_[new_el]) {
                return;
            } else {
                std::swap(elements_array_[(new_el + 1) / 2 - 1], elements_array_[new_el]);
                new_el = (new_el + 1) / 2 - 1;
            }
        }
    }

    void DeleteMin() {
        if (size_ == 0) {
            return;
        }
        std::swap(elements_array_[0], elements_array_[size_ - 1]);
        --size_;
        if (size_ == 0) {
            return;
        }
        size_t new_el = 0;
        while ((new_el + 1) * 2 - 1 < size_) {
            size_t min_child = (new_el + 1) * 2 - 1;
            if (min_child + 1 < size_ && elements_array_[min_child + 1] < elements_array_[min_child]) {
                ++min_child;
            }
            if (elements_array_[min_child] < elements_array_[new_el]) {
                std::swap(elements_array_[min_child], elements_array_[new_el]);
                new_el = min_child;
            } else {
                return;
            }
        }
    }

    size_t Size() const {
        return size_;
    }

    bool Empty() const {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }

    const T &GetMin() const {
        return elements_array_[0];
    }

    ~MyPrioretyTree() {
    }

private:
    size_t size_;
    size_t reserve_;
    std::unique_ptr<T[]> elements_array_;
};