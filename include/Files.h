#ifndef _FILES_H_
#define _FILES_H_

#include <fstream>
#include <vector>

using namespace std;

class Files {
    public:
        // ifstream LoadFile(const string& filename); // wrapper function for loading files that includes error handling and formatting
        static string trim(string input); // trim a string
        static string to_upper(string input); // make a string all uppercase
        static string to_lower(string input); // make a string all lowercase
        static vector<string> split(string input, string delim); // split a string into tokens and return them as a vector
        static vector<string> processFileLine(string line, string delim, int &lineNumber); // take a line from a file and process it (including error handling) then return it's tokens
    private:
};


#endif