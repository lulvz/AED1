#include "csv_reader.h"

CsvReader::CsvReader(const std::string& filename) {
    this->filename = filename;
    this->file = std::fstream(filename);
    if (!this->file) {
        this->error = true;    
    }
    // skip first line and store it in the header variable
    std::string line;
    std::getline(this->file, line);
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) {
        this->header.push_back(item);
    }
}

std::vector<std::string> CsvReader::readNextLine() {
    std::vector<std::string> parts;
    std::string line;
    if (getline(this->file, line)) {
        std::stringstream ss(line);
        std::string part;
        while (getline(ss, part, ',')) {
            parts.push_back(part);
        }
    }
    return parts;
}

std::vector<std::string> CsvReader::getHeader() {
    return this->header;
}

bool CsvReader::eof() const { 
    return this->file.eof();
}