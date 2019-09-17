#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "SuffixTree.h"

using namespace std;

int main(int argc, char** argv)
{
    string filename;
    if(argc==1)
        filename = "strings.txt";
    else
        filename = argv[1];
    ifstream infile(filename);
    string parser;
    getline(infile,parser);
    int size = atoi( parser.c_str() );
    string* words = new string[size];
    int index = 0;

    while(getline(infile,parser) && index<size)
    {
        words[index] = parser;
        index++;
    }

    SuffixTree* deneme = new SuffixTree(words,size);
    deneme -> output();
}
