#include "Image.hh"
#include <vector>
#include <fstream>
#include <string>

using namespace std;


class AbstractWriter {
    public:
        AbstractWriter(string_view path);
        virtual void write(const Image& image) = 0;
    protected:
        const string path_;
};

class TXTWriter : public AbstractWriter{
    public:
        TXTWriter(string_view path);
        void write(const Image& image) override;
};

class PPMWriter : public AbstractWriter{
    public:
        PPMWriter(string_view path);
        void write(const Image& image) override;
};