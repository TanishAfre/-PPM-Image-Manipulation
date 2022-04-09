//
// Created by floodd on 23/03/2022.
// Tanish Afre
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"



bool Image::load(string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
    try {
        if (ifs.fail()) { return false;}
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) {return false;}
        ifs >> w >> h >> b;
        this->w = w; this->h = h;
        this->pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3];
        // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i) {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
            if (this->pixels[i].r > 0.7) this->pixels[i].r;
            if (this->pixels[i].g > 0.7) this->pixels[i].g;
            if (this->pixels[i].b > 0.7) this->pixels[i].b;
        }
        ifs.close();
        return true;
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ifs.close();
        return false;
    }
    return false;
}

//Gamma encoding
bool Image::loadRaw(string filename)
{
    ifstream in(filename);
    if(in.good())
    {
        in >> w;
        in >> h;

        for(int i = 0; i < w*h; i++)
        {
            float r, g, b;
            in >> r >>g>>b;
            this->pixels[i].r = (unsigned char) (r *255);
            this->pixels[i].g = (unsigned char) (g *255);
            this->pixels[i].b = (unsigned char) (b *255);
            cout << r << this->pixels[i].r<< endl;
        }
        in.close();
        return true;
    }
    return false;
}

bool Image::savePPM(string filename)
{
    if (this->w == 0 || this->h == 0) {return false;}
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
        if (ofs.fail()) return false;
        ofs << "P6\n"<< this->w << " " << this->h << "\n255\n";
        unsigned char r, g, b;
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < this->w * this->h; ++i) {
            r = static_cast<unsigned char>(std::min(1.f, (float)this->pixels[i].r)* this->pixels[i].r);
            g = static_cast<unsigned char>(std::min(1.f, (float)this->pixels[i].g)* this->pixels[i].g);
            b = static_cast<unsigned char>(std::min(1.f, (float)this->pixels[i].b)* this->pixels[i].b);
            ofs << r << g << b;
        }
        ofs.close();
        return true;
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
    return false;
}

void Image::filterRed()
{
    for (int i = 0; i < this->w * this->h; ++i) {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}

void Image::filterGreen()
{
    for (int i = 0; i < this->w * this->h; ++i) {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}

void Image::filterBlue()
{
    for (int i = 0; i < this->w * this->h; ++i) {
        this->pixels[i].g = 0;
        this->pixels[i].r = 0;
    }
}

void Image::greyScale()
{
    for(int r = 0; r < h; r++)
    {
        for(int c = 0;  c< w;c++)
        {
            int num = (this->pixels[r*w+c].r + this->pixels[r*w+c].g+this->pixels[r*w+c].b)/3;
            this->pixels[r*w+c].r=this->pixels[r*w+c].g=this->pixels[r*w+c].b=num;
        }
    }
}

void Image::flipHorizontal()
{
    for(int c = 0;  c< w/2;c++)    //x axis
    {
        for(int r = 0; r < h; r++)  //y axis
        {
            swap(this->pixels[(r * w + c)].r,this->pixels[(r * w + (w - c))].r);
            swap(this->pixels[(r * w + c)].g,this->pixels[(r * w + (w - c))].g);
            swap(this->pixels[(r * w + c)].b ,this->pixels[(r * w + (w - c))].b);
        }
    }
}

void Image::flipVertically()
{
    for(int x = 0;  x<w ; x++)    //x axis
    {
        for(int y = 0; y < h/2 ; y++)  //y axis
        {
            swap(this->pixels[(x+y*w)].r,this->pixels[x+(h-1-y)*w].r);
            swap(this->pixels[(x+y*w)].g,this->pixels[x+(h-1-y)*w].g);
            swap(this->pixels[(x+y*w)].b,this->pixels[x+(h-1-y)*w].b);
        }
    }
}

void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
{

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}