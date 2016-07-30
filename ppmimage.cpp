#include "ppmimage.h"
#include <iostream>
#include <string>

 PPMImage::PPMImage(){

 }

PPMImage::~PPMImage(){
    delete [] imageBits;
    imageBits = 0;
 }

std::ofstream& operator <<(std::ofstream& out, const PPMImage& img){

    out << img.magicNum << '\n';
    out << img.width << ' ' << img.height << '\n';
    out << img.maxColor << '\n';
    //write binary data
    int block = 3;
    int memoryBlockSize = block*img.width*img.height;
    out.write(img.imageBits, memoryBlockSize); //Write binary data into file
    out.close();
    return out;
}

std::ifstream& operator >>(std::ifstream& in, PPMImage& img){

    in >> img.magicNum;
    in >> img.width;
    in >> img.height;
    in >> img.maxColor;
    //ignore line feed
    in.ignore(1, '\n');
    //read in binary data
    int block = 3;
    int memoryBlockSize = block*img.width*img.height;
    img.imageBits = new char[memoryBlockSize];
    in.read(img.imageBits, memoryBlockSize); //Read binary data into array
    in.close();
    return in;
}

void PPMImage::decodeBit(char& decodeByte ,int decodeBitIndex ,char readByte)const{

    //read the least significant bit from readByte
     char mask = 1;

    if((mask & readByte) == 0)// bit is 0
    {
        //turn bit off
        mask = ~(1 << decodeBitIndex);
        decodeByte &= mask;

        //cout<< "0";

    }else{// bit is 1

        //turn bit on
        mask = 1 << decodeBitIndex;
        decodeByte |= mask;

       // cout << "1";
    }
    // cout << decodeByte;
 }

void PPMImage::encodeBit(char encodeByte, int encodeBitIndex,char& cryptByte){

    /*
        only changing the least significant bit in cryptByte.
        encodeBit is the index of the bit we will be get from
        encodeByte
    */
   // cout << encodeByte;
    char mask = 1 << encodeBitIndex;

    if((mask & encodeByte) == 0)// bit is 0
    {
        mask = ~(1);
        cryptByte &= mask;
        //cout << 0;
    }else{// bit is 1
        mask = 1;
        cryptByte |= mask;
        //cout << 1;
    }
}

void PPMImage::hideData(string message){

    int messageLength = message.length();
    int imageLength = getLength();

    for(int pixelByte = 2, i = 0; pixelByte < imageLength; i++)
    {
        bool done = (i == messageLength); //check to see if we encoded the last char in the message
        char encodeByte;
        if(done) encodeByte = '\0';
        else encodeByte = message[i];
       // cout << encodeByte;
        //encode character bit by bit. Start from most significant bit
        for(int j = 7; j > -1; j--,pixelByte+=3)
        {
            encodeBit(encodeByte, j, *(imageBits+pixelByte));
        }
        //cout << endl;
        if(done)return;
    }
}

string PPMImage::recoverData()const{

    string message;

    for(int pixelByte = 2, size = getLength(); pixelByte < size;)
    {
        //decode character bit by bit. start form most signif bit
        char decodedChar = '\0';
        for(int i = 7; i > -1 ; i--,pixelByte+=3)
        {
            decodeBit(decodedChar,i, *(imageBits+pixelByte));
        }
       // cout << decodedChar << endl;
        //break;
        if(decodedChar == '\0')break;
        else{
            message+=decodedChar;
        }
    }

    return message;
}

void PPMImage::grayscale(){

    for(int i = 0, length = getLength() ; i  < length; i+=3)
    {
       unsigned char R = imageBits[i];
       unsigned char G = imageBits[i+1];
       unsigned char B = imageBits[i+2];

       imageBits[i] = (R * .299) + (G * .587) + (B * .114);
       imageBits[i+1] = (R * .299) + (G * .587) + (B * .114);
       imageBits[i+2] = (R * .299) + (G * .587) + (B * .114);
    }
}

void PPMImage::sepia(){

   for(int i = 0, length = getLength() ; i  < length; i+=3)
    {
       unsigned char R = imageBits[i];
       unsigned char G = imageBits[i+1];
       unsigned char B = imageBits[i+2];

        //bound red
        int newVal = (R * .393) + (G *.769) + (B * .189);
        if(newVal > 255) imageBits[i] = 255;
        else imageBits[i] = newVal;
        //bound green
        newVal =(R * .349) + (G *.686) + (B * .168);
        if(newVal > 255) imageBits[i+1] = 255;
        else imageBits[i+1] = newVal;
        //bound blue
        newVal = (R * .272) + (G *.534) + (B * .131);
        if(newVal > 255) imageBits[i+2];
        else imageBits[i+2] = newVal;
    }
}

void PPMImage::negative(){

    for(int i = 0, length = getLength(); i< length ; i+=3)
    {
        //red
        imageBits[i] = 255 -  imageBits[i];
        //green
        imageBits[i+1] = 255 -  imageBits[i+1];
        //blue
        imageBits[i+2] = 255 -  imageBits[i+2];
    }

}

