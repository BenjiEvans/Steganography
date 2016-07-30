#include <iostream>
#include <fstream>
#include <string>
#include "ppmimage.h"
using namespace std;

void hideMessage(ifstream& in);
void recoverMessage(ifstream& in);
void convertToGrayscale(ifstream& in);
void convertToSepia(ifstream& in);
void convertToNegative(ifstream& in);
string getSourceFileName();
string getOutputFileName();

int main()
{
    cout << "What would you like to do?\n";
    cout << "    " << "a.) Hide a message\n";
    cout << "    " << "b.) Recover a message\n";
    cout << "    " << "c.) Convert image to grayscale\n";
    cout << "    " << "d.) Convert image to sepia\n";
    cout << "    " << "e.) Convert image to negative\n";
    cout << "    " << "f.) Exit\n";
    char choice;
    cout << "Enter your selection: ";
    cin >> choice;

    if(choice == 'f')return 0;
    string inFileName = getSourceFileName();

    ifstream inFile;
    inFile.open(inFileName.c_str(), std::ifstream::binary);

    if(!inFile.fail())
    {
         switch(choice){
        case 'a':
            hideMessage(inFile);
            break;
        case 'b':
            recoverMessage(inFile);
            break;
        case 'c':
            convertToGrayscale(inFile);
            break;
        case 'd':
            convertToSepia(inFile);
            break;
        case 'e':
            convertToNegative(inFile);
            break;
        }

    }else cout << "Sorry source file specified was not found..\n";

    return 0;
}


void hideMessage(std::ifstream& in){

    string outFileName = getOutputFileName();
    cout << "Please enter a phrase to hide: ";
    string message;
    cin.get();
    getline(cin, message);
    PPMImage image;
    in >> image;
    image.hideData(message);
    ofstream outFile;
    outFile.open(outFileName.c_str(),std::ofstream::binary);
    outFile << image;
    cout << "Your message \"" << message <<"\" has been hidden in file: " << outFileName;
}


void recoverMessage(std::ifstream& in){
    PPMImage image;
    in >> image;
    cout << "Hidden message: "  << image.recoverData();
}


void convertToGrayscale(std::ifstream& in){
     PPMImage image;
     in >> image;
     string outFileName = getOutputFileName();
     ofstream outFile;
     outFile.open(outFileName.c_str(), std::ofstream::binary);
     image.grayscale();
     outFile << image;
     cout << "Your image has been converted to Grayscale and stored in file: " << outFileName;
}

void convertToSepia(std::ifstream& in){
     PPMImage image;
     in >> image;
     string outFileName = getOutputFileName();
     ofstream outFile;
     outFile.open(outFileName.c_str(), std::ofstream::binary);
     image.sepia();
     outFile << image;
     cout << "Your image has been converted to Sepia and stored in file: " << outFileName;
}


void convertToNegative(std::ifstream& in){
    PPMImage image;
    in >> image;
    string outFileName = getOutputFileName();
    ofstream outFile;
    outFile.open(outFileName.c_str(), std::ofstream::binary);
    image.negative();
    outFile << image;
    cout << "Your image has been converted to Negative and stored in file: " << outFileName;
}

string getSourceFileName(){
    string filename;
    cout << "Please specify the source PPM filename: ";
    cin >> filename;
    return filename;
}

string getOutputFileName(){
    string filename;
    cout << "Please specify the output PPM filename: ";
    cin >> filename;
    return filename;
}



