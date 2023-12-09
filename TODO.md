# 1. Determiner la structure du code et faire le diagramme des classes

* Un pixel est soit en RGB (structure) soit en noir et blanc (short unsigned int)
* typedef de 2D_array = array<array<'TYPE'>>

**Template <Pixel> class Image** 
_PUBLIC_
* constructeurs : 
  * à partir d'un tableau
  * générer un tableau avec la même valeurs partout ie Image(size_x, size_y, value)

* destructeur : pas forcément besoin

* constructeur de copie : peut être cool pour copier des images

* P getPixel(size_t pos_x, size_t pos_y) //return le pixel P
* void setPixel(size_t pos_x, size_t pos_y, P value) // set the pixel P with the value Value

_PRIVATE_:
* 2D_array<Pixel> data;

**class AbstractReader**
* public AbstractReader();
* public pure virtual Image read(const std::string& path);

**class CSVReader(AbstractReader)**
* public Image read(const std::string& path);

**class PNGReader(AbstractReader)**
* public Image read(const std::string& path);

**class TXTReader(AbstractReader)**
* public Image read(const std::string& path);


**class Output**
* public pure virtual void output(const std::string& path);
* protected Image& image;
* protected std::string path;

**class CSVOutput(Output)**
* public FileOutput(Image& image);
* public void save(const std::string& path);

**class PNGOutput(Output)**
* public FileOutput(Image& image);
* public void save(const std::string& path);
  
  **class TEXTOutput(Output)**
* public FileOutput(Image& image);
* public void save(const std::string& path);


- [ ] Faire le diagramme de classe

# 2. Coder les classes

- [x] Classe Pixel
- [ ] Classe Image
  - [ ] Tests
  - [ ] Documentation
- [ ] Classe Output
  - [x] TEXTOutput
  - [x] PPMOutput
  - [ ] Tests
  - [ ] Documentation
- [ ] Classe AbstractReader
  - [x] PPMReader
  - [x] TXTReader
  - [ ] Tests
  - [ ] Documentation
- [ ] Classe Compute
  - [x] FFT
  - [x] IFFT
  - [x] DFT
  - [x] IDFT
  - [ ] FFT(Image)
  - [ ] Adapter à la classe Image/Pixel
  - [ ] Transpose
  - [ ] Gtest
  - [ ] Documentation
- [ ] Histogram / Gplot

- [x] Choisir si on fait des pixels sur 8bits ou unsigned int
- [ ] Gestion des exceptions
  - [x] Classe Pixel
  - [ ] Classe Image (en cours)
  - [ ] Classe Compute
  - [ ] Classe Output
  - [ ] Classe AbstractReader


