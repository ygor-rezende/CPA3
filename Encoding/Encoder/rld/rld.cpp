// rld.cpp : 
//Console application that will decode RLE files using the following command - line interfaces :
// rld [--debug] [--help] inputfile [outputfile]
//

#include <iostream>
#include <fstream>
using namespace std;

// Function to convert a compressed file (.rle) and output this file decoded
void outputRLD(ifstream& in, ofstream& out, bool debugMode) {
    char ch;                // store the characters to be output
    char numCh;             // store the number of chars to be output
    //first read numch (number of repetitions)
    while (in.read(&numCh, sizeof(char)))
    {
        //read the char
        in.read(&ch, sizeof(char));
        
        //put char in the file numCh times
        for(size_t i = 0; i < unsigned(uint8_t(numCh)); i++){
            out.put(ch);
        }
        if (debugMode)
            cout << unsigned(uint8_t(numCh)) << " " << unsigned(uint8_t(ch)) << endl;
        
    }
}// end function

//print help
void printHelp() {
    cout << "rld (c) 2020-1, Garth Santor" << endl;
    cout << string(59, '=') << endl;
    cout << "Version 2.0.0" << endl;
    cout << "\nA run-length decoder utility." << endl;
    cout << "\nUsage: rld [--debug] [--help] [--version] infile [outfile]" << endl;
    cout << "\nExamples:" << endl;
    cout << "rld myfile.doc.rle \n\t> decodes 'myfile.doc.rle' to 'myfile.doc' (binary input)" << endl;
    cout << "\nrld --debug myfile.doc.rle \n\t> decodes 'myfile.doc.rle' to 'myfile.doc' (text input)" << endl;
    cout << "\nrld myfile.doc ..\\out \n\t> decodes 'myfile.doc' from the current folder to 'myfile.doc.rle' into the '..\\out'" << endl;
    cout << "\nrld --help \n\t> displays the help" << endl;
    cout << "\n\trld --version" << endl;
    cout << "\t\t> displays version number in the format d.d.d" << endl;
}

// returns the position (int) of .rle if found and -1 if not found
int hasRle(string filename)
{
    return filename.find(".rle");
}//end function


int main(int argc, char* argv[])
{
    ifstream fileIn;
    ofstream fileOut;
    string filename;
    size_t pos = 0;
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
            if ((pos = hasRle(filename)) == -1){
                cout << "Error: program <" << filename << "> doesn't exist." << endl;
                exit(EXIT_FAILURE);
            }
            else{
                fileIn.open(filename, ios::in | ios::binary);
                if (!fileIn) {
                    cout << "Error: program <" << filename << "> doesn't exist." << endl;
                    exit(EXIT_FAILURE);
                }
                fileOut.open(filename.substr(0, pos), ios::out | ios::binary);
                if (!fileOut) {
                    cout << "Fail to create output file." << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }//end else
    }//end if

     // if argc == 3 means that the command line would be rld --debug inputfile or rld inputfile outputfile
    else if (argc == 3) {
        // open the outputfile as text if the second command is --debug
        if (strcmp(argv[1], "--debug") == 0) {
            filename = argv[2];
            isDebug = true;
            if ((pos = hasRle(filename)) == -1)
                cout << "Error! No .rle extension found. Please provide an output file." << endl;
            else{
                fileIn.open(filename, ios::in | ios::binary);
                if (!fileIn) {
                    cout << "Fail to read the file " << filename << ". File not found!" << endl;
                    exit(EXIT_FAILURE);
                }
                fileOut.open(filename.substr(0, pos), ios::out);
                if (!fileOut) {
                    cout << "Fail to create output file." << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        // open inputfile and outputfile named from command
        else {
            filename = argv[1];
            if ((pos = hasRle(filename)) == -1)
                cout << "Error! No .rle extension found." << endl;
            else{
                fileIn.open(filename, ios::in | ios::binary);
                if (!fileIn) {
                    cout << "Fail to read the file " << filename << ". File not found!" << endl;
                    exit(EXIT_FAILURE);
                }
                filename = argv[2];
                fileOut.open(filename, ios::out | ios::binary);
                if (!fileOut) {
                    cout << "Fail to create output file. " << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

    }// end else if argc == 3

    // This condition covers rld --debug inputfile outputfile
    else if (argc == 4) {
        if (strcmp(argv[1], "--debug") == 0) {
            isDebug = true;
            filename = argv[2];
            fileIn.open(filename, ios::in | ios::binary);
            if (!fileIn) {
                cout << "Fail to read the file " << argv[2] << ". File not found!" << endl;
                exit(EXIT_FAILURE);
            }
            filename = argv[3];
            fileOut.open(filename, ios::out);
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

    outputRLD(fileIn, fileOut, isDebug);
    fileIn.close();
    fileOut.close();

}//end main


