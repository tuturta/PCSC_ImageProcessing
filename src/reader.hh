#include "Image.hh"
#include <vector>
#include <string>

using namespace std;


class AbstractReader {
    public:
        AbstractReader(string_view path);
        virtual Image read() = 0;
    protected:
        const string path_;
};

class TXTReader : public AbstractReader{
    public:
        TXTReader(string_view path);
        Image read() override;
};

class PPMReader : public AbstractReader{
    public:
        PPMReader(string_view path);
        Image read() override;
};