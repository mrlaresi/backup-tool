#include <fstream> // io file
#include <iostream> // input output
#include <filesystem> // traversing files
#include <ostream>
#include <sstream> // string stream
#include <system_error>
#include <vector> // std::vector


// Until C++20 standard gets implimented in compilers:
// {
// For linux
#ifndef _WIN32
#include <sys/types.h>
#include <sys/stat.h>
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
        std::vector<fs::path> backup_paths; // all the paths
        fs::path backup_addr; // backup file
        fs::path backup_dest; // destination of backups

        std::error_code copy_folder (const fs::path&, const fs::path&);
        std::string get_time();
    public:
        FileInOut();
        int read_backup();
        void backup();
        void add_backup(const fs::path);
        time_t modify_time(const std::string&);
};


/**
* Recursively copies the contents of the source folder into the destination
* folder. Returns 0 or an error code depending on if the operation was successful
*/
std::error_code FileInOut::copy_folder(const fs::path &source, const fs::path &destination) {
    std::error_code error;
    if (!source.is_absolute() || !destination.is_absolute()) {
        // Should never be reached
        throw "Either source or destination of operation 'copy_folder' is not absolute path.";
    }
    fs::copy(source, destination, fs::copy_options::recursive, error);
    return error;
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
 * Default constructor
 */
FileInOut::FileInOut() {
    fs::path default_addr = "./back.txt";
    fs::path default_dest = "./testfolder"; // TODO: placeholder
    std::error_code error;
    backup_addr = fs::canonical(default_addr, error);
    if (error) {
        std::cout << "Backup file doesn't exist. Creating a new file." << std::endl;
        backup_addr = fs::weakly_canonical(default_addr, error);
        backup_dest = fs::weakly_canonical(default_dest, error);
        if (error) { 
            std::cerr << "Unexpected error:" << error << std::endl;
        }
        std::fstream file;
        file.open(backup_addr, std::fstream::app);
        file << "" << std::endl;
        file.close();
    }
    
}


/**
* Reads backup paths from the file and into vector
* Return 1 if reading file failed.
*/
int FileInOut::read_backup() {
    std::fstream file;
    file.open(backup_addr, std::fstream::in);
    if (file.fail()) { 
        std::cerr << "Encountered error reading backup paths." << std::endl;
        return 1; 
    }
    while (!file.eof()) {
        std::string buffer;
        std::getline(file, buffer);
        fs::path p = buffer; 
        std::error_code error;
        fs::canonical(p, error);
        if (error) {
            std::cerr << "Invalid file location: " << p << std::endl;
            continue;
        }
        backup_paths.push_back(p);
    }
    file.close();
    return 0;
}
    

/**
* Recursively copies folder and it's contents to another location
*/
void FileInOut::backup() {
    time_t current_time = std::time(nullptr);
    unsigned count = 0;
    fs::path folder_name = get_time();

    for (unsigned i = 0; i < backup_paths.size(); i++) {
        // Do nothing if file hasn't been modified
        if (modify_time(backup_paths[i]) < last_backup) { continue; }
        std::cout << "Copying " << backup_paths[i] << " to " << backup_dest << std::endl;
        std::error_code error = copy_folder(backup_paths[i], backup_dest / folder_name);
        
        if (error) {
            std::cout << "Something went wrong while copying files " << backup_paths[i] << std::endl;
            continue;
        }
        count ++;
    }
        
    std::cout << "Done. Total " << count << " folders backed up." << std::endl;
    if (count > 0) {
        last_backup = current_time;
    }
}


/**
* Adds new file path to the list of backups
*/
void FileInOut::add_backup(const fs::path path) {
    std::fstream file;
    file.open(path, std::fstream::in);
    file.close();
    // Check if file exists
    if (file.fail()) {
        std::cerr << "Input file '" << path << "' does not exist." << std::endl;
        return; 
    }
    // Will create new file if the file doesn't exist
    file.open(backup_addr, std::fstream::app);
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
    //fio.backup("aha", "zika");
    //std::cout << fio.modify_time("maha.txt") << std::endl ;
    return 0;
}