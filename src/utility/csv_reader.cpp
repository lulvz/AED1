#include "csv_reader.h"

CsvReader::CsvReader(const std::string& filename) {
    this->filename = filename;
    this->file_read = std::fstream(filename);
    this->file_write = std::fstream(filename, std::ios::app);
    if (!this->file_read) {
        this->error = true;    
    }
    if (!this ->file_write) {
        this->error = true;
    }
    // skip first line and store it in the header variable
    std::string line;
    std::getline(this->file_read, line);
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) {
        this->header.push_back(item);
    }
}

std::vector<std::string> CsvReader::readNextLine() {
    std::vector<std::string> parts;
    std::string line;
    if (getline(this->file_read, line)) {
        std::stringstream ss(line);
        std::string part;
        while (getline(ss, part, ',')) {
            parts.push_back(part);
        }
    }
    return parts;
}
// just open file in write mode trunc, which deletes content
// of the file and then open it back up in append mode
void CsvReader::clearFile() {
    this->file_write.close();
    this->file_write.open(this->filename, std::ios::out | std::ios::trunc);
    this->file_write.close();
    this->file_write.open(this->filename, std::ios::app);
}
void CsvReader::writeLine(std::vector<std::string> sv) {
    std::string final = "";
    for(std::string s : sv) {
        final += s + ",";
    }  
    final.pop_back();
    file_write << final << std::endl; 
}

void CsvReader::writeLines(std::vector<std::vector<std::string>> svv) {
    for(std::vector<std::string> sv : svv) {
        CsvReader::writeLine(sv); 
    }
}

std::vector<std::string> CsvReader::getHeader() {
    return this->header;
}

bool CsvReader::eof() const { 
    return this->file_read.eof();
}