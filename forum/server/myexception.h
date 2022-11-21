#pragma once
#include <exception>
#include <string>
class MyException: public std::exception {
private:
    std::string exceptionText;
public:
    MyException(std::string text);
    const char* what() const noexcept;
};

