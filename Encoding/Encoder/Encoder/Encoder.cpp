// Encoder.cpp : 
// Console application that will encode files using RLE compression using the following command-line interfaces:
// rle [--debug] [--help] inputfile [outputfile]
//

#include <iostream>
#include <fstream>
using namespace std;

// Function to get the data from input file and output this file as .rle (compressed)
void outputRLE(ifstream& in, ofstream& out, bool debugMode) {
    char ch;                // store the input characters
    uint8_t countCh = 0;    // count how many repeated caracters there is in the file
    char aux = -1;          // auxiliar variable to hold the previous char read
    uint8_t const MAXCOUNT = 255;
    while (in.read(&ch, sizeof(char)))
    {
        // check if the current char is the same to the previous, or if is the first time in loop, up to 255.
        if ((ch == aux || countCh == 0) && countCh < MAXCOUNT)
            countCh++;
        //when the char read is different from previous one it will print the number of chars followed by that char
        else
        {
            out.put(countCh);
            out.put((unsigned(uint8_t(aux))));
            if (debugMode)
                cout << (unsigned)countCh << " " << unsigned(uint8_t(aux)) << endl;
            countCh = 1;
        }
        aux = ch;
    }//end while
    // if the file contains only reapeated data count = 1, then we need to print to the output file
    if (countCh >= 1) {
        out.put(countCh);
        out.put((unsigned(uint8_t(aux))));
        if (debugMode)
            cout << (unsigned)countCh << " " << unsigned(uint8_t(aux)) << endl;
    }
}// end function


//print help
void printHelp() {
    cout << "rle (c) 2020-1, Garth Santor" << endl;
    cout << string(59, '=') << endl;
    cout << "Version 2.0.0" << endl;
    cout << "\nA run-length encoder utility." << endl;
    cout << "\nc" << endl;
    cout << "Examples:" << endl;
    cout << "\trle myfile.doc \n\t> encodes 'myfile.doc' to 'myfile.doc.rle' (binary output)" << endl;
    cout << "\nrle --debug ..\\myfile.doc \n\t> encodes 'myfile.doc' from the parent folder to 'myfile.doc.rle'"
        " (text output) into the current folder" << endl;
    cout << "\nrle myfile.doc ..\\out \n\t> encodes 'myfile.doc' from the current folder to 'myfile.doc.rle' into the '..\\out'" << endl;
    cout << "\nrle --help \n\t> displays the help" << endl;
    cout << "\n\trle --version" << endl;
    cout << "\t\t> displays version number in the format d.d.d" << endl;
}

//main program
int main(int argc, char* argv[])
{
    ifstream fileIn;
    ofstream fileOut;
    string filename;
    bool isDebug = false;
    if (argc == 1) {
        cout << "Error: no commandline arguments detected - showing help." << endl;
        printHelp();
        exit(EXIT_FAILURE);
    }
    // print the help and exit program
    if (strcmp(argv[1], "--help") == 0) {
        printHelp();
        exit(EXIT_SUCCESS);
    }
    
    if (argc == 2) {
        if (strcmp(argv[1], "--debug") == 0) {
            cout << "Error! No input file specified.";
        }
        else {
            filename = argv[1];
            fileIn.open(filename, ios::in | ios::binary);
            if (!fileIn){
                cout << "Error: program <" << filename << "> doesn't exist." << endl;
                exit(EXIT_FAILURE);
            }
            fileOut.open(filename + ".rle", ios::out | ios::binary);
            if (!fileOut) {
                cout << "Fail to create the file " << filename + ".rle" << "." << endl;
                exit(EXIT_FAILURE);
            }

        }
    }
    
    // if argc == 3 means that the command line would be rle --debug inputfile or rle inputfile outputfile
    else if (argc == 3) {
        // open the outputfile as text if the second command is --debug
        if (strcmp(argv[1],"--debug") == 0) {
            filename = argv[2];
            isDebug = true;
            fileIn.open(filename, ios::in | ios::binary);
            if (!fileIn) {
                cout << "Fail to read the file " << filename << ". File not found!" << endl;
                exit(EXIT_FAILURE);
            }
            fileOut.open(filename + ".rle", ios::out);
            if (!fileOut) {
                cout << "Fail to create the file " << filename + ".rle" << "." << endl;
                exit(EXIT_FAILURE);
            }
        }
        // open inputfile and outputfile named from the command
        else {
            fileIn.open(argv[1], ios::in | ios::binary);
            if (!fileIn) {
                cout << "Fail to read the file " << argv[1] << ". File not found!" << endl;
                exit(EXIT_FAILURE);
            }
            filename = argv[2];
            fileOut.open(filename + ".rle", ios::out | ios::binary);
            if (!fileOut) {
                cout << "Fail to create the file " << argv[2] << "." << endl;
                exit(EXIT_FAILURE);
            }
        }
        
    }// end else if argc == 3
    
     // This condition covers rle --debug inputfile outputfile
    else if (argc == 4) {
        if (strcmp(argv[1],"--debug") == 0) {
            isDebug = true;
            fileIn.open(argv[2], ios::in | ios::binary);
            if (!fileIn) {
                cout << "Fail to read the file " << argv[2] << ". File not found!" << endl;
                exit(EXIT_FAILURE);
            }
            filename = argv[3];
            fileOut.open(filename + ".rle", ios::out);
            if (!fileOut) {
                cout << "Fail to create the file " << filename << "." << endl;
                exit(EXIT_FAILURE);
            }

        }
        else {
            cout << "Error: program " << argv[1] << " does not exist." << endl;
            exit(EXIT_FAILURE);
        }

    }//end else if argc == 4
    else {
        cout << "Error: Too may arguments!" << endl;
        exit(EXIT_FAILURE);
    }
    outputRLE(fileIn, fileOut, isDebug);
    fileIn.close();
    fileOut.close();
    

}//end main
