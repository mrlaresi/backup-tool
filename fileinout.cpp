#include "fileinout.h"
#include <fstream> // io file
#include <iostream> // input output
#include <sstream> // string stream
#include <filesystem> // traversing files
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


FileInOut::FileInOut() {
    fs::path default_addr = "./back.txt";
    fs::path default_dest = "./testfolder"; // TODO: placeholder
    std::error_code error1;
    std::error_code error2;
    backup_addr = fs::canonical(default_addr, error1);
    backup_dest = fs::canonical(default_dest, error2);
    if (error1) {
        std::cout << "Backup file isn't in correct format." << std::endl;
        // TODO: replace with proper handling
        exit(1);
    }
    if (!fs::exists(backup_addr)) {
        std::cout << "File containing backups doesn't exist. Creating" << std::endl;
        std::fstream file;
        file.open(backup_addr, std::fstream::app);
        if (file.fail()) {
            std::cerr << "Folder containing the file doesn't exist." << std::endl;
            // TODO: replace with proper handling
            exit(1);
        }
        file.close();
    }
    if (error2) {
        std::cout << "Backup folder isn't in correct format." << std::endl;
        // TODO: replace with proper handling
        exit(1);
    }
    if (!fs::exists(backup_dest)) {
        if (!fs::create_directory(backup_dest)) {
            std::cout << "Unable to create directory." << std::endl;
            // TODO: replace with proper handling
            exit(1);
        }
        
    }
    
}


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
        fs::absolute(p, error);
        if (error) {
            std::cerr << "Invalid file location: " << p << std::endl;
            continue;
        }
        backup_paths.push_back(p);
    }
    file.close();
    return 0;
}
    

void FileInOut::backup() {
    time_t current_time = std::time(nullptr);
    unsigned count = 0;
    unsigned skip = 0;
    fs::path folder_name = get_time();
    std::cout << "Performing backup on " << backup_paths.size() << " folders.\n";

    for (unsigned i = 0; i < backup_paths.size(); i++) {
        // Do nothing if file hasn't been modified
        if (modify_time(backup_paths[i]) < last_backup) { skip++; continue; }
        std::cout << "Copying " << backup_paths[i] << " to " << backup_dest << "\n";
        std::error_code error = copy_folder(backup_paths[i], backup_dest / folder_name);
        
        if (error) {
            std::cout << "Something went wrong while copying files from " << backup_paths[i] << "\n";
            continue;
        }
        count ++;
    }
        
    std::cout << "Done. Total " << count << " folders backed up.\n";
    std::cout << "Skipped " << skip << " folders as no modifications had been made." << std::endl;
    if (count > 0) {
        last_backup = current_time;
    }
}


void FileInOut::add_backup(const fs::path& path) {
    std::fstream file;
    // Will create new file if the file doesn't exist
    file.open(backup_addr, std::fstream::app);
    file << path.string() << std::endl;
    file.close();
    std::cout << "Added filepath " << path.string() << std::endl;
}


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

std::error_code FileInOut::copy_folder(const fs::path &source, const fs::path &destination) {
    std::error_code error;
    if (!source.is_absolute() || !destination.is_absolute()) {
        // Should never be reached
        throw "Either source or destination of operation 'copy_folder' is not absolute path.";
    }
    fs::copy(source, destination, fs::copy_options::recursive, error);
    return error;
}


std::string FileInOut::get_time() {
    std::time_t t = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y%m%d_%H%M");
    std::string ret;
    ss >> ret;
    return ret;
}