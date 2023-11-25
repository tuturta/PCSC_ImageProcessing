# 1 Determiner la structure du code et faire le diagramme des classes

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
* public pure virtual 2D_array<Pixel> read(const std::string& path);

**class CSVReader(AbstractReader)**
* public 2D_array<Pixel> read(const std::string& path);

**class Output**
* public pure virtual void output(const std::string& path);
* protected Image& image;
* protected std::string path;

**class FileOutput(Output)**
* public FileOutput(Image& image);
* public void save_in_CSV(const std::string& path);

