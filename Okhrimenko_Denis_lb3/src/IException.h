#ifndef IEXCEPTION_H 
#define IEXCEPTION_H

#include <iostream>

class IException : public std::exception
{
private:
    std::string message;

public:
    explicit IException(std::string message) : message{std::move(message)} {};

    virtual const char* what() const noexcept override {
        return message.c_str();
    };
};

#endif