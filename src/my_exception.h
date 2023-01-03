#include <exception>
#include <string>

class CanNotOpenFile : std::exception {
public:
    explicit CanNotOpenFile(std::string message) : m_error_("не удалось открыть файл: " + message){};

    const char* what() const noexcept final {
        return m_error_.c_str();
    }

private:
    std::string m_error_;
};

class NotSetFile : std::exception {
public:
    NotSetFile(){};

    const char* what() const noexcept final {
        return "файл закрыт";
    }
};

class BadArchive : std::exception {
public:
    BadArchive(){};

    const char* what() const noexcept final {
        return "переданный архив не коректен";
    }
};