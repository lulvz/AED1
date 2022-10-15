#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include <fstream>
#include <fstream>
#include <sstream>
class CsvReader {
public:
    bool error = false;
    CsvReader(const std::string& filename);
    std::vector<std::string> readNextLine();
    bool eof() const;
private:
    std::string filename;
    std::fstream file;
};


#endif