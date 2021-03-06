#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

class FileInOut {
    private:
        std::vector<std::string> backup_paths;
        std::string file_in;
        std::string backup_location;
        void copy_folder (const fs::path&, const fs::path&);
        std::string get_time();
    public:
        int read_backup(const char*);
        void backup(const char*, const char*);
        int add_backup(const char*);
};

/**
* Recursively copies the contents of the source folder into the destination
* folder.
*/
void FileInOut::copy_folder(const fs::path &source, const fs::path &destination) {
    fs::copy(source, destination, fs::copy_options::recursive);
}

/**
* Get current local time in yyyymmdd_hhmm format
*/
std::string FileInOut::get_time() {
    std::time_t t = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y%m%d_%H%M");
    std::string ret;
    ss >> ret;
    return ret;
}

/**
* Reads lines containing backup locations from the file and into vector
* Return 1 if reading file failed.
*/
int FileInOut::read_backup(const char *file_in) {
    std::fstream file;
    file.open(file_in, std::fstream::in);
    if (file.fail()) { 
        std::cerr << "Encountered error reading file '" << file_in << "'." << std::endl;
        return 1; 
    }
    while (!file.eof()) {
        std::string buffer;
        std::getline(file, buffer);
        backup_paths.push_back(buffer);
        //std::cout << buffer<<std::endl;
    }
    file.close();
    return 0;
}
    
/**
* Recursively copies folder and it's contents to another location
*/
void FileInOut::backup(const char *source, const char *location) {
    std::string folder_name = "./" + get_time();
    std::cout << "Copying to " << location << std::endl;
    copy_folder(source, location);
    std::cout << "Done" << std::endl;
}

/**
* Adds new file location to the list of backups
*/
int FileInOut::add_backup(const char* location) {
    std::fstream file;
    file.open(location, std::fstream::in);
    file.close();
    if (file.fail()) {
        std::cerr << "Input file '" << location << "' does not exist." << std::endl;
        return 1; 
    }
    file.open("osoitteita.txt", std::fstream::app);
    file << "\nasd";
    file.close();
    return 0;
}

int main() {
    FileInOut fio;
    //add_backup();
    fio.add_backup("asd");
    if (0<fio.read_backup("osoitteita.txt")) {std::cout << "error";}
    return 0;
}