#include "validator.h"
#include "fileinout.h"
#include <fstream> // io file
#include <iostream> // input output
#include <sstream> // string stream
#include <filesystem> // traversing files
#include <vector> // std::vector
#include <algorithm> // std::find


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

FileInOut::FileInOut(const std::string& addr, const std::string& dest) {
    fs::path default_addr = addr;
    fs::path default_dest = dest; // TODO: placeholder
    backup_addr = Validator::validate_path(default_addr);
    backup_dest = Validator::validate_path(default_dest);

    if (backup_addr == "") {
        if (Validator::has_parent(backup_addr)) {
            std::cout << "File containing backups doesn't exist. Creating" << std::endl;
            std::fstream file;
            file.open(backup_addr, std::fstream::app);
            file.close();
        }
    }
    
    if (backup_dest == "") {
        if (Validator::has_parent(backup_dest)) {
            fs::create_directory(backup_dest);
        }
    }
    read_backup();
}
    

void FileInOut::backup() {
    time_t current_time = std::time(nullptr);
    unsigned count = 0;
    unsigned skip = 0;
    fs::path folder_name = get_time();
    std::cout << "Performing backup on " << backup_paths.size() << " locations.\n";

    for (unsigned i = 0; i < backup_paths.size(); i++) {
        // Do nothing if file hasn't been modified
        if (modify_time(backup_paths[i]) < last_backup) { skip++; continue; }
        std::cout << "Copying " << backup_paths[i] << " to " << backup_dest << "\n";
        std::error_code error = copy_folder(backup_paths[i], backup_dest / folder_name);
        
        // Shouldn't happen unless file located at the filepath was removed
        if (error) {
            std::cout << "Something went wrong while copying files from " << backup_paths[i] << "\n";
            continue;
        }
        count++;
    }
        
    std::cout << "Done. Total " << count << " folders backed up.\n";
    std::cout << "Skipped " << skip << " folders as no modifications had been made\n";
    if (count > 0) {
        last_backup = current_time;
    }
}


int FileInOut::add_backup(const fs::path& path) {
    auto it = exists(path);
    if (it != backup_paths.end()) {
        std::cout << "Filepath already exists on the list. No changes were made.\n";
        return 0;
    }
    std::fstream file;
    // Will create new file if the file doesn't exist
    file.open(backup_addr, std::fstream::out | std::fstream::app);
    file << path.string() << "\n";
    file.close();
    backup_paths.push_back(path);
    std::cout << "Added filepath " << path.string() << "\n";
    return 1;
}


int FileInOut::remove_backup(const fs::path& path) {
    auto it = exists(path);
    if (it == backup_paths.end()) {
        return 0; 
    }
    backup_paths.erase(it);
    std::cout << "Removed filepath " << path.string() << "\n";
    update_file();
    return 1;
}


std::vector<std::string> FileInOut::read_file(const fs::path& path) {
    std::fstream file;
    std::vector<std::string> lines;
    file.open(path, std::fstream::in);

    if (file.fail()) { 
        std::cerr << "Encountered error reading backup paths.\n";
        return lines; 
    }

    while (!file.eof()) {
        std::string buffer;
        std::getline(file, buffer);
        lines.push_back(buffer);
    }
    return lines;
}


void FileInOut::set_backup(const fs::path& path) {
    backup_dest = path;
}


void FileInOut::read_backup() {
    fs::path p;
    std::vector<std::string> lines = this->read_file(backup_addr);
    for (unsigned i = 0; i < lines.size(); i++) {
        if (lines[i] == "") { continue; }
        p = lines[i]; 
        p = Validator::validate_path(p);
        if (p == "") {
            std::cerr << "Invalid file location: " << lines[i] << "\n";
            continue;
        }
        backup_paths.push_back(p);
    }
}


void FileInOut::update_file() {
    std::fstream file;
    file.open(backup_addr, std::fstream::out | std::fstream::trunc);
    for (unsigned i = 0; i < backup_paths.size(); i++) {
        file << backup_paths[i].string() << "\n";
    }
    file.close();
    std::cout << "Refreshed backup file.\n";
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

std::vector<fs::path>::iterator FileInOut::exists(const fs::path& path) {
    std::vector<fs::path>::iterator it = std::find(backup_paths.begin(), backup_paths.end(), path);
    return it;
}
