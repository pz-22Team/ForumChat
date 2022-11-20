#include "myexception.h"

MyException::MyException(std::string text ):exceptionText(text)  {}

const char *MyException::what() const noexcept {
    return exceptionText.c_str();
}
