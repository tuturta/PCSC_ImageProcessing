#pragma once

#include "Image.hh"
#include <vector>
#include <string>

/// @brief Abstract base class for image readers.
class AbstractReader {
    public:
    /// @brief Constructor for AbstractReader.
    /// @param path The path to the file to be read.
    explicit AbstractReader(std::string_view path);

    /// @brief Pure virtual function to read an Image.
    /// @return The Image read from the file.
    virtual Image read() = 0;

    protected:
    const std::string path_; ///< Path to the file.
};

/// @brief Implementation of a text file reader for images.
class TXTReader : public AbstractReader {
    public:
    /// @brief Constructor for TXTReader.
    /// @param path The path to the text file to be read.
    explicit TXTReader(std::string_view path);

    /// @brief Read the Image data from a text file.
    /// @return The Image read from the file.
    Image read() override;
};

/// @brief Implementation of a PPM P3 file reader for images.
class PPMReader : public AbstractReader {
    public:
    /// @brief Constructor for PPMReader.
    /// @param path The path to the PPM P3 file to be read.
    explicit PPMReader(std::string_view path);

    /// @brief Read the Image data from a PPM P3 file.
    /// @return The Image read from the file.
    Image read() override;
};
