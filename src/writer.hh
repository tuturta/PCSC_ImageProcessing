#pragma once

#include "Image.hh"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief Abstract base class for image writers.
 */
class AbstractWriter {
public:
    /**
     * @brief Constructor for AbstractWriter.
     * @param path The path to the file to be written.
     */
    explicit AbstractWriter(string_view path);

    /**
     * @brief Pure virtual function to write an Image.
     * @param image The Image to be written.
     */
    virtual void write(const Image& image) = 0;

protected:
    const string path_; /**< Path to the file. */
};

/**
 * @brief Implementation of a text file writer for images.
 */
class TXTWriter : public AbstractWriter {
public:
    /**
     * @brief Constructor for TXTWriter.
     * @param path The path to the text file to be written.
     */
    explicit TXTWriter(string_view path);

    /**
     * @brief Write the Image data to a text file.
     * @param image The Image to be written.
     */
    void write(const Image& image) override;
};

/**
 * @brief Implementation of a PPM file writer for images.
 */
class PPMWriter : public AbstractWriter {
public:
    /**
     * @brief Constructor for PPMWriter.
     * @param path The path to the PPM file to be written.
     */
    explicit PPMWriter(string_view path);

    /**
     * @brief Write the Image data to a PPM file.
     * @param image The Image to be written.
     */
    void write(const Image& image) override;
};