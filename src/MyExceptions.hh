#pragma once

#include <string>
#include <stdexcept>

class NegativeException : public std::runtime_error {
public:
    NegativeException(std::string const& msg) : std::runtime_error(msg) {}
};

class InvalidDimException : public std::runtime_error {
public:
    explicit InvalidDimException(std::string const& msg) : std::runtime_error(msg) {}
};
