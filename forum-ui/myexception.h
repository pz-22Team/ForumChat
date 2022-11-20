#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <exception>
#include <string>

class MyException: public std::exception {
private:
    std::string exceptionText;
public:
    MyException(std::string text);
    const char* what() const noexcept;
};

#endif // MYEXCEPTION_H
