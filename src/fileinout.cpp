#include <fstream> // io file
#include <filesystem> // traversing files
#include <vector> // std::vector

#include "validator.h"
#include "fileinout.h"

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


std::string FileInOut::write_to_file(const fs::path& file_path, const std::string& text) {
    fs::path p = Validator::validate_path(file_path);
    if (p == "") {
        return "Invalid path.\n";
    }
    
    std::fstream file;
    // Will create new file if the file doesn't exist
    file.open(file_path, std::fstream::out | std::fstream::app);
    // Should only be reached if the file is already in use
    if (file.fail()) {
        return "Unexpected error occurred. File might already be in use.\n";
    }
    file << text << "\n";
    file.close();
    return "";
}


std::string FileInOut::create_file(const fs::path& file_path) {
    fs::path parent = Validator::has_parent(file_path);
    if (parent != "") {
        std::fstream file;
        file.open(file_path, std::fstream::app);
        file.close();
        return "File created: " + (parent / file_path).string() + "\n";
    }
    return "Invalid filepath.\n";
}


std::string FileInOut::create_folder(const fs::path& file_path) {
    fs::path parent = Validator::has_parent(file_path);
    if (parent != "") {
        fs::create_directory(file_path);
        return "Folder created: " + (parent / file_path).string() + "\n";
    }
    return "Invalid filepath.\n";
}


std::string FileInOut::remove_line(const fs::path& file_path, const std::string& text) {
    fs::path p = Validator::validate_path(file_path);
    if (p == "") {
        return "Invalid path.\n";
    }
    fs::path new_file = p.parent_path() / "placeholder.txt";
    std::fstream original, modified;
    original.open(file_path, std::fstream::in);
    if (original.fail()) {
        return "Unexpected error occurred. File might already be in use.\n";
    }
    modified.open(new_file, std::fstream::out | std::fstream::trunc);
    if (modified.fail()) {
        return "Unexpected error occurred. File might already be in use.\n";
    }
    std::string line;
    while (getline(original, line)) {
        if (line != text) {
            modified << line << "\n";
        }
    }
    original.close();
    modified.close();
    fs::remove(p);
    fs::rename(new_file, p);
    return "";
}


std::vector<std::string> FileInOut::read_file(const fs::path& path) {
    std::fstream file;
    std::vector<std::string> lines;
    file.open(path, std::fstream::in);

    if (file.fail()) { 
        return lines; 
    }

    while (!file.eof()) {
        std::string buffer;
        std::getline(file, buffer);
        lines.push_back(buffer);
    }
    return lines;
}


fs::path FileInOut::fetch_filename_stem(const fs::path& path) {
    return path.stem().string();
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

std::error_code FileInOut::copy(const fs::path &source, const fs::path &destination) {
    std::error_code error;
    // if directory, do recursive
    if (!Validator::validate_directory(destination)) {
        create_folder(destination);
    }
    if (Validator::validate_directory(source)) {
        fs::copy(source, destination / source.filename(), fs::copy_options::recursive, error);
        return error;
    }
    fs::copy(source, destination, error);
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
