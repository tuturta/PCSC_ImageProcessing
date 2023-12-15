#include "../src/transform.hh"
#include "../src/reader.hh"
#include "../src/writer.hh"
#include "../src/Image.hh"
#include <Eigen/Dense>
#include <iostream>
#include<gtest/gtest.h>


using namespace std;
using Eigen::MatrixXcd;
using Eigen::VectorXcd;

class TransformTest : public ::testing::Test {
    protected:
        void SetUp() override{
            Eigen::MatrixXcd complexMatrix(3, 3);
            complexMatrix << std::complex<double>(1.0, 2.0), std::complex<double>(3.0, 4.0), std::complex<double>(5.0, 6.0),
                             std::complex<double>(7.0, 8.0), std::complex<double>(9.0, 10.0), std::complex<double>(11.0, 12.0),
                             std::complex<double>(13.0, 14.0), std::complex<double>(15.0, 16.0), std::complex<double>(17.0, 18.0);

            original_matrix = complexMatrix;

            Eigen::VectorXcd complexVector(5);
            complexVector << std::complex<double>(1.0, 2.0), std::complex<double>(3.0, 4.0), std::complex<double>(5.0, 6.0),
                             std::complex<double>(7.0, 8.0), std::complex<double>(9.0, 10.0);
            original_vector = complexVector;
        }

        MatrixXcd original_matrix;
        VectorXcd original_vector;
};

class PadToPowerOfTwoTest : public TransformTest {};
class FourierTransformTest : public TransformTest {};

// Test case for padToPowerOfTwo with VectorXcd
TEST_F(PadToPowerOfTwoTest, test_padding_vector) {
    cout << original_vector.size() << endl;
    // Test the padToPowerOfTwo function
    bool result = padToPowerOfTwo(original_vector);

    // Add your assertions based on the expected behavior
    ASSERT_TRUE(result);
    EXPECT_EQ(original_vector.size(), 8);  // Check the size after padding
}

// Test case for padToPowerOfTwo with MatrixXcd
TEST_F(PadToPowerOfTwoTest, test_padding_matrix) {
    // Test the padToPowerOfTwo function
    bool result = padToPowerOfTwo(original_matrix);

    // Add your assertions based on the expected behavior
    ASSERT_TRUE(result);
    EXPECT_EQ(original_matrix.rows(), 4);  // Check the number of rows after padding
    EXPECT_EQ(original_matrix.cols(), 4);  // Check the number of columns after padding
}

// Test case to verify FFT inverse and forward operations
TEST_F(FourierTransformTest, test_identity_FFT_IFFT) {
    // Create a random MatrixXcd
    MatrixXcd originalMatrix = MatrixXcd::Random(4, 4);

    // Forward FFT
    FFT fft;
    MatrixXcd transformedMatrix(originalMatrix);
    fft.fwd(transformedMatrix);

    // Inverse FFT
    fft.inv(transformedMatrix);

    // Check if the result is approximately equal to the original matrix
    EXPECT_TRUE(originalMatrix.isApprox(transformedMatrix, 1e-10));
}

// Main function to run the tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
