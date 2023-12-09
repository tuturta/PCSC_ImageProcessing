#include<exception>

struct NegativeException : public std::exception {};

struct InvalidDimException : public std::exception {};