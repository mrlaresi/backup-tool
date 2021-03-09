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
        time_t last_backup = -1; // time of last backup
        std::vector<std::string> backup_paths; // all the paths
        std::string backup_path; // backup file

        void copy_folder (const fs::path&, const fs::path&);
        std::string get_time();
    public:
        FileInOut();
        int read_backup();
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
 * Constructor
 */
FileInOut::FileInOut() {
    backup_path = "./back.txt";
}

/**
* Reads backup paths from the file and into vector
* Return 1 if reading file failed.
*/
int FileInOut::read_backup() {
    std::fstream file;
    file.open(backup_path, std::fstream::in);
    if (file.fail()) { 
        std::cerr << "Encountered error reading backup paths." << std::endl;
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
* Adds new file path to the list of backups
*/
void FileInOut::add_backup(const char* path) {
    std::fstream file;
    file.open(path, std::fstream::in);
    file.close();
    // Check if file exists
    if (file.fail()) {
        std::cerr << "Input file '" << path << "' does not exist." << std::endl;
        return; 
    }
    // Will create new file if the file doesn't exist
    file.open(backup_path, std::fstream::app);
    file << path << std::endl;
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