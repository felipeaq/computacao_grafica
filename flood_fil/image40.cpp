#include <fstream>
#include <iostream>
// #include <string>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

struct pixel
{
    int r;
    int g;
    int b;

};


class image
{
public:
    image();
    ~image();
    void loadimage(string nombre);
    void saveimage(string nombre);
    void resize(int x, int y);
    void setpixel(int x, int y, int red, int green, int blue);
    int getred(int x, int y);
    int getgreen(int x, int y);
    int getblue(int x, int y);
private:
    int width;
    int height;
    int maxcolor;

    pixel **img;
    pixel **imgbuffer;
};

image::image()
{
    height=1080, width=1920;
    img = new pixel*[width];
    for(int i = 0; i < width; ++i)
    {
        img[i] = new pixel[height];
    }

    imgbuffer = new pixel*[width];
    for(int i = 0; i < width; ++i)
    {
        imgbuffer[i] = new pixel[height];
    }


}

void image::resize(int x, int y)
{
    for(int i = 0; i < width; ++i)
    {
        delete [] img[i];
    }
    delete [] img;

    for(int i = 0; i < width; ++i)
    {
        delete [] imgbuffer[i];
    }
    delete [] imgbuffer;

    width=x, height=y;

    img = new pixel*[width];

    for(int i = 0; i < width; ++i)
    {
        img[i] = new pixel[height];
    }

    imgbuffer = new pixel*[height];

    for(int i = 0; i < width; ++i)
    {
        imgbuffer[i] = new pixel[height];
    }


}

image::~image()
{

    for(int i = 0; i < width; ++i)
    {
        delete [] img[i];
    }
    delete [] img;

    for(int i = 0; i < width; ++i)
    {
        delete [] imgbuffer[i];
    }
    delete [] imgbuffer;

}

int image::getred(int i, int j)
{
    return  img[i][j].r;
}
int image::getgreen(int i, int j)
{
    return  img[i][j].g;
}
int image::getblue(int i, int j)
{
    return  img[i][j].b;
}

void image::setpixel(int i,int j,int red=0,int green=0,int blue=0)
{
    imgbuffer[i][j].r=red;
    imgbuffer[i][j].g=green;
    imgbuffer[i][j].b=blue;
}

void image::loadimage(string nombre)
{
    int red,green,blue,width_f,height_f;

    cout << "Arquivo de entrada "<< nombre <<endl;
    ifstream iFile(nombre.c_str());

    if (iFile==NULL)
    {
        cout << "Missing file!" << endl;
        exit(0);
    }

    iFile.ignore(INT_MAX, '\n');
    //  iFile.ignore(INT_MAX, '\n');


    iFile >> width_f;
    iFile >> height_f;
    iFile >> maxcolor;

    if (width_f > width || height_f > height)
		resize(width_f,height_f);

    width=width_f;
	height=height_f;

    for(int j=0; j<height; j++)
        for(int i=0; i<width; i++)
        {

            iFile >> red;
            iFile >> green;
            iFile >> blue;
            img[i][j].r=red;
            img[i][j].g=green;
            img[i][j].b=blue;

        }

    iFile.close();

}
void image::saveimage(string nombre)
{
    ofstream oFile(nombre.c_str());

    if (oFile==NULL)
    {
        cout << "Missing file!" << endl;
        exit(0);
    }
    oFile << "P3\n" << "#Created by the author" << "\n" << width << " "
          << height << "\n" << maxcolor << "\n";


    for(int j=0; j<height; j++)
        for(int i=0; i<width; i++)

//            oFile << imgbuffer[i][j].r << " " << imgbuffer[i][j].g << " " << imgbuffer[i][j].b << " ";
            oFile << img[i][j].r << " " << img[i][j].g << " " << img[i][j].b << " ";

    oFile.close();
}
int main(int argc, char **argv)
{

    if (argc<3)
    {
        cout << "insufficient arguments" << endl;
        exit(0);
    }

    image* fig1= new image();

    fig1->loadimage(argv[1]);
    fig1->saveimage(argv[2]);

    delete fig1;

    return 0;
}
