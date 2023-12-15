#pragma once

#include <string>
#include <stdexcept>

/// @brief Runtime exception to throw when expected positive value but got negative one
class NegativeException : public std::runtime_error {
public:
    NegativeException(std::string const& msg) : std::runtime_error(msg) {}
};

/// @brief Runtime exception to throw when an index is inconsistent with an object dimension
class InvalidDimException : public std::runtime_error {
public:
    explicit InvalidDimException(std::string const& msg) : std::runtime_error(msg) {}
};
