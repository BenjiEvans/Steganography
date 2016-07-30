#ifndef PPMIMAGE_H
#define PPMIMAGE_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class PPMImage{
private:
    int height;
    int width;
    int maxColor;
    string magicNum;
    char* imageBits;
    int getLength()const{
        return 3*width*height;
    }
    void encodeBit(char,int,char&);//complete
    void decodeBit(char&,int,char)const;//complete
public:
    PPMImage();//complete
    ~PPMImage(); //complete
    friend std::ofstream& operator <<(std::ofstream& out, const PPMImage& img);// complete
    friend std::ifstream& operator >>(std::ifstream& in, PPMImage& img);//complete
    void hideData(string message);// complete
    string recoverData()const;// complete
    void grayscale();
    void sepia();
    void negative();//complete

};

#endif

