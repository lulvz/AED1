#include "csv_reader.h"

/*! @brief Construtor CsvReader, cria dois objetos fstream para ler e escrever potenciais alterações nos horários.
*          
*   @param[in] filename
*/

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
    std::string line;
    std::getline(this->file_read, line);
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) {
        this->header.push_back(item);
    }
}

/*! @brief Função que lê uma linha de um objecto CsvReader, guardando a informação encontrada nessa linha num vetor.
*   
*   @return É retornado um vector<string> contendo as informações da linha lida.
*/

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

/*! @brief Função que apaga todos os conteúdos de um objeto CsvReader, e abre-o de novo em modo write.
*/

void CsvReader::clearFile() {
    this->file_write.close();
    this->file_write.open(this->filename, std::ios::out | std::ios::trunc);
    this->file_write.close();
    this->file_write.open(this->filename, std::ios::app);
}

/*! @brief Função que escreve o conteúdo de uma string para uma linha de um objeto CsvReader.
*   
*   @param[in] sv
*/
void CsvReader::writeLine(std::vector<std::string> sv) {
    std::string final = "";
    for(std::string s : sv) {
        final += s + ",";
    }  
    final.pop_back();
    file_write << final << std::endl; 
}

/*! @brief Funçâo que escreve o conteúdo de um conjunto de strings, linha a linha, para um objeto CsvReader.
*   
*   @param[in] svv
*/

void CsvReader::writeLines(std::vector<std::vector<std::string>> svv) {
    for(std::vector<std::string> sv : svv) {
        CsvReader::writeLine(sv); 
    }
}

/*! @brief Função de ulilidade da classe CsvReader.
*
*   @return Devolve o header do respetivo ficheiro CsvReader.
*/

std::vector<std::string> CsvReader::getHeader() {
    return this->header;
}

/*! @brief Função de ultilidade da classe CsvReader.
*   
*   @return Retorna True caso o ficheiro já tenha sido completamente lido (end_of_file).
*/

bool CsvReader::eof() const { 
    return this->file_read.eof();
}