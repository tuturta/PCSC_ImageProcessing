#pragma once
#include <Eigen/Dense>


class FourierTransform{
    public:
        virtual void transform(Eigen::VectorXcd & input) = 0;
        virtual void transform(Eigen::MatrixXcd& input);
        virtual void inverse_transform(Eigen::VectorXcd & input);
        virtual void inverse_transform(Eigen::MatrixXcd & input);
};

class FFT : public FourierTransform{
    public:
        void transform(Eigen::VectorXcd& input) override;
        void transform(Eigen::MatrixXcd& input) override;
};

class DFT : public FourierTransform{
    public:
        void transform(Eigen::VectorXcd& input) override;
        void transform(Eigen::MatrixXcd& input) override;
};

bool padToPowerOfTwo(Eigen::VectorXcd& input);
bool padToPowerOfTwo(Eigen::MatrixXcd& input);
// vector<complex<double>> to_complex(const vector<unsigned int>& input);
