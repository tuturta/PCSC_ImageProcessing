#pragma once

#include <Eigen/Dense>
#include "Image.hh"

using Eigen::VectorXcd;
using Eigen::MatrixXcd;

/// @brief Abstract base class for Fourier Transform operations.
class FourierTransform {
    public:
    /// @brief Forward Fourier Transform on a 1D complex vector.
    /// @param input The input complex vector.
    virtual void fwd(VectorXcd& input) = 0;

    /// @brief Forward Fourier Transform on a 2D complex matrix.
    /// @param input The input complex matrix.
    virtual void fwd(MatrixXcd& input);

    /// @brief Inverse Fourier Transform on a 1D complex vector.
    /// @param input The input complex vector.
    virtual void inv(VectorXcd& input);

    /// @brief Inverse Fourier Transform on a 2D complex matrix.
    /// @param input The input complex matrix.
    virtual void inv(MatrixXcd& input);
};

/// @brief Implementation of Fast Fourier Transform (FFT).
class FFT : public FourierTransform { 
    public:
    /// @brief Forward Fourier Transform on a 1D complex vector using FFT.
    /// @param input The input complex vector.
    void fwd(VectorXcd& input) override;

    /// @brief Forward Fourier Transform on a 2D complex matrix using FFT.
    /// @param input The input complex matrix.
    void fwd(MatrixXcd& input) override;
};

/// @brief Implementation of Discrete Fourier Transform (DFT).
class DFT : public FourierTransform {
    public:
    /// @brief Forward Fourier Transform on a 1D complex vector using DFT.
    /// @param input The input complex vector.
    void fwd(VectorXcd& input) override;

    /// @brief Forward Fourier Transform on a 2D complex matrix using DFT.
    /// @param input The input complex matrix.
    void fwd(MatrixXcd& input) override;
};

/// @brief Abstract base class for image filters.
class Filter {
    public:
    /// @brief Constructor for the Filter class.
    /// @param image The image to apply the filter on.
    explicit Filter(Image& image);

    /// @brief Apply the filter to the image (pure virtual function).
    virtual void apply() = 0;

    protected:
    Image& image_; /**< Reference to the image being filtered. */

};

/// @brief Implementation of a Contour Extraction filter.
class ContourExtraction : public Filter {
    public:
    /// @brief Constructor for ContourExtraction filter.
    /// @param image The image to apply the filter on.
    explicit ContourExtraction(Image& image);

    /// @brief Apply the ContourExtraction filter to the image.
    void apply() override;
};

/// @brief Implementation of a Gaussian Filter.
class GaussianFilter : public Filter {
    public:
    /// @brief Constructor for GaussianFilter.
    /// @param image The image to apply the filter on.
    explicit GaussianFilter(Image& image);

    /// @brief Constructor for GaussianFilter with specified sigma and filter size.
    /// @param image The image to apply the filter on.
    /// @param sigma The standard deviation for the Gaussian filter.
    /// @param filter_size The size of the filter.
    /// @throw std::invalid_argument if filter_size is larger than the image or sigma is negative.
    GaussianFilter(Image& image, double sigma, size_t filter_size);

    /// @brief Apply the GaussianFilter to the image.
    void apply() override;

    private:
    double sigma_;      /**< Standard deviation for the Gaussian filter. */
    size_t filter_size_; /**< Size of the filter. */
};

/// @brief Checks if a given VectorXcd has a size that is not a power of two, pads it if needed.
/// @param input The VectorXcd to check and pad.
/// @return True if padding was applied, false otherwise.
bool padToPowerOfTwo(VectorXcd& input);

/// @brief Checks if a given MatrixXcd has row and column sizes that are not powers of two, pads it if needed.
/// @param input The MatrixXcd to check and pad.
/// @return True if padding was applied, false otherwise.
bool padToPowerOfTwo(MatrixXcd& input);

/// @brief Applies a filter to the input matrix.
/// @param input The input matrix.
/// @param filter The filter matrix.
/// @return The filtered matrix.
MatrixXcd applyFilter(const MatrixXcd& input, const MatrixXcd& filter);
