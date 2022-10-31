#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
class CsvReader {
public:
    bool error = false;
    CsvReader(const std::string& filename);
    std::vector<std::string> readNextLine();
    void writeLine(std::vector<std::string>);
    void writeLines(std::vector<std::vector<std::string>>);
    bool eof() const;
    std::vector<std::string> getHeader();
private:
    std::string filename;
    std::fstream file_read;
    std::fstream file_write;

    std::vector<std::string> header;
};


#endif