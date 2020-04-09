#pragma once

#include <string>
#include <fstream>

namespace json {
// Moves the fileStream's streampos to the character after first character found
    char seek(char c, std::ifstream &fileStream);

// Move the fileStream's streampos to the first character that's in the given string
    char seek(const std::string &chars, std::ifstream &filestream);

// Seek the first non whitespace character
    char seekNonWS(std::ifstream &fileStream);

// Parse a string untill the specified character
    std::string parseUntill(char c, std::ifstream &fileStream);

}