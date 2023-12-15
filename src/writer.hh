#pragma once

#include "Image.hh"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/// @brief Abstract base class for image writers.
class AbstractWriter {
    public:
    /// @brief Constructor for AbstractWriter.
    /// @param path The path to the file to be written.
    /// @param image The Image to be written.
    explicit AbstractWriter(string_view path, const Image& image);

    /// @brief Pure virtual function to write an Image.
    virtual void write() = 0;

    protected:
    const string path_; ///< Path to the file.
    const Image& image_; ///< Image to be written.
};

/// @brief Implementation of a text file writer for images.
class TXTWriter : public AbstractWriter {
    public:
    /// @brief Constructor for TXTWriter.
    /// @param path The path to the text file to be written.
    /// @param image The Image to be written.
    explicit TXTWriter(string_view path, const Image& image);

    /// @brief Write the Image data to a text file.
    void write() override;
};

/// @brief Implementation of a PPM file writer for images.
class PPMWriter : public AbstractWriter {
    public:
    /// @brief Constructor for PPMWriter.
    /// @param path The path to the PPM file to be written.
    /// @param image The Image to be written.
    explicit PPMWriter(string_view path, const Image& image);

    /// @brief Write the Image data to a PPM file.
    void write() override;
};
