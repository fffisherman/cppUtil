#include <exception>
#include <string>

class Exception : public std::exception {
public:
    Exception(std::string what);
    ~Exception() noexcept override = default;

    const char* what() const noexcept override {
        return message_.c_str();
    }

    const char* stackTrace() const noexcept {
        return stack_.c_str();
    }

    
private:
    std::string stackTrace(bool demangle);
    std::string message_;
    std::string stack_;
};