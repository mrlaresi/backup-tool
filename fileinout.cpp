#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

// Until C++20 standard gets implimented in compilers:
// {
// For linux
#ifndef _WIN32
#include <unistd.h>
#endif

// For windows
#ifdef _WIN32
#define stat _stat
#endif
// }

namespace fs = std::filesystem;
//namespace chrono = std::chrono;

class FileInOut {
    private:
        time_t last_backup = -1;
        std::vector<std::string> backup_paths;
        std::string file_in;
        std::string backup_location;
        void copy_folder (const fs::path&, const fs::path&);
        std::string get_time();
    public:
        int read_backup(const char*);
        void backup(const char*, const char*);
        void add_backup(const char*);
        time_t modify_time(const std::string&);
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
    last_backup = std::time(nullptr);
    std::string folder_name = "./" + get_time();
    std::cout << "Copying to " << location << std::endl;
    copy_folder(source, location);
    std::cout << "Done" << std::endl;
}

/**
* Adds new file location to the list of backups
*/
void FileInOut::add_backup(const char* location) {
    std::fstream file;
    file.open(location, std::fstream::in);
    file.close();
    // Check if file exists
    if (file.fail()) {
        std::cerr << "Input file '" << location << "' does not exist." << std::endl;
        return; 
    }
    // Will create new file if the file doesn't exist
    file.open("maha.txt", std::fstream::app);
    file << location << std::endl;
    file.close();
}

/**
 * Returns the date and time of the last modification done to a given file 
 * in time_t format.
 */
time_t FileInOut::modify_time(const std::string &path) {
    /* Does not work until compiler supports C++20 >:c
       Would've been platform wide way to obtain time_t value
    
    auto mod_time = fs::last_write_time("asd.txt");
    auto ttime = decltype(mod_time)::clock::to_time_t(mod_time);
    */

    struct stat result;
    if (stat(path.c_str(), &result) ==0) {
        auto mod_time = result.st_mtime;
        return mod_time;
    }
    return -1;
}

int main() {
    FileInOut fio;
    //add_backup();
    //fio.add_backup("./zika/zika.txt");
    //if (0<fio.read_backup("osoitteita.txt")) {std::cout << "error";}
    std::cout << fio.modify_time("maha.txt");
    return 0;
}