#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

/**
 * Recursively copies the contents of the source folder into the destination
 * folder.
 */
void copy_folder(const fs::path &source, const fs::path &destination) {
    fs::copy(source, destination, fs::copy_options::recursive);
}


/**
 * Reads files to be backed up from a file
 */
int read_backup(const char* file_in) {
    std::fstream file;
    file.open(file_in, std::fstream::in);
    if (file.fail()) { return 1; }
    while (!file.eof()) {
        char buffer[512];
        file.getline(buffer, 512);
        std::cout << buffer<<std::endl;
    }
    file.close();
    return 0;
}

/**
 * Get current local time in yyyymmdd_hhmm format
 */
std::string get_time() {
    std::time_t t = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y%m%d_%H%M");
    std::string ret;
    ss >> ret;
    return ret;
}

/**
 * Recursively copies folder and it's contents to another location
 */
void backup(const char* source, const char* location) {
    std::string folder_name = "./" + get_time();
    std::cout << "Copying to " << location << std::endl;
    copy_folder(source, location);
    std::cout << "Done" << std::endl;
}

/**
 * Adds new file location to the list of backups
 */
void add_backup() {
    std::fstream file;
    file.open("osoitteita.txt", std::fstream::app);
    file << "\nasd";
    file.close();
}

int main() {
    //backup();
    
    add_backup();
    if (0<read_file("osoitteita.txt")) {std::cout << "error";}
    return 0;
}