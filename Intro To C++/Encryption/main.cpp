#include <iostream>
#include <fstream>
#include "crypt.h"

using namespace std;

int main(int argc, char* argv[]) {
    //Command line arguments
    int encrypt = 0;
    int key = 0;
    string infile = "";
    string outfile = "";
    bool error = false;

    for (int i = 1; i < argc; i++) {
        //Prevent duplicate args
        for (int j = i+1; j<argc; j++) {
            if (string(argv[i]) == string(argv[j])) error = true;
        }

        //Command translation
        if (string(argv[i]) == "-e") encrypt++;
        else if (string(argv[i]) == "-d") encrypt--;
        else if (string(argv[i]) == "-k" && i+1 < argc) {
            for (int j = 0; j < string(argv[i+1]).length(); j++)
                if (!isdigit(argv[i+1][j])) error = true;
            key = stoi(argv[i+1]);
            i++;
        }
        else if (string(argv[i]) == "-i" && i+1 < argc) {
            infile = argv[i+1];
            i++;
        }
        else if (string(argv[i]) == "-o" && i+1 < argc) {
            outfile = argv[i+1];
            i++;
        }
    }

    //cout <<"test"<<error<<encrypt<<endl;

    //Resiliency
    if (key == 0 || infile.empty() || outfile.empty() || error || encrypt == 0) {
        cout <<"Error: incorrect argument format\nUsage: "<<argv[0]<<" [-e|-d] -k <key> -i <inputFile> -o <outputFile>"<<endl;
        return 1;
    }

    //In file
    ifstream in(infile);
    if (!in) {
        cout <<"Error: could not open input file "<<infile<<endl;
        return 1;
    }

    string inText((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>()));
    in.close();

    //Encrypt or decrypt the input text
    string output = cryption(inText, encrypt*key);

    //Out file
    ofstream out(outfile);
    if (!out) {
        cout <<"Error: could not open output file "<<outfile<<endl;
        return 1;
    }

    out<<output;
    out.close();

    return 0;
}
