#include "../include/Files.h"
#include <cctype>

string Files::trim(string input) { // trim a string
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

string Files::to_upper(string input) {
    for (unsigned int i = 0; i < input.size(); i++) {
        input[i] = toupper(input.at(i));
    }
    return input;
}