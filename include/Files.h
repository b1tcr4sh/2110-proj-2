#ifndef _FILES_H_
#define _FILES_H_

#include <fstream>

using namespace std;

class Files {
    public:
        // ifstream LoadFile(const string& filename); // wrapper function for loading files that includes error handling and formatting
        string trim(string input); // trim a string
        string to_upper(string input); // make a string all uppercase
    private:
};


#endif