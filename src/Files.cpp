// author: Rylee Ford
// purpose: implements some static helper functions for parsing files and string input. The goal is to standardize the error handling and method of loading for our group so we get consistent behavior.

#include "../include/Files.h"
#include <cctype>
#include <algorithm>

using namespace std;

string Files::trim(string input) { // trim whitespace from a string
        // Find the first character that isnt whitespace
        size_t start = input.find_first_not_of(" \t\r\n");

        if (start == string::npos) { // if the first character is empty (if the string is empty),
            return NULL; // then return null
        }

        // otherwise, remove extra spaces from beginning and end of line
        size_t end = input.find_last_not_of(" \t\r\n");
        input = input.substr(start, end - start + 1);

        return input;
}

string Files::to_upper(string text) {    // Converts string to uppercase so capitalization doesn't matter when comparing names
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return toupper(c); });
    return text;
}

string Files::to_lower(string text) {    // Converts string to lowercase so capitalization doesn't matter when comparing names
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return tolower(c); });
    return text;
}

vector<string> Files::split(string input, string delimiter) { // split a string by a delimter and return a list of tokens
    vector<string> tokens; 
    size_t pos = 0;
    string token;
    while ((pos = input.find(delimiter)) != string::npos) { // for each delimiter (until we run out)
        token = input.substr(0, pos); // split the string along the delimiter
        tokens.push_back(token); // add the splitted string to the tokens
        input.erase(0, pos + delimiter.length()); // remove the token from the source string so we can keep processing it
    }
    tokens.push_back(input); // push the remaning input (the last token)

    return tokens; // and treturn the list of tokens
}

vector<string> Files::processFileLine(string line, string delim, int &lineNumber) { // combination of all of the above functions to make processing the loaded files easier and more standard
    lineNumber++;

    // Find the first character that isnt whitespace
    size_t start = line.find_first_not_of(" \t\r\n");

    if (start == string::npos) { // if line is empty
        return vector<string>(); // then skip
    }

    // Remove extra spaces from beginning and end of line
    size_t end = line.find_last_not_of(" \t\r\n");
    line = line.substr(start, end - start + 1);

    
    if (line[0] == '#') { // if the line begins with #, it is a comment
        return vector<string>(); // then skip
    }

    return Files::split(line, "|"); // split the line and return it
}