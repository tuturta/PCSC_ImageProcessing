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

class NegativeDimException : public std::invalid_argument {
public:
    explicit NegativeDimException(std::string const& msg) : std::invalid_argument(msg) {}
};

class NegativePixelValueException : public std::invalid_argument {
public:
    explicit NegativePixelValueException(std::string const& msg) : std::invalid_argument(msg) {}
};

class WrongPpmFormatException : public std::invalid_argument {
public:
    explicit WrongPpmFormatException(std::string const& msg) : std::invalid_argument(msg) {}
};

class WrongFileFormatException : public std::invalid_argument {
public:
    explicit WrongFileFormatException(std::string const& msg) : std::invalid_argument(msg) {}
};

class PixelDimException : public std::domain_error {
public:
    explicit PixelDimException(std::string const& msg) : std::domain_error(msg) {}
};

class RectangleImageException : public std::domain_error {
public:
    explicit RectangleImageException(std::string const& msg) : std::domain_error(msg) {}
};

class MinImageSizeException : public std::invalid_argument {
public:
    explicit MinImageSizeException(std::string const& msg) : std::invalid_argument(msg) {}
};